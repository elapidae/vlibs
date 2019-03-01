#ifndef II_UDP_PACKETS_H
#define II_UDP_PACKETS_H

#include <assert.h>
#include "vlog_pretty.h"
#include <vector>
#include "vtimepoint.h"
#include "vstring.h"
#include "vserializable.h"
#include "serialization/serialization_hash.h"
#include "serialization/serialization_decoder.h"
#include "serialization/serialization_encoder.h"
#include "transmitterbychannels.h"


#include <set>
#include <map>
#include <unordered_map>


static constexpr auto default_packet_size = 1472;

using serialization::hash_type;
using Splitted_Packets = std::vector<VString>;
using diff_id_type = uint16_t; // поля для отличения пакетов из разных сообщений.

Splitted_Packets split_packets( const VString& primary_message,
                                hash_type hash_name,
                                hash_type hash_full,
                                const std::string& channel,
                                int pk_size = default_packet_size );

template<typename T>
Splitted_Packets encode_and_split( const T& msg,
                                   const std::string& channel,
                                   int pk_size = default_packet_size )
{
    using namespace serialization;
    auto str = Encoder::encode( msg );
    return split_packets( str,
                          hash_of_name<T>(),
                          hash_of_signature<T>(),
                          channel,
                          pk_size );
}

struct PacketHeap
{
    diff_id_type packet_id;     // max enthropy here.
    diff_id_type message_id;    //
    diff_id_type program_id;    //

    hash_type hash_name;
    hash_type hash_full;
};

static constexpr auto _tupline_PacketHeap = []( const PacketHeap& heap )
{
    return std::make_tuple( heap.packet_id,
                            heap.message_id,
                            heap.program_id,

                            heap.hash_name,
                            heap.hash_full );
};
template<> struct VSerializable<PacketHeap>
{
    result_of_lambda< decltype(_tupline_PacketHeap), PacketHeap >
    operator()( const PacketHeap& val )
    { return _tupline_PacketHeap(val); }
};

class PacketJoiner
{
public:
    void add( serialization::ReadBuffer* buf );
    bool ready() const;
    const VString& result() const;

    VSteadyTimePoint elapsed() const;

private:
    VSteadyTimePoint _last_ts;
    int packets_count = -1;
    std::map<int, std::string> packets;
    VString _res;
};

class ChannelsInfoObserver
{
public:
    void add_to_observe( const std::string& channel );
    void observe_all();

    bool is_observe( const std::string& channel ) const;
    bool is_observe( const serialization::channel_hash_type& h ) const;

private:
    bool _all = false;
    std::set<std::string> _channels;
    std::set<serialization::channel_hash_type> _hashes;
};

//=======================================================================================
namespace std
{
    template<>
    struct hash<PacketHeap>
    {
        size_t operator()( const PacketHeap& val ) const noexcept
        {
            return serialization::calc_hash( val );
        }
    };
}
//=======================================================================================


class UdpReceiver
{
public:

    template<typename T, typename Fn>
    void subscribe( Fn fn, const std::string& channel );

    template<typename T, typename Fn>
    void subscribe_multi( Fn fn );

    void add_packet( const VString &packet );

private:
    ChannelsInfoObserver channels_observer;
    std::map<hash_type,TransmitterByChannels> transmitters;
    std::map<hash_type,hash_type> type_signatures;

    template<typename T>
    TransmitterByChannels& get_transmitter();

    std::unordered_map<PacketHeap,PacketJoiner> joiners;
    PacketJoiner& joiner_for( const PacketHeap& heap );
};

template<typename T>
TransmitterByChannels& UdpReceiver::get_transmitter()
{
    auto tn_hash = serialization::hash_of_name<T>();
    auto transmitter = transmitters.find( tn_hash );

    if ( transmitter == transmitters.end() )
    {
        type_signatures.insert( tn_hash, serialization::hash_of_signature<T>() );
        transmitters.insert( {tn_hash,TransmitterByChannels::make<T>()} );
        transmitter = transmitters.find(tn_hash);
    }
    return transmitter->second;
}

template<typename T, typename Fn>
void UdpReceiver::subscribe( Fn fn, const std::string& channel )
{
    get_transmitter<T>().subscribe( std::forward<Fn>(fn), channel );
}

template<typename T, typename Fn>
void UdpReceiver::subscribe_multi( Fn fn )
{
    get_transmitter<T>().subscribe_multi( std::forward<Fn>(fn) );
}


#endif // II_UDP_PACKETS_H
