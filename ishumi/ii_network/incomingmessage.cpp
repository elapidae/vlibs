#include "incomingmessage.h"

#include "vlogger.h"

using namespace ii;
using namespace std;
using namespace std::chrono;


//=======================================================================================
template<typename C, typename K>
static bool contains( const C& c, const K &key )
{
    return c.find( key ) != c.end();
}
//=======================================================================================


//=======================================================================================
//IncomingMessage::IncomingMessage( json11::Json &&j )
//    : _obj( j.object_items() )
//{
//    if ( !j.is_object() )
//        throw Error("Incoming json is not object.");

//    if ( !contains(_obj, msg_id_label) )
//        throw Error("Incoming message has not msg-id label.");
//}
//=======================================================================================
IncomingMessage::IncomingMessage( const json11::Json::object &o, const VByteArray &b )
    : _obj( o )
    , _bin( b )
{}
//=======================================================================================
string IncomingMessage::target() const
{
    auto t = _obj.find( target_label );
    return t == _obj.cend()
                        ? string()
                        : (*t).second.string_value();
}
//=======================================================================================
int32_t IncomingMessage::msg_id() const
{
    auto res = _obj.at( msg_id_label ).int_value();
    if ( !res ) throw Error("Message id is broken.");
    return res;
}
//=======================================================================================
const VByteArray &IncomingMessage::bin() const
{
    return _bin;
}
//=======================================================================================
string IncomingMessage::meta_string(const string &label) const
{
    return meta_root().at(label).string_value();
}
//=======================================================================================
const json11::Json::object &IncomingMessage::meta_root() const
{
    return _obj;
}
//=======================================================================================
//bool IncomingMessage::_is_fragmented() const
//{
//    return contains(_obj, fragment_num_label);
//}
//=======================================================================================
//bool IncomingMessage::_is_leading() const
//{
//    return !target().empty();
//}
//=======================================================================================
//void IncomingMessage::_set_data( VByteArray &&data )
//{
//    _bin = move(data);
//}
//=======================================================================================
//int IncomingMessage::_json_bin_size() const
//{
//    return _obj.at(bin_size_label).int_value();
//}
//=======================================================================================
//int IncomingMessage::_fragment_num() const
//{
//    auto fn = _obj.at( fragment_num_label );
//    if ( !fn.is_number() ) throw Error("fragment number is not correct");
//    return fn.int_value();
//}
//=======================================================================================
//int IncomingMessage::_fragment_count() const
//{
//    auto fn = _obj.at( fragment_count_label );
//    if ( !fn.is_number() ) throw Error("fragment number is not correct");
//    return fn.int_value();
//}
//=======================================================================================




//=======================================================================================
IncomingMessage::PacketsReceiver::PacketsReceiver(chrono::milliseconds expire_time)
    : _expire_time( expire_time )
{}
//=======================================================================================
void IncomingMessage::PacketsReceiver::set_expire_time(milliseconds expire_time)
{
    _expire_time = expire_time;
}
//=======================================================================================
void IncomingMessage::PacketsReceiver::append( const VByteArray &packet )
{
    clean_expired();

    _PacketParser parser( packet );

    if ( !parser.is_fragmented() )
    {
        received( parser.get_incoming() );
        return;
    }

    if ( !contains(_joiners, parser.msg_id()) )
    {
        _Joiner joiner( parser.msg_id(), parser.fragment_count() );
        _joiners.emplace( parser.msg_id(), joiner );
    }

    _Joiner & jref = _joiners.at(parser.msg_id());
    jref.append( parser );

    if ( !jref.is_ready() ) return;

    received( jref.get_incoming_message() );
    _joiners.erase( parser.msg_id() );
}
//=======================================================================================
void IncomingMessage::PacketsReceiver::clean_expired()
{
    auto now = steady_clock::now();

    vector<int32_t> exp_keys;
    for ( const auto & j: _joiners )
    {
        auto expire = now - j.second.last_usage();
        if (expire >= _expire_time)
            exp_keys.push_back( j.first );
    }

    for ( auto key: exp_keys )
    {
        vtrace(vlog("Msg with id", key, " has expired and will be kill."));
        _joiners.erase( key );
    }
}
//=======================================================================================
//void IncomingMessage::PacketsReceiver::_prepare_msg( IncomingMessage && msg,
//                                                    bool leading,
//                                                    int32_t msg_id )
//{
//    if (leading)
//    {
//        if ( contains(_messages, msg_id) ) throw Error("Msg id already in use.");
//        _messages.emplace( msg_id, move(msg) );
//    }

//    auto fragment_count = msg._fragment_count();

//    if ( !contains(_datas, msg_id) )
//    {
//        BinaryDataJoiner joiner( fragment_count );
//        _datas.emplace( msg_id, move(joiner) );
//    }

//    if ( _datas.at(msg_id).fragments_count() != fragment_count )
//        throw Error("Fragment count has not matched");
//}
//=======================================================================================



//=======================================================================================
//      _PacketParser
//=======================================================================================
IncomingMessage::_PacketParser::_PacketParser(const VByteArray &packet)
{
    auto zeropos = std::find( packet.cbegin(), packet.cend(), '\0' );
    if ( zeropos == packet.cend() ) throw Error("Cannot find zero symbol");

    string jerr;
    auto json = json11::Json::parse( string(packet.cbegin(), zeropos), jerr );
    if ( !jerr.empty() ) throw Error(jerr);
    if ( !json.is_object() ) throw Error("Json is not object");
    obj = json.object_items();

    frag_count    = obj[fragment_count_label].int_value();
    frag_num      = obj[fragment_num_label].int_value();
    mid           = obj[msg_id_label].int_value();
    has_target    = !obj[target_label].string_value().empty();
    json_bin_size = obj[bin_size_label].int_value();

    auto datapos = zeropos + 1; // ok, zero pos != end.
    bin.assign( datapos, packet.end() );

    _check_adequates();
}
//=======================================================================================
void IncomingMessage::_PacketParser::_check_adequates()
{
    if (mid == 0)
        throw Error("Msg_id is not defined.");

    if (frag_count < 0 || frag_num < 0)
        throw Error("Fragment count or num < 0.");

    if ( frag_count + frag_num > 0 )
    {
        if ( frag_count == 0 || frag_num == 0 )
            throw Error("Fragmented values are not adequete.");

        if ( frag_num > frag_count )
            throw Error("Fragment num > count");
    }

    if ( !is_leading() && !is_fragmented() )
        throw Error("Json is not fragment and is not leading message");

    if (int(bin.size()) != json_bin_size)
        throw Error("Size is not correct.");
}
//=======================================================================================
int32_t IncomingMessage::_PacketParser::msg_id() const
{
    return mid;
}
//=======================================================================================
bool IncomingMessage::_PacketParser::is_leading() const
{
    return has_target;
}
//=======================================================================================
bool IncomingMessage::_PacketParser::is_fragmented() const
{
    return frag_count != 0;
}
//=======================================================================================
int IncomingMessage::_PacketParser::fragment_count() const
{
    return frag_count;
}
//=======================================================================================
int IncomingMessage::_PacketParser::fragment_num() const
{
    return frag_num;
}
//=======================================================================================
IncomingMessage IncomingMessage::_PacketParser::get_incoming() const
{
    assert( !is_fragmented() );
    return IncomingMessage( get_json(), get_bin() );
}
//=======================================================================================
const VByteArray & IncomingMessage::_PacketParser::get_bin() const
{
    return bin;
}
//=======================================================================================
const json11::Json::object & IncomingMessage::_PacketParser::get_json() const
{
    return obj;
}
//=======================================================================================
//      _PacketParser
//=======================================================================================



//=======================================================================================
//      _Joiner
//=======================================================================================
IncomingMessage::_Joiner::_Joiner( int32_t my_msgid, int frags_count )
    : _msg_id( my_msgid )
    , _djoiner( frags_count )
{}
//=======================================================================================
int32_t IncomingMessage::_Joiner::msg_id() const
{
    return _msg_id;
}
//=======================================================================================
void IncomingMessage::_Joiner::append( const _PacketParser &packet )
{
    assert( msg_id() == packet.msg_id() );

    if ( packet.is_leading() && _has_leading )
        throw Error("Joiner: leading packet already received.");

    if ( packet.is_leading() )
    {
        _obj = packet.get_json();
        _has_leading = true;
    }

    _djoiner.push( packet.fragment_num(), packet.get_bin() );

    if ( _djoiner.is_ready() && !_has_leading )
        throw Error("Bin data ready, but has not leading info.");
}
//=======================================================================================
bool IncomingMessage::_Joiner::is_ready() const
{
    return _djoiner.is_ready();
}
//=======================================================================================
IncomingMessage IncomingMessage::_Joiner::get_incoming_message()
{
    assert( is_ready() );
    return IncomingMessage( _obj, _djoiner.join() );
}
//=======================================================================================
steady_clock_t IncomingMessage::_Joiner::last_usage() const
{
    return _djoiner.last_usage();
}
//=======================================================================================
//      _Joiner
//=======================================================================================
