#ifndef ISHUMI_IMPL_DECODER_H
#define ISHUMI_IMPL_DECODER_H

#include "ishumi_impl_signature.h"
#include "ishumi_impl_readbuffer.h"

//=======================================================================================
namespace ishumi
{
    //===================================================================================
    namespace impl
    {
        //===============================================================================
        class AbstractDecoder
        {
        public:
            class DecodeError : public std::runtime_error
            { public: DecodeError(const std::string& msg); };


            template<typename T>
            static T decode( ReadBuffer* buf );

            template<typename T>
            static T decode( const VString& buf );

            virtual void process( const VString& buf ) = 0;
            virtual ~AbstractDecoder() = default;

        private:
            template<typename U, Serial_Spec>
            struct _reader;

            template<int idx, typename Res, typename Tuple, typename ... Es>
            struct _tuple_reader;
        };
        //===============================================================================
        template<typename T>
        class Decoder : public AbstractDecoder
        {
        public:
            //  Кто будет принимать сообщения.
            using ProcessFunc = std::function<void(T&&)>;
            explicit Decoder( ProcessFunc rfunc ) : _rfunc(rfunc) {}

            virtual void process( const VString& buf ) override;

        private:
            ProcessFunc _rfunc;
        };

        //===== IMPLEMENTATION ==========================================================
        template<typename T>
        T AbstractDecoder::decode( ReadBuffer* buf )
        {
            static_assert ( is_serialize<T>(), "Type must be serializable." );

            using tuple_type = serialize_tuple_type<T>;
            auto constexpr idx = first_tuple_idx<tuple_type>();
            return _tuple_reader< idx, T, tuple_type >::read( buf );
        }
        //-------------------------------------------------------------------------------
        template<typename T>
        T AbstractDecoder::decode( const VString& buf )
        {
            ReadBuffer rbuf( buf );
            auto res = decode<T>( &rbuf );

            if ( !rbuf.finished() )
                throw std::logic_error( "Buffer not finished." );

            return res;
        }
        //-------------------------------------------------------------------------------
        template<typename T>
        void Decoder<T>::process( const VString& buf )
        {
            ReadBuffer rbuf( buf );
            _rfunc( std::move(decode<T>(&rbuf)) );
        }

        //===============================================================================

        //===============================================================================
        //  decoder tail, собственно ради этой строчки все и затевалось :).
        template< typename Res, typename Tuple, typename ... Es>
        struct AbstractDecoder::_tuple_reader<-1,Res,Tuple,Es...>
        {
            static Res read( ReadBuffer*, Es&& ... es )
            {
                return Res{ std::forward<Es>(es)... };
            }
        };
        //-------------------------------------------------------------------------------
        //  decoder process        
        template<int idx, typename Res, typename Tuple, typename ... Es>
        struct AbstractDecoder::_tuple_reader
        {
            static Res read( ReadBuffer* buf, Es&& ... es )
            {
                using val_type = typename std::tuple_element<idx,Tuple>::type;
                auto val = _reader<val_type, serial_spec<val_type>()>::read( buf );

                constexpr auto tuple_sz = std::tuple_size<Tuple>::value;
                constexpr auto new_idx  = idx + 1 == tuple_sz ? -1 : idx + 1;
                using  next = _tuple_reader< new_idx, Res, Tuple, Es..., val_type >;

                return next::read( buf, std::forward<Es>(es)..., std::move(val) );
            }
        };
        //===============================================================================

        //===============================================================================
        //  reader simples
        template<typename T>
        struct AbstractDecoder::_reader<T,Serial_Spec::Simple>
        {
            static T read( ReadBuffer* rbuf )
            {
                return rbuf->read<T>();
            }
        };
        //-------------------------------------------------------------------------------
        //  reader vector
        template<typename T>
        struct AbstractDecoder::_reader<T,Serial_Spec::Vector>
        {
            static T read( ReadBuffer* rbuf )
            {
                using elem_type = typename T::value_type;

                auto sz = rbuf->read_size();
                T res(sz);
                for ( auto& v: res )
                    v = _reader<elem_type,serial_spec<elem_type>()>::read( rbuf );

                return res;
            }
        };
        //-------------------------------------------------------------------------------
        //  reader serialized
        template<typename T>
        struct AbstractDecoder::_reader<T,Serial_Spec::Serialized>
        {
            static T read( ReadBuffer* rbuf )
            {
                return AbstractDecoder::decode<T>( rbuf );
            }
        };
        //-------------------------------------------------------------------------------
        //  reader tuple
        template<typename T>
        struct AbstractDecoder::_reader<T,Serial_Spec::Tuple>
        {
            static T read( ReadBuffer* rbuf )
            {
                constexpr auto idx = first_tuple_idx<T>();
                return AbstractDecoder::_tuple_reader<idx,T,T>::read( rbuf );
            }
        };
        //===============================================================================
    } // namespace impl
    //===================================================================================
} // namespace ishumi
//=======================================================================================

#endif // ISHUMI_IMPL_DECODER_H
