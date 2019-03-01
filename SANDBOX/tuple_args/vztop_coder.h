#ifndef VZTOP_CODER_H
#define VZTOP_CODER_H

#include <tuple>
#include <assert.h>
#include "vstring.h"
#include "vztop_buffers.h"

#include "vztop_deploy.h"
//#include <utility>

//=======================================================================================
namespace vztop
{
    //===================================================================================
    template< typename Res, typename Pck >
    struct Coder2
    {
        static Res unpack( const Pck& pack )
        {
            return _unpacker<false,0>::_unpack( pack );
        }

        static void raw_pack( const Pck& pack, WriteBuffer* buf )
        {
            return _packer<false,0>::_pack( pack, buf );
        }

        static WriteBuffer full_pack( const Pck& pack )
        {
            WriteBuffer res;
            raw_pack( pack, &res );
            return res;
        }

        //===============================================================================
        template<bool let_stop, size_t idx>
        struct _packer
        {
            //void pack( WriteBuffer *buf )
            //{ assert(false && "This method has not be instanced."); }
        };
        //===============================================================================
        template<size_t idx>
        struct _packer<true,idx>
        {
            static void _pack( const Pck&, WriteBuffer * )
            {}
        };
        //===============================================================================
        template<size_t idx>
        struct _packer<false,idx>
        {
            static void _pack( const Pck& pack, WriteBuffer *buf )
            {
                constexpr auto pack_size = Pck::size;

                auto val = std::get<idx>(pack);
                //using valtype = typename Pck::template element<idx>::type;

                buf->write( val );

                constexpr auto new_idx  = idx + 1 == pack_size ? 0 : idx + 1;
                constexpr auto end_proc = new_idx == 0;

                using mypack = _packer<end_proc, new_idx>;
                return mypack::_pack( pack, buf );
            }
        };
        //===============================================================================

        //===============================================================================
        template<bool EndProc, size_t idx, typename ... Es>
        struct _unpacker
        {
            static Res _unpack( const Pck& )
            { assert(false && "This method has not be instanced."); }
        };
        //===============================================================================
        template< typename ... Es >
        struct _unpacker<true, 0, Es...>
        {
            static Res _unpack( const Pck&, Es&& ... es )
            {
                return Res{ std::forward<Es>(es)... };
            }
        };
        //===============================================================================
        template<size_t idx, typename ... Es>
        struct _unpacker<false, idx, Es...>
        {
            static Res _unpack( const Pck& pack, Es&& ... es )
            {
                constexpr auto pack_size = Pck::size;

                auto val = std::get<idx>(pack);
                using valtype = typename Pck::template element<idx>::type;

                constexpr auto new_idx  = idx + 1 == pack_size ? 0 : idx + 1;
                constexpr auto end_proc = new_idx == 0;

                using nextu = _unpacker<end_proc, new_idx, Es..., valtype>;
                return nextu::_unpack( pack, std::forward<Es>(es)..., std::move(val) );
            }
        };
        //===============================================================================

    protected:
        virtual ~Coder2() = default;
    };

    //===================================================================================
//    template<typename ... Args>
//    auto To_Tuple(Args...args) -> std::tuple<Args...>
//    {
//        return std::make_tuple(args...);
//    }
    //===================================================================================
//    template<typename Res>
//    struct Signature
//    {
//        void pack( const Res& );
//    };


    //===================================================================================
//    template< typename Res, typename ... Args >
//    struct Coder
//    {
//        //-------------------------------------------------------------------------------

//        using Tuple = std::tuple<Args...>;
//        enum   { TupleSize = std::tuple_size<decltype(Tuple())>() };
//        //-------------------------------------------------------------------------------

//        Coder() { static_assert(TupleSize > 0, ""); }
//        //-------------------------------------------------------------------------------

//        static Res from_args ( Args&& ... args  );
//        static Res from_tuple( const Tuple& tup );
//        //-------------------------------------------------------------------------------

//        virtual void to_buffer( WriteBuffer *buf, const Res& val ) = 0;


//        static const char* type_name() { return Signature<Res>::name(); }

//        //===============================================================================
//        template<bool EndProc, size_t idx, typename ... Es>
//        struct _extractor
//        {
////            static Res ex( const Tuple& )
////            {
//////                vdeb << "gen realize, something wrong...";
//////                assert(false);
////            }
//        };
//        //===============================================================================
//        template< typename ... Es >
//        //template<typename Res, typename ... Es>
//        struct _extractor<true, 0, Res, Es...>
//        {
//            static Res ex( const Tuple&, Es&& ... es )
//            { return from_args( std::forward<Es>(es)... ); }
//        };
//        //===============================================================================
//        template<size_t idx, typename ... Es>
//        //template<size_t idx, typename Res, typename ... Es>
//        struct _extractor<false, idx, Res, Es...>
//        {
//            static Res ex( const Tuple& tup, Es&& ... es )
//            {
//                auto val = std::get<idx>(tup);
//                using valtype = typename std::tuple_element<idx, Tuple>::type;

//                constexpr auto new_idx  = idx + 1 == TupleSize ? 0 : idx + 1;
//                constexpr auto end_proc = new_idx == 0;

//                using myEx = _extractor<end_proc, new_idx, Res, Es..., valtype>;
//                return myEx::ex( tup, std::forward<Es>(es)..., std::move(val) );
//            }
//        };
//        //===============================================================================
//    protected:
//        virtual ~Coder() = default;
//    }; // Coder
    //===================================================================================


    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
//    template< typename Res, typename ... Args >
//    //template<typename ... Args>
//    //template<typename Res>
//    Res Coder<Res,Args...>::from_args( Args&& ... args )
//    {
//        return Res{ std::forward<Args>(args)... };
//    }
//    //===================================================================================
//    template< typename Res, typename ... Args >
//    //template<typename ... Args>
//    //template<typename Res>
//    Res Coder<Res,Args...>::from_tuple( const Tuple& tup )
//    {
//        return _extractor<false,0,Res>::ex( tup );
//    }
    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
} // namespace vztop
//=======================================================================================



#endif // VZTOP_CODER_H
