#ifndef VZTOP_ENCODER_H
#define VZTOP_ENCODER_H

#include "vztop_buffers.h"
#include "vztop_deploy.h"
#include "vztop_signature.h"

template <class T>
class TD;

//=======================================================================================
namespace vztop
{
    class Encoder
    {
    public:

        //===============================================================================
        template<typename T>
        static VString full_encode( const T& val )
        {
            static const auto name_crc = Signature<T>::name_crc();
            static const auto full_crc = Signature<T>::full_crc();

            WriteBuffer buffer;

            buffer.write(name_crc);
            buffer.write(full_crc);

            encode( val, &buffer );

            return buffer.buffer();
        }
        //===============================================================================
        template<typename T>
        static void encode( const T& val, WriteBuffer* buffer )
        {
            auto pack = Deploy<T>::pack( val );
            using packtype = decltype( pack );

            _encoder<false,0,packtype>::encode( pack, buffer );
        }
        //===============================================================================


        //===============================================================================
        template<bool let_stop, size_t idx, typename Pck>
        struct _encoder;
        //===============================================================================
        //  Tail
        template<size_t idx, typename Pck>
        struct _encoder<true,idx,Pck>
        {
            static void encode( const Pck&, WriteBuffer * )
            {}
        };
        //===============================================================================
        //  Process
        template<size_t idx, typename Pck>
        struct _encoder<false,idx,Pck>
        {
            static void encode( const Pck& pack, WriteBuffer *buf )
            {
                constexpr auto pack_size = Pck::size;

                auto val = std::get<idx>(pack);
                using valtype = decltype(val);

                //buf->write( val );
                _writer<decltype(val),Signature<valtype>::type()>::write( buf, val );

                constexpr auto new_idx  = idx + 1 == pack_size ? 0 : idx + 1;
                constexpr auto end_proc = new_idx == 0;

                using next = _encoder<end_proc, new_idx, Pck>;
                return next::encode( pack, buf );
            }
        };
        //===============================================================================

        template<typename T, typename Signature<T>::Type what>
        struct _writer;

        template<typename T>
        struct _writer<T,Signature<T>::Type::Plain>
        {
            static void write( WriteBuffer* buf, const T& val )
            {
                buf->write( val );
            }
        };

        template<typename T>
        struct _writer<T,Signature<T>::Type::Vector>
        {
            static void write( WriteBuffer* buf, const T& val )
            {
                uint32_t sz = static_cast<uint32_t>( val.size() );
                buf->write( sz );

                using elem_type = typename T::value_type;
                //TD<elem_type> fff;
                using sign_type = Signature<elem_type>;
                using elem_writer = _writer<elem_type,sign_type::type()>;

                for( const auto& v: val )
                    elem_writer::write( buf, v );
            }
        };

        template<typename T>
        struct _writer<T,Signature<T>::Type::Deployed>
        {
            static void write( WriteBuffer* buf, const T& val )
            {
                encode( val, buf );
            }
        };

    }; // Encoder

} // namespace vztop
//=======================================================================================


#endif // VZTOP_ENCODER_H
