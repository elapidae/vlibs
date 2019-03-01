#ifndef VZTOP_DECODER_H
#define VZTOP_DECODER_H

#include "vztop_deploy.h"
#include "vztop_buffers.h"
#include <functional>

template<class T>
class TD;

namespace vztop
{
    //===================================================================================
    class AbstractDecoder
    {
    public:
        virtual void decode( ReadBuffer* ) = 0;
        virtual ~AbstractDecoder() = default;
    };
    //===================================================================================


    template<typename T>
    class Decoder : public AbstractDecoder
    {
    public:
        using ReceiveFunc = std::function<void(T&&)>;
        Decoder( ReceiveFunc rfunc ) : _rfunc(rfunc) {}

        static T do_decode( ReadBuffer* buf )
        {
            using Pck = typename
                    std::result_of<decltype(&Deploy<T>::pack)(const T&)>::type;

            return _decoder<false,0,Pck>::decode(buf);
        }

        virtual void decode( ReadBuffer *buf ) override
        {
            _rfunc( std::move(do_decode(buf)) );
        }

    private:
        ReceiveFunc _rfunc;

        //===============================================================================
        template<bool let_stop, size_t idx, typename Pck,typename ... Es>
        struct _decoder;
        //===============================================================================
        template<typename Pck,typename ... Es>
        struct _decoder<true,0,Pck,Es...>
        {
            static T decode( ReadBuffer *, Es&& ... es )
            {
                return T{ std::forward<Es>(es)... };
            }
        };
        //===============================================================================
        template<size_t idx, typename Pck,typename ... Es>
        struct _decoder<false,idx,Pck,Es...>
        {
            static T decode( ReadBuffer* buf, Es&& ... es )
            {
                using cr_valtype = typename Pck::template element<idx>::type;
                using c_valtype  = typename std::remove_reference<cr_valtype>::type;
                using valtype    = typename std::remove_const<c_valtype>::type;

                //auto val = buf->read<valtype>();
                auto val = _reader<valtype, Signature<valtype>::type()>::read( buf );

                constexpr auto new_idx  = idx + 1 == Pck::size ? 0 : idx + 1;
                constexpr auto let_stop = new_idx == 0;

                using  next = _decoder<let_stop, new_idx,Pck,Es...,valtype>;
                return next::decode( buf, std::forward<Es>(es)..., std::move(val) );
            }
        };
        //===============================================================================

        //===============================================================================
        template<typename U, typename Signature<U>::Type>
        struct _reader;

        template<typename U>
        struct _reader<U,Signature<U>::Type::Plain>
        {
            static U read( ReadBuffer* rbuf )
            {
                using c_valtype  = typename std::remove_reference<U>::type;
                using valtype    = typename std::remove_const<c_valtype>::type;
                return rbuf->read<valtype>();
            }
        };
        template<typename U>
        struct _reader<U,Signature<U>::Type::Vector>
        {
            static U read( ReadBuffer* rbuf )
            {
                using c_vectype  = typename std::remove_reference<U>::type;
                using VectorT    = typename std::remove_const<c_vectype>::type;

                using elemtype   = typename VectorT::value_type;

                auto sz = rbuf->read<uint32_t>();
                VectorT res(sz);
                for (auto& v: res)
                    v = _reader<elemtype,Signature<elemtype>::type()>::read(rbuf);

                return res;
            }
        };
        template<typename U>
        struct _reader<U,Signature<U>::Type::Deployed>
        {
            static U read( ReadBuffer* rbuf )
            {
                return Decoder<U>::do_decode( rbuf );
            }
        };
        //===============================================================================
    }; // Decoder
    //===================================================================================
} // namespace vztop
//=======================================================================================

#endif // VZTOP_DECODER_H
