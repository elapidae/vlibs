#ifndef TRANSMITTERBYCHANNELS_H
#define TRANSMITTERBYCHANNELS_H


#include <map>
#include <vector>
#include <memory>
#include "serialization/serialization_readbuffer.h"
#include "serialization/serialization_decoder.h"


//=======================================================================================
class TransmitterByChannels
{
public:
    template<typename T>
    static TransmitterByChannels make();

    template<typename T, typename Fn>
    void subscribe( Fn fn, const std::string& channel );

    template<typename T, typename Fn>
    void subscribe_multi( Fn fn );

    void decode( serialization::ReadBuffer *buf, const std::string& channel );
    void decode( const VString& buf, const std::string& channel );

private:
    class PimplBase; std::shared_ptr<PimplBase> p;
    TransmitterByChannels( std::shared_ptr<PimplBase>&& pp ) : p(std::move(pp)) {}

    template<typename T> class Pimpl;
    template<typename T> Pimpl<T>& dp() { return dynamic_cast<Pimpl<T>&>( *p ); }
};

//=======================================================================================
class TransmitterByChannels::PimplBase
{
public:
    virtual void decode( serialization::ReadBuffer *buf, const std::string& channel ) = 0;
    virtual void decode( const VString& buf, const std::string& channel ) = 0;

    virtual ~PimplBase() = default;
};
//=======================================================================================
template<typename T>
class TransmitterByChannels::Pimpl : public PimplBase
{
public:
    //-----------------------------------------------------------------------------------
    using Sink = std::function<void(const T&)>;
    using SinkMulti = std::function<void(const T&,const std::string&)>;
    //-----------------------------------------------------------------------------------
    void subscribe( const Sink& sink, const std::string& channel )
    {
        sinks.insert( {channel,sink} );
    }
    //-----------------------------------------------------------------------------------
    void subscribe_multi( const SinkMulti& sink )
    {
        sinks_multi.push_back( sink );
    }
    //-----------------------------------------------------------------------------------
    void transmit( const T& val, const std::string& channel )
    {
        auto range = sinks.equal_range( channel );
        for ( auto it = range.first; it != range.second; ++it )
            it->second( val );

        for ( auto& it: sinks_multi )
            it( val, channel );
    }
    //-----------------------------------------------------------------------------------
    void decode( serialization::ReadBuffer *buf, const std::string& channel ) override
    {
        auto val = serialization::AbstractDecoder::decode<T>( buf );
        transmit( val, channel );
    }
    //-----------------------------------------------------------------------------------
    void decode( const VString& buf, const std::string& channel ) override
    {
        auto val = serialization::AbstractDecoder::decode<T>( buf );
        transmit( val, channel );
    }
    //-----------------------------------------------------------------------------------
private:
    std::multimap<std::string,Sink> sinks;
    std::vector<SinkMulti> sinks_multi;
};
//=======================================================================================
template<typename T>
TransmitterByChannels TransmitterByChannels::make()
{
    return { std::make_shared<Pimpl<T>>() };
}
//---------------------------------------------------------------------------------------
template<typename T, typename Fn>
void TransmitterByChannels::subscribe( Fn fn, const std::string& channel )
{
    dp<T>().subscribe( std::forward<Fn>(fn), channel );
}
//---------------------------------------------------------------------------------------
template<typename T, typename Fn>
void TransmitterByChannels::subscribe_multi( Fn fn )
{
    dp<T>().subscribe_multi( std::forward<Fn>(fn) );
}
//=======================================================================================



#endif // TRANSMITTERBYCHANNELS_H
