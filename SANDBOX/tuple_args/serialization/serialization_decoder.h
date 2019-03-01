#ifndef SERIALIZATION_DECODER_H
#define SERIALIZATION_DECODER_H

#include <stdexcept>
#include <functional>
#include <memory>
#include "serialization/serialization_readbuffer.h"
#include "serialization/serialization_type_traits.h"
#include "serialization/serialization_hash.h"


//=======================================================================================
namespace serialization
{
    //===================================================================================
    class AbstractDecoder
    {
    public:
        AbstractDecoder( hash_type hname, hash_type hfull );
        hash_type hash_name() const;
        hash_type hash_full() const;


        using SharedPtr = std::shared_ptr<AbstractDecoder>;

        class DecodeError : public std::runtime_error
        { public: DecodeError(const std::string& msg); };

        template<typename T> static typename std::enable_if< is_serializable<T>(),
        T>::type decode( ReadBuffer* buf );

        template<typename T> static typename std::enable_if< !is_serializable<T>(),
        T>::type decode( ReadBuffer* buf );

        template<typename T>
        static T decode( const VString& buf );

        void process( const VString& buf );

        virtual void process( ReadBuffer* buf ) = 0;
        virtual ~AbstractDecoder() = default;

    private:
        hash_type _hname, _hfull;

        template<typename T, Type_Spec>
        struct _reader;

        template<int idx, typename Res, typename Tuple, typename ... Es>
        struct _tuple_reader;
    };
    //===================================================================================
    template<typename T>
    class Decoder : public AbstractDecoder
    {
    public:
        //  Кто будет принимать сообщения.
        using ProcessFunc = std::function<void(T&&)>;

        explicit Decoder( ProcessFunc rfunc );

        virtual void process( ReadBuffer* buf ) override;

    private:
        ProcessFunc _rfunc;
    };
    //===================================================================================

    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    template<typename T> typename std::enable_if< is_serializable<T>(),
    T>::type AbstractDecoder::decode( ReadBuffer* buf )
    {
        static_assert ( is_serializable<T>(), "Type must be serializable." );

        using tuple_type = serializable_tuple_type<T>;
        auto constexpr idx = tuple_start_idx<tuple_type>();
        return _tuple_reader< idx, T, tuple_type >::read( buf );
    }
    //-----------------------------------------------------------------------------------
    template<typename T> typename std::enable_if< !is_serializable<T>(),
    T>::type AbstractDecoder::decode( ReadBuffer* buf )
    {
        return _reader< T, type_spec<T>() >::read( buf );
    }
    //-----------------------------------------------------------------------------------
    template<typename T>
    T AbstractDecoder::decode( const VString& buf )
    {
        ReadBuffer rbuf( buf );
        auto res = decode<T>( &rbuf );

        if ( !rbuf.finished() )
            throw DecodeError( "Buffer not finished." );

        return res;
    }
    //-----------------------------------------------------------------------------------
    template<typename T>
    Decoder<T>::Decoder( ProcessFunc rfunc )
        : AbstractDecoder( hash_of_name<T>(), hash_of_signature<T>() )
        , _rfunc(rfunc)
    {}
    //-----------------------------------------------------------------------------------
    template<typename T>
    void Decoder<T>::process( ReadBuffer* buf )
    {
        _rfunc( std::move(decode<T>(buf)) );
    }
    //===================================================================================

    //===================================================================================
    //  tuple reader -- tail, собственно ради этой строчки все и затевалось :).
    template< typename Res, typename Tuple, typename ... Es >
    struct AbstractDecoder::_tuple_reader<-1, Res, Tuple, Es... >
    {
        static Res read( ReadBuffer*, Es&& ... es )
        {
            return Res{ std::forward<Es>(es)... };
        }
    };
    //-----------------------------------------------------------------------------------
    //  tuple reader -- process
    template< int idx, typename Res, typename Tuple, typename ... Es >
    struct AbstractDecoder::_tuple_reader
    {
        static Res read( ReadBuffer* buf, Es&& ... es )
        {
            using val_type = typename std::tuple_element<idx,Tuple>::type;
            auto val = _reader<val_type, type_spec<val_type>()>::read( buf );

            constexpr auto tuple_sz = tuple_size<Tuple>();
            constexpr auto new_idx  = tuple_next_idx<idx, Tuple>();
            using  next = _tuple_reader< new_idx, Res, Tuple, Es..., val_type >;

            return next::read( buf, std::forward<Es>(es)..., std::move(val) );
        }
    };
    //===================================================================================

    //===================================================================================
    //  reader simple
    template<typename T>
    struct AbstractDecoder::_reader<T,Type_Spec::Simple>
    {
        static T read( ReadBuffer* rbuf )
        {
            return rbuf->read<T>();
        }
    };
    //-----------------------------------------------------------------------------------
    //  reader array
    template<typename T>
    struct AbstractDecoder::_reader<T,Type_Spec::Array>
    {
        static T read( ReadBuffer* rbuf )
        {
            using elem_type = typename T::value_type;
            using reader = _reader< elem_type, type_spec<elem_type>() >;

            T res;
            for ( auto& v: res )
                v = reader::read( rbuf );

            return res;
        }
    };
    //-----------------------------------------------------------------------------------
    //  reader vector
    template<typename T>
    struct AbstractDecoder::_reader<T,Type_Spec::Vector>
    {
        static T read( ReadBuffer* rbuf )
        {
            using elem_type = typename T::value_type;
            using reader = _reader< elem_type, type_spec<elem_type>() >;

            auto sz = rbuf->read_size();
            T res(sz);
            for ( auto& v: res )
                v = reader::read( rbuf );

            return res;
        }
    };
    //-----------------------------------------------------------------------------------
    //  reader serialized
    template<typename T>
    struct AbstractDecoder::_reader<T,Type_Spec::Serialized>
    {
        static T read( ReadBuffer* rbuf )
        {
            return AbstractDecoder::decode<T>( rbuf );
        }
    };
    //-----------------------------------------------------------------------------------
    //  reader serialized size
    template<typename T>
    struct AbstractDecoder::_reader<T,Type_Spec::Serialized_Size>
    {
        static T read( ReadBuffer* rbuf )
        {
            return T( rbuf->read_size() );
        }
    };
    //-----------------------------------------------------------------------------------
    //  reader tuple
    template<typename T>
    struct AbstractDecoder::_reader<T,Type_Spec::Tuple>
    {
        static T read( ReadBuffer* rbuf )
        {
            constexpr auto idx = tuple_start_idx<T>();
            return AbstractDecoder::_tuple_reader<idx,T,T>::read( rbuf );
        }
    };
    //===================================================================================
} // namespace serialization
//=======================================================================================


#endif // SERIALIZATION_DECODER_H
