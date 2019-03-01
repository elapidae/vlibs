#include "ii_udp_packets.h"

#include "serialization/serialization_writebuffer.h"
#include "serialization/serialization_encoder.h"
#include "serialization/serialization_decoder.h"

#include "vrandom.h"
#include <atomic>
#include "verror.h"
#include <assert.h>


template<typename Cont, typename T>
struct _contains
{
    static bool contains( const Cont& c, const T& val )
    {
        auto it = std::find( c.begin(), c.end(), val );
        return it != c.end();
    }
};

template<typename Key, typename Mapped>
struct _contains<std::map<Key,Mapped>,Key>
{
    static bool contains( const std::map<Key,Mapped>& m, const Key& key )
    {
        auto it = m.find( key );
        return it != m.end();
    }
};


template<typename C, typename T>
static bool contains( const C& c, const T& val )
{
    return _contains<C,T>::contains( c, val );
}

//template<typename C, typename T>
//static bool contains<std::map<C,T>,T>( const C& c, const T& val )
//{
//    auto it = std::find( c.begin(), c.end(), val );
//    return it != c.end();
//}


//template<typename Key>
//template<typename Mapped>
//static bool contains( const std::map<Key,Mapped>& m, const Key& val )
//{
//    auto it = std::find( m.begin(), m.end(), val );
//    return it != m.end();
//}



//using namespace ii::udp;
using namespace serialization;


static diff_id_type program_id()
{
    static diff_id_type res = VRandom_mt19937().any<diff_id_type>();
    return res;
}

static diff_id_type packet_id()
{
    static VRandom_mt19937 rand;
    return rand.any<diff_id_type>();
}

static diff_id_type next_message_num()
{
    static std::atomic<diff_id_type> res{0};
    return ++res;
}


//  Calculate how much bytes can be written, extract from message this tail,
//  writes finished flag and tail to buffer.
static void extract_and_write_tail( VString::ForwardView *view,
                                    WriteBuffer *buf,
                                    int pk_size )
{
    int tail_size = pk_size - buf->size() - 1; // 1 byte as last flag.
    if ( tail_size <= 0 )
        throw verror("Packet size too little, tail_size = ", tail_size);
    tail_size = std::min( tail_size, view->remained() );

    auto tail = view->take_str( size_t(tail_size) );

    buf->write( view->finished() );
    buf->write_raw( tail );
}
//=======================================================================================
Splitted_Packets split_packets( const VString &primary_message,
                                         serialization::hash_type hash_name,
                                         serialization::hash_type hash_full,
                                         const std::string &channel,
                                         int pk_size )
{
    assert( pk_size > 0 );
    assert( !primary_message.empty() );

    WriteBuffer heap_buf;
    heap_buf.add_to_reserve( uint(pk_size) );

    auto heap = PacketHeap{ packet_id(),
                            next_message_num(),
                            program_id(),
                            hash_name,
                            hash_full };

    serialization::Encoder::encode( heap, &heap_buf );

    auto view = primary_message.forward_view();

    Splitted_Packets res;

    // Первый пакет содержит полноценное имя канала.
    auto first_pkbuf = heap_buf;
    first_pkbuf.write_size( 0 );
    first_pkbuf.write( channel );

    extract_and_write_tail( &view, &first_pkbuf, pk_size );
    res.push_back( first_pkbuf.result() );

    // Далее пишем только хэш канала.
    auto channel_hash = serialization::hash_of_channel( channel );
    VSerialize_Size cur_pk = 0;
    while ( !view.finished() )
    {
        auto cur_buf = heap_buf;
        cur_buf.write_size( ++cur_pk );
        cur_buf.write( channel_hash );

        extract_and_write_tail( &view, &cur_buf, pk_size );
        res.push_back( cur_buf.result() );
    }
    return res;
}
//=======================================================================================
// 1. Понимаем куда относится пакет. Есть ли его joiner
void UdpReceiver::add_packet( const VString& packet )
{
    ReadBuffer buf( packet );
    auto heap = AbstractDecoder::decode<PacketHeap>( &buf );

    // Не реагируем на сообщения, типы которых нам не интересны.
    if ( transmitters.count(heap.hash_name) == 0 ) return;

    //  Проверка корректности версии (сигнатуры) типа.
    auto our_sign_hash = type_signatures.at(heap.hash_name);
    if ( heap.hash_full != our_sign_hash )
    {
        vwarning("Type signature of hash", std::hex, heap.hash_name, "does not match."
                 " Received hash =", heap.hash_full, ", but Our hash =", our_sign_hash );
        return;
    }

    auto pk_num = buf.read_size();
    auto channel        = pk_num == 0 ? buf.read<std::string>() : "";
    auto channel_hash   = pk_num != 0 ? buf.read<channel_hash_type>()
                                      : hash_of_channel( channel );

    //  Не реагируем на ненужные нам каналы.
    if ( pk_num == 0 && !channels_observer.is_observe(channel)      ) return;
    if ( pk_num != 0 && !channels_observer.is_observe(channel_hash) ) return;


}
//=======================================================================================
PacketJoiner &UdpReceiver::joiner_for( const PacketHeap &heap )
{
    assert(false);
    PacketHeap h2;
    vdeb( heap == h2 );
    auto it = joiners.find( heap );
//    if ( it != joiners.end() ) return it->second;

//    joiners.insert( {heap,{}} );
//    return joiners.find(heap)->second;
}
//=======================================================================================
void PacketJoiner::add( ReadBuffer *buf )
{

}
//=======================================================================================
bool PacketJoiner::ready() const
{
    return !_res.empty();
}
//=======================================================================================
const VString &PacketJoiner::result() const
{
    assert( ready() );
    return _res;
}
//=======================================================================================


//=======================================================================================
void ChannelsInfoObserver::add_to_observe( const std::string &channel )
{
    _channels.insert( channel );
    _hashes.insert( hash_of_channel(channel) );
}
//=======================================================================================
void ChannelsInfoObserver::observe_all()
{
    _all = true;
}
//=======================================================================================
bool ChannelsInfoObserver::is_observe( const std::string& channel ) const
{
    return _all || _channels.count( channel );
}
//=======================================================================================
bool ChannelsInfoObserver::is_observe( const channel_hash_type& h ) const
{
    return _all || _hashes.count( h );
}
//=======================================================================================

