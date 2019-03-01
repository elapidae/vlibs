#ifndef DecoderTransmitter_H
#define DecoderTransmitter_H

#include <memory>
#include <functional>
#include <map>
#include <set>
#include "serialization/serialization_decoder.h"


//=======================================================================================
template<typename T>
class DecoderTransmitter;

//=======================================================================================
class DecoderTransmitter_Iface
{
public:
    using SharedPtr = std::shared_ptr< DecoderTransmitter_Iface >;

    template<typename T, typename Fn>
    void subscribe( Fn fn, const std::string& channel );

    template<typename T, typename Fn>
    void subscribe_multi( Fn fn );

    template<typename T>
    void transmit( const T& val, const std::string& channel );

    void decode( serialization::ReadBuffer *buf, const std::string& channel );
    void decode( const VString& buf, const std::string& channel );

private:
    template<typename T> DecoderTransmitter<T>& _derived();
};

//=======================================================================================
template<typename T>
class DecoderTransmitter : public DecoderTransmitter_Iface
{
public:
    static SharedPtr make() { return std::make_shared<DecoderTransmitter<T>>(); }

    using Sink = std::function<void(const T&)>;
    using SinkMulti = std::function<void(const T&,const std::string&)>;

    void do_subscribe( const Sink& sink, const std::string& channel );
    void do_subscribe_multi( const SinkMulti& sink );
    void do_decode( serialization::ReadBuffer *buf, const std::string& channel );
    void do_decode( const VString& buf, const std::string& channel );
    void do_transmit( const T& val, const std::string& channel );

private:
    std::map<std::string,Sink> sinks;
    std::vector<SinkMulti> sinks_multi;
};

//=======================================================================================
template<typename T, typename Fn>
void DecoderTransmitter_Iface::subscribe( Fn fn, const std::string& channel )
{
    _derived<T>().do_subscribe( std::forward<Fn>(fn), channel );
}
//---------------------------------------------------------------------------------------
template<typename T, typename Fn>
void DecoderTransmitter_Iface::subscribe_multi( Fn fn )
{
    _derived<T>().do_subscribe_multi( std::forward<Fn>(fn) );
}
//---------------------------------------------------------------------------------------
template<typename T>
void DecoderTransmitter_Iface::transmit( const T& val, const std::string& channel )
{
    _derived<T>().do_transmit( val, channel );
}
//---------------------------------------------------------------------------------------
//void DecoderTransmitter_Iface::decode( serialization::ReadBuffer *buf,
//                                       const std::string& channel )
//{
//    //_derived<T>().do_decode( buf, channel );
//}
//---------------------------------------------------------------------------------------
//void DecoderTransmitter_Iface::decode( const VString& buf, const std::string& channel )
//{
//    //_derived<T>().do_decode( buf, channel );
//}
//---------------------------------------------------------------------------------------
template<typename T>
DecoderTransmitter<T>& DecoderTransmitter_Iface::_derived()
{
    return dynamic_cast< DecoderTransmitter<T>& >( *this );
}

//=======================================================================================
template<typename T>
void DecoderTransmitter<T>::do_subscribe( const Sink& sink, const std::string& channel )
{
    sinks.insert( {channel,sink} );
}
//---------------------------------------------------------------------------------------
template<typename T>
void DecoderTransmitter<T>::do_subscribe_multi( const SinkMulti& sink )
{
    sinks_multi.push_back( sink );
}
//---------------------------------------------------------------------------------------
template<typename T>
void DecoderTransmitter<T>::do_decode( serialization::ReadBuffer *buf,
                                       const std::string& channel )
{
    auto val = serialization::AbstractDecoder::decode<T>( buf );
    do_transmit( val, channel );
}
//---------------------------------------------------------------------------------------
template<typename T>
void DecoderTransmitter<T>::do_decode( const VString& buf,
                                       const std::string& channel )
{
    auto val = serialization::AbstractDecoder::decode<T>( buf );
    do_transmit( val, channel );
}
//---------------------------------------------------------------------------------------
template<typename T>
void DecoderTransmitter<T>::do_transmit( const T& val, const std::string& channel )
{
    auto range = sinks.equal_range( channel );
    for ( auto it = range.first; it != range.second; ++it )
        (*it)( val );

    for ( auto& it: sinks_multi )
        it( val );
}
//=======================================================================================

#endif // DecoderTransmitter_H
