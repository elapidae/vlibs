#include "mainwindow.h"
#include <QApplication>

#include <ishumi_serialize.h>
#include "vstring.h"
#include "vlog_pretty.h"
#include <assert.h>

#include <type_traits>
#include <vector>
#include <type_traits>
#include "ishumi_impl_encoder.h"
#include "ishumi_impl_decoder.h"

#include "vcat_containers.h"

template<typename T> class TD;

//using namespace vztop;


//=======================================================================================
struct ABC
{
    int  a;
    uint b;
    char c;
};
namespace ishumi
{
    static constexpr auto _reduce_ABC = []( const ABC& val )
    {
        return std::make_tuple( val.a, val.b, val.c );
    };

    template<>
    struct Serialize< ABC >
    {
        static std::string id()
        { return extract_serialize_typename(__PRETTY_FUNCTION__) +
                 "ver. 1.0, 2018-10-06 by Elapidae";
        }

        result_of_arg1<decltype(_reduce_ABC), ABC>
        operator()( const ABC& val )
        { return _reduce_ABC(val); }
    };
}
//=======================================================================================



//=======================================================================================
namespace ishumi
{
    //===================================================================================
    template<typename T> struct Serialize;
    //===================================================================================
    constexpr auto _reduce_VPointF = []( const VPointF& val )
    {
        return std::make_tuple( val.x(), val.y() );
    };
    //===================================================================================
    template<>
    struct Serialize< VPointF >
    {
        static constexpr const char* id()
        { return "VPointF ver. 1.0 2018-10-06 by Elapidae"; }

        result_of_arg1< decltype(_reduce_VPointF), VPointF >
        operator()( const VPointF& val )
        { return _reduce_VPointF(val); }
    };
    //===================================================================================
} // namespace ishumi
//=======================================================================================


struct MM
{
    std::vector<int> vi;
    std::string str;
    std::vector<std::string> vs;
    std::tuple<int,char> tic;
    std::vector<VPointF> vp;
    std::tuple<> sss;
    std::array<int,5> arr5;
};
//=======================================================================================
namespace ishumi
{
    //===================================================================================
    static constexpr auto _pack_MM = []( const MM& val )
    {
        return make_tuple( val.vi,
                           val.str,
                           val.vs,
                           val.tic,
                           val.vp,
                           val.sss );

        //return make_tuple( val.vi, val.str, val.vs, val.tic );
    };
    //===================================================================================
    template<>
    struct Serialize<MM>
    {
        static constexpr const char* id()
        {
            return "MM version 1.0 by Elapidae";
        }

        result_of_arg1<decltype(_pack_MM),MM>
        operator()( const MM& val )
        {
            return _pack_MM( val );
        }
    };
    //===================================================================================
}
//=======================================================================================


#include "ishumi_impl_signature.h"
using namespace ishumi;
using namespace ishumi::impl;

struct PV1
{
    std::vector<VPointF> v;
};

//=======================================================================================
namespace ishumi
{
    //===================================================================================
    static constexpr auto _pack_PV = []( const PV1& val )
    {
        return make_tuple( val.v );
        //return make_tuple( val.vi, val.str, val.vs, val.tic );
    };
    //===================================================================================
    template<>
    struct Serialize<PV1>
    {
        static std::string id()
        {
            return extract_serialize_typename(__PRETTY_FUNCTION__)
                   + "ver. 1";

        }

        result_of_arg1<decltype(_pack_PV),PV1>
        operator()( const PV1& val )
        {
            return _pack_PV( val );
        }
    };
    //===================================================================================
}
//=======================================================================================


struct AB
{
    int a;
    std::string b;
};

template<typename Res, typename First, typename ... Es>
std::tuple<First,Es...> tupline()
{
    Res{ First(),Es()... };
}

//void fff() {}
void ff( std::vector<double> ) {}
void ff( int ) { vdeb << 42; }
//// на какую функцию указывает pf1?
//auto ( *pf1 )( int ) = &ff;
//using pf2 = decltype( ff );
//typedef decltype( &ff ) pf3;

#include "serialization/serialization_type_traits.h"
//using namespace ii;


template<typename T> static constexpr
size_t tuple_size()
{
    return std::tuple_size<T>::value;
}

//template<typename T>
//struct _is_array : std::false_type {};
//template<typename T>
//struct _is_array<std::array<T,tuple_size<>>,std::tuple_size<std::array<T>>::value> : std::true_type {};

template<typename T> static constexpr
bool is_array()
{
    return tuple_size<T>() >= 0;
}
//===============================================================================


int main( int argc, char *argv[] )
{

    return 0;

    (void)argc; (void)argv;
}
