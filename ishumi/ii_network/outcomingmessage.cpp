#include "outcomingmessage.h"

using namespace ii;
using namespace std;



//=======================================================================================
class DataArray_Driver
{
public:
    DataArray_Driver( const VByteArray *a, int piece_size )
        : arr(a)
        , piece_size(piece_size)
    {
        pieces  = arr->size() / piece_size;
        pieces += arr->size() % piece_size ? 1 : 0;

        end_piece = arr->cbegin();
        shift_to_next();
    }

    bool at_end() const
    {
        return cur_piece == pieces;
    }

    void shift_to_next()
    {
        ++cur_piece;
        assert( cur_piece <= pieces );

        begin_piece = end_piece;

        end_piece = at_end() ? arr->cend() : end_piece + piece_size;
    }

    VByteArray::const_iterator begin_piece;
    VByteArray::const_iterator end_piece;

    int cur_piece = 0;
    int pieces;
    const VByteArray *arr;
    const int piece_size;
};

//=======================================================================================
uint OutcomingMessage::default_max_bin_size = 1300;
//=======================================================================================




//=======================================================================================
OutcomingMessage::OutcomingMessage( const string &target, const VByteArray &data )
    : _data   ( data   )
    , _msg_id ( rand() )
{
    assert( !target.empty() );

    while (!_msg_id) _msg_id = rand();

    _obj.emplace( target_label, target  );
    _obj.emplace( msg_id_label, _msg_id );
}
//=======================================================================================
void OutcomingMessage::insert(const string &label, const json11::Json &val)
{
    assert( !label.empty() && label.front() != '_' );

    _obj.emplace( label, val );
}
//=======================================================================================

OutcomingMessage::Dump OutcomingMessage::dump( uint max_bin_size )
{
    assert(max_bin_size > 0);

    bool need_fragment = _data.size() > max_bin_size;

    return need_fragment
            ? _dump_multi( max_bin_size )
            : _dump_one();
}
//=======================================================================================
OutcomingMessage::Dump OutcomingMessage::dump()
{
    return dump( default_max_bin_size );
}
//=======================================================================================
VByteArray OutcomingMessage::_make_packet( json11::Json::object *obj,
                                           VByteArray::const_iterator begin,
                                           VByteArray::const_iterator end )
{
    VByteArray res;

    if ( begin != end )
        obj->emplace( bin_size_label, int(end - begin) );

    res.append( json11::Json(*obj).dump() );
    res.append( '\0' );

    if ( begin != end )
        res.append( begin, end );

    return res;
}
//=======================================================================================
OutcomingMessage::Dump OutcomingMessage::_dump_one()
{
    return { _make_packet(&_obj, _data.cbegin(), _data.cend()) };
}
//=======================================================================================
OutcomingMessage::Dump OutcomingMessage::_dump_multi( int piece_size )
{
    Dump res;

    DataArray_Driver arr_driver( &_data, piece_size );

    _obj.emplace( fragment_num_label, 1 );
    _obj.emplace( fragment_count_label, arr_driver.pieces );

    auto packet = _make_packet( &_obj, arr_driver.begin_piece, arr_driver.end_piece);
    res.push_back( packet );

    while( !arr_driver.at_end() )
    {
        arr_driver.shift_to_next();

        json11::Json::object fobj;
        fobj.emplace(msg_id_label, _msg_id);
        fobj.emplace(fragment_num_label, arr_driver.cur_piece);
        fobj.emplace(fragment_count_label, arr_driver.pieces);

        auto frag = _make_packet(&fobj, arr_driver.begin_piece, arr_driver.end_piece);
        res.push_back( frag );
    }
    return res;
}
//=======================================================================================

