#ifndef INCOMINGMESSAGE_H
#define INCOMINGMESSAGE_H

#include <unordered_map>
#include "json11.h"
#include "vsignal.h"
#include "vbytearray.h"

#include "message.h"
#include "binarydatajoiner.h"

//=======================================================================================
namespace ii
{
    //===================================================================================

    class IncomingMessage : Message
    {
    public:
        class Error : public std::runtime_error
        { public: Error(const std::string &e) :runtime_error(e) {} };

        class PacketsReceiver;

        std::string target()    const;
        int32_t     msg_id()    const;

        const VByteArray &bin() const;

        int meta_int    ( const std::string &label ) const;
        int meta_double ( const std::string &label ) const;
        int meta_string ( const std::string &label ) const;
        int meta_bool   ( const std::string &label ) const;

        const json11::Json::object & meta_root() const;
        const json11::Json::object & meta_object ( const std::string &label ) const;
        const json11::Json::array  & meta_array  ( const std::string &label ) const;

    private:
        class _Joiner;
        class _PacketParser;

        //IncomingMessage( json11::Json && j );
        IncomingMessage( const json11::Json::object & o, const VByteArray & b );

        json11::Json::object _obj;
        VByteArray           _bin;
        int32_t              _msg_id;

        //friend class PacketsReceiver;
        //bool _is_fragmented() const;
        //bool _is_leading()  const;
        //void _set_data( VByteArray && data );
        //int  _json_bin_size() const;
        //int _fragment_num()   const;
        //int _fragment_count() const;
    };

    //===================================================================================
    // Задача: Собрать одно сообщение из приходящих кусочков.
    // Эта же задача примерно решалась в классе BinaryDataJoiner, который, по хорошему,
    // надо срастить с этим классом.
    class IncomingMessage::_Joiner
    {
    public:
        _Joiner(int32_t my_msgid , int frags_count);

        int32_t msg_id() const;

        void append(const _PacketParser &packet );

        bool is_ready() const;

        IncomingMessage get_incoming_message();

        steady_clock_t last_usage() const;

    private:
        int32_t _msg_id;
        json11::Json::object _obj;
        bool _has_leading = false;
        BinaryDataJoiner _djoiner;
    };

    //===================================================================================
    // Задача класса: при приеме нового пакета, выделить из него json и bin,
    // и интерпретировать ключевые поля. По сути, начальная интерпретация входных данных.
    class IncomingMessage::_PacketParser
    {
    public:
        _PacketParser( const VByteArray &packet );

        int32_t msg_id() const;

        bool is_leading() const;

        bool is_fragmented() const;
        int  fragment_count() const;
        int fragment_num() const;

        // Можно вызывать только если пакет не фрагментирован.
        IncomingMessage get_incoming() const;

        const VByteArray & get_bin() const;
        const json11::Json::object & get_json() const;

    private:
        VByteArray bin;
        json11::Json::object obj;

        void _check_adequates();

        int32_t mid;
        int     frag_count;
        int     frag_num;
        bool    has_target;
        int     json_bin_size;
    };

    //===================================================================================
    class IncomingMessage::PacketsReceiver
    {
    public:
        VSignal<IncomingMessage> received;

        PacketsReceiver( std::chrono::milliseconds expire_time
                                                    = std::chrono::milliseconds(2000) );

        void append( const VByteArray &packet );

        void clean_expired();

    private:
        std::unordered_map<int32_t, _Joiner>  _joiners;

        //void _prepare_msg(IncomingMessage && msg , bool leading, int32_t msg_id);

        //std::unordered_map<int32_t, IncomingMessage>  _messages;
        //std::unordered_map<int32_t, BinaryDataJoiner> _datas;
        std::chrono::milliseconds _expire_time;
    };

} // namespace ii
//=======================================================================================


#endif // INCOMINGMESSAGE_H
