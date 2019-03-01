#ifndef SERIALIZATION_ENCODER_H
#define SERIALIZATION_ENCODER_H

#include "serialization/serialization_writebuffer.h"

//=======================================================================================
namespace serialization
{
    //===================================================================================
    class Encoder
    {
    public:
        template<typename T> static typename std::enable_if< is_serializable<T>(),
        void>::type encode( const T& val, WriteBuffer* buffer );

        template<typename T> static typename std::enable_if< !is_serializable<T>(),
        void>::type encode( const T& val, WriteBuffer* buffer );

        template<typename T>
        static VString encode( const T& val );

    private:
        template<int idx, typename Tuple>
        struct _tuple_writer;

        template<typename T, Type_Spec>
        struct _writer;

    }; // Encoder;

    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    template<typename T>
    VString Encoder::Encoder::encode( const T& val )
    {
        WriteBuffer buf;
        buf.add_to_reserve( min_size<T>() );
        encode( val, &buf );
        return buf.result();
    }
    //-----------------------------------------------------------------------------------
    template<typename T> typename std::enable_if< is_serializable<T>(),
    void>::type Encoder::encode( const T& val, WriteBuffer* buffer )
    {
        auto tuple = VSerializable<T>()( val ); // Everything for this line...
        using Tuple = decltype( tuple );
        _tuple_writer<tuple_start_idx<Tuple>(), Tuple>::write( tuple, buffer );
    }
    //-----------------------------------------------------------------------------------
    template<typename T> typename std::enable_if< !is_serializable<T>(),
    void>::type Encoder::encode( const T& val, WriteBuffer* buffer )
    {
        _writer<T,type_spec<T>()>::write( val, buffer );
    }
    //===================================================================================

    //===================================================================================
    //  tuple writer process
    template<int idx,typename Tuple>
    struct Encoder::_tuple_writer
    {
        static void write( const Tuple& tupl, WriteBuffer* buf )
        {
            auto val = std::get<idx>( tupl );
            using valtype = decltype( val );

            _writer<valtype,type_spec<valtype>()>::write( val, buf );

            _tuple_writer<tuple_next_idx<idx,Tuple>(),Tuple>::write( tupl, buf );
        }
    };
    //-----------------------------------------------------------------------------------
    //  tuple writer tail
    template<typename Tuple>
    struct Encoder::_tuple_writer<-1,Tuple>
    {
        static void write( const Tuple&, WriteBuffer* )
        {} // do nothing
    };
    //===================================================================================

    //===================================================================================
    //  writer simple
    template<typename T>
    struct Encoder::_writer<T,Type_Spec::Simple>
    {
        static void write( const T& val, WriteBuffer* buf )
        {
            buf->write( val );
        }
    };
    //-----------------------------------------------------------------------------------
    //  writer vector
    //  В начале идет перерезервирование места в буффере. Считаем реальный размер,
    //  если он окажеться больше, укажем об этом буфферу.
    template<typename T>
    struct Encoder::_writer<T,Type_Spec::Vector>
    {
        static void write( const T& val, WriteBuffer* buf )
        {
            using elem_type = typename T::value_type;

            auto real_size = size_of_size(val.size()) +
                             val.size() * min_size<elem_type>();

            if ( real_size > min_size<T>() )
                buf->add_to_reserve( real_size - min_size<T>() );

            buf->write_size( val.size() );

            using elem_writer = _writer< elem_type, type_spec<elem_type>() >;

            for( const auto& v: val )
                elem_writer::write( v, buf );
        }
    };
    //-----------------------------------------------------------------------------------
    //  writer array
    template<typename T>
    struct Encoder::_writer<T,Type_Spec::Array>
    {
        static void write( const T& val, WriteBuffer* buf )
        {
            using elem_type = typename T::value_type;
            using elem_writer = _writer< elem_type, type_spec<elem_type>() >;

            for( const auto& v: val )
                elem_writer::write( v, buf );
        }
    };
    //-----------------------------------------------------------------------------------
    //  writer serialized
    template<typename T>
    struct Encoder::_writer<T,Type_Spec::Serialized>
    {
        static void write( const T& val, WriteBuffer* buf )
        {
            encode( val, buf );
        }
    };
    //-----------------------------------------------------------------------------------
    //  writer serialized_size
    template<typename T>
    struct Encoder::_writer<T,Type_Spec::Serialized_Size>
    {
        static void write( const T& val, WriteBuffer* buf )
        {
            buf->write_size( val );
        }
    };
    //-----------------------------------------------------------------------------------
    //  writer tuple
    template<typename T>
    struct Encoder::_writer<T,Type_Spec::Tuple>
    {
        static void write( const T& val, WriteBuffer* buf )
        {
            _tuple_writer<tuple_start_idx<T>(),T>::write( val, buf );
        }
    };
    //===================================================================================
} // namespace serialization
//=======================================================================================

#endif // SERIALIZATION_ENCODER_H
