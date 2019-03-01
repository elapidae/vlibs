#ifndef ISHUMI_IMPL_ENCODER_H
#define ISHUMI_IMPL_ENCODER_H

#include <assert.h>
#include "ishumi_impl_signature.h"
#include "ishumi_impl_writebuffer.h"


//=======================================================================================
namespace ishumi
{
    //===================================================================================
    namespace impl
    {
        //===============================================================================
        class Encoder
        {
        public:
            template<typename T>
            static void encode( const T& val, WriteBuffer* buffer );

            template<typename T>
            static VString encode( const T& val );

        private:
            template<int idx, typename Tuple>
            struct _tuple_writer;

            template<typename T, Serial_Spec>
            struct _writer;

        }; // Encoder;

        //===== IMPLEMENTATION ==========================================================
        template<typename T>
        VString Encoder::Encoder::encode( const T& val )
        {
            WriteBuffer buf;
            encode( val, &buf );
            return buf.result();
        }
        //-------------------------------------------------------------------------------
        template<typename T>
        void Encoder::encode( const T& val, WriteBuffer* buffer )
        {
            static_assert ( is_serialize<T>(), "Type must be serializable." );
            auto tupl = Serialize<T>()( val );
            using tuple_type = decltype(tupl);
            auto constexpr idx = first_tuple_idx<tuple_type>();
            //TDI<idx> ddd;
            _tuple_writer<idx, tuple_type>::write( tupl, buffer );
        }
        //===============================================================================

        //===============================================================================
        //  tuple writer process
        template<int idx,typename Tuple>
        struct Encoder::_tuple_writer
        {
            static void write( const Tuple& tupl, WriteBuffer* buf )
            {
                constexpr auto tuple_size = std::tuple_size<Tuple>::value;

                auto val = std::get<idx>( tupl );
                using valtype = decltype( val );

                _writer<valtype,serial_spec<valtype>()>::write( val, buf );

                constexpr auto new_idx  = idx + 1 == tuple_size ? -1 : idx + 1;
                _tuple_writer<new_idx,Tuple>::write( tupl, buf );
            }
        };
        //-------------------------------------------------------------------------------
        //  tuple writer tail
        template<typename Tuple>
        struct Encoder::_tuple_writer<-1,Tuple>
        {
            static void write( const Tuple&, WriteBuffer* )
            {} // do nothing
        };
        //===============================================================================

        //===============================================================================
        //  writer simple
        template<typename T>
        struct Encoder::_writer<T,Serial_Spec::Simple>
        {
            static void write( const T& val, WriteBuffer* buf )
            {
                buf->write( val );
            }
        };
        //-------------------------------------------------------------------------------
        //  writer vector
        template<typename T>
        struct Encoder::_writer<T,Serial_Spec::Vector>
        {
            static void write( const T& val, WriteBuffer* buf )
            {
                buf->write_size( val.size() );

                using elem_type = typename T::value_type;
                using elem_writer = _writer< elem_type, serial_spec<elem_type>() >;

                for( const auto& v: val )
                    elem_writer::write( v, buf );
            }
        };
        //-------------------------------------------------------------------------------
        //  writer serialized
        template<typename T>
        struct Encoder::_writer<T,Serial_Spec::Serialized>
        {
            static void write( const T& val, WriteBuffer* buf )
            {
                encode( val, buf );
            }
        };
        //-------------------------------------------------------------------------------
        //  writer serialized
        template<typename T>
        struct Encoder::_writer<T,Serial_Spec::Tuple>
        {
            static void write( const T& val, WriteBuffer* buf )
            {
                _tuple_writer<first_tuple_idx<T>(),T>::write( val, buf );
            }
        };
        //===============================================================================
    } // namespace impl
    //===================================================================================
} // namespace ishumi
//=======================================================================================


#endif // ISHUMI_IMPL_ENCODER_H
