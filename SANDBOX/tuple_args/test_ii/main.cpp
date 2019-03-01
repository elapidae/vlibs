#include <iostream>

#include "vlog_pretty.h"
#include "vstring.h"
#include "serialization/serialization_type_traits.h"
#include "vserializable.h"
#include "serialization/serialization_encoder.h"
#include "serialization/serialization_decoder.h"

#include "ii_udp_packets.h"

#include "vcat_containers.h"
#include "serialization/serialization_type_compare.h"
#include "serialization/serialization_hash.h"

#include "gtest/gtest.h"

#include "transmitterbychannels.h"

using namespace serialization;


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
//#pragma GCC diagnostic ignored "-Wweak-vtables"
//#pragma GCC diagnostic ignored "-Wshorten-64-to-32"


class II_Serialization: public testing::Test
{};

//=======================================================================================
TEST_F( II_Serialization, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( II_Serialization, string_traits )
{
    EXPECT_EQ( is_string<std::string>(), true );
    EXPECT_EQ( is_string<int>(), false );
}
//=======================================================================================
TEST_F( II_Serialization, simple_traits )
{
    EXPECT_TRUE( is_simple<bool>() );
    EXPECT_FALSE( is_arithmetic<bool>() );

    EXPECT_EQ( is_simple<int>(), true );
    EXPECT_EQ( is_simple<uint>(), true );
    EXPECT_EQ( is_simple<float>(), true );
    EXPECT_EQ( is_simple<double>(), true );
    EXPECT_EQ( is_simple<std::string>(), true );

    EXPECT_EQ( is_simple<std::vector<int>>(), false );
    EXPECT_EQ( is_simple<std::tuple<>>(), false );
    EXPECT_EQ( is_simple<std::tuple<int>>(), false );
    EXPECT_EQ( (is_simple<std::array<int,0>>()), false );
    EXPECT_EQ( (is_simple<std::array<uint,2>>()), false );
    //EXPECT_EQ( is_simple<std::>(), false );
}
//=======================================================================================
TEST_F( II_Serialization, vector_traits )
{
    EXPECT_TRUE( is_vector<std::vector<uint>>() );
    EXPECT_FALSE( is_vector<std::string>() );
    EXPECT_FALSE( is_vector<int>() );
}
//=======================================================================================
TEST_F( II_Serialization, tuple_traits )
{
    EXPECT_TRUE( (has_tuple_size<std::array<int,3>>()) );
    EXPECT_TRUE( (has_tuple_size<std::array<int,0>>()) );

    EXPECT_TRUE( has_tuple_size<std::tuple<>>() );
    EXPECT_TRUE( has_tuple_size<std::tuple<int>>() );
    EXPECT_TRUE( (has_tuple_size<std::tuple<int,uint>>()) );

    EXPECT_FALSE( has_tuple_size<std::string>() );
    EXPECT_FALSE( has_tuple_size<int>() );

    EXPECT_EQ( (tuple_start_idx<std::tuple<>>()), -1 );
    EXPECT_EQ( (tuple_start_idx<std::tuple<int>>()), 0 );
    EXPECT_EQ( (tuple_start_idx<std::tuple<int,uint>>()), 0 );
}
//=======================================================================================

TEST_F( II_Serialization, containers_traits )
{
    EXPECT_TRUE( (has_value_type<std::array<int,3>>()) );
    EXPECT_TRUE( (has_size_type<std::array<int,3>>()) );

    EXPECT_TRUE( (has_value_type<std::vector<int>>()) );
    EXPECT_TRUE( (has_size_type<std::vector<int>>()) );

    EXPECT_TRUE( (has_value_type<std::string>()) );
    EXPECT_TRUE( (has_size_type<std::string>()) );

    EXPECT_FALSE( (has_value_type<int>()) );
    EXPECT_FALSE( (has_size_type<int>()) );
    EXPECT_FALSE( (has_value_type<std::tuple<int>>()) );
    EXPECT_FALSE( (has_size_type<std::tuple<int>>()) );
}
//=======================================================================================

TEST_F( II_Serialization, tuple_vs_array )
{
    using t0 = std::tuple<>;
    using t1 = std::tuple<int>;
    EXPECT_TRUE( is_tuple<t0>() );
    EXPECT_TRUE( is_tuple<t1>() );
    EXPECT_FALSE( is_array<t0>() );
    EXPECT_FALSE( is_array<t1>() );

    using arr = std::array<int,4>;
    EXPECT_TRUE( is_array<arr>() );
    EXPECT_FALSE( is_tuple<arr>() );

    using vec = std::vector<int>;
    EXPECT_FALSE( is_array<vec>() );
    EXPECT_FALSE( is_tuple<vec>() );
}
//=======================================================================================

//=======================================================================================
struct ABC
{
    ABC(int aa,uint bb,char cc) : a(aa), b(bb), c(cc) {}

    int  a;
    uint b;
    char c;
};
//=======================================================================================
//===================================================================================
static constexpr auto _tupline_ABC = []( const ABC &val )
{
    return std::make_tuple( val.a, val.b, val.c );
};
//-----------------------------------------------------------------------------------
template<> struct VSerializable<ABC>
{
    //  Этот метод можно не писать.
    //static constexpr const char* label()
    //{ return "ver 1.0, 09-10-2018, by Elapidae"; }

    result_of_lambda< decltype(_tupline_ABC), ABC >
    operator()( const ABC& val )
    { return _tupline_ABC(val); }
};
//===================================================================================


TEST_F( II_Serialization, serializable_traits )
{
    using t = serializable_tuple_type<ABC>;
    EXPECT_EQ( tuple_size<t>(), 3 );

    EXPECT_EQ( serializable_label<VSerialize_Example>(),
               "(ver 1.0, 09-10-2018, by Elapidae)");
    EXPECT_EQ( serializable_label<ABC>(), "()" );

    EXPECT_EQ( serializable_type_name<ABC>(), "ABC");
    EXPECT_EQ( serializable_type_name<VSerialize_Example>(), "VSerialize_Example");

    EXPECT_TRUE( is_serializable<ABC>() );
    EXPECT_FALSE( is_serializable<t>() );

//    vdeb << serializable_type_name<AnyT<int>>();
}
//=======================================================================================

//=======================================================================================
struct ABCD : ABC
{
    ABCD (int a, uint b, char c, VSerialize_Example e)
    {
        ABC::a = a;
        ABC::b = b;
        ABC::c = c;
        ex = e;
    }
    VSerialize_Example ex;
};
//=======================================================================================
//===================================================================================
static constexpr auto _tupline_ABCD = []( const ABCD &val )
{
    return std::make_tuple( val.a, val.b, val.c, val.ex );
};
//-----------------------------------------------------------------------------------
template<> struct VSerializable<ABCD>
{
    static VString label() { return "label of ABCD"; }

    result_of_lambda< decltype(_tupline_ABCD), ABCD >
    operator()( const ABCD& val )
    { return _tupline_ABCD(val); }
};
//===================================================================================


TEST_F( II_Serialization, type_signatures )
{
    EXPECT_EQ( type_signature<char>(), "char8" );

    EXPECT_EQ( type_signature<int8_t>(), "int8" );
    EXPECT_EQ( type_signature<uint8_t>(), "uint8" );
    EXPECT_EQ( type_signature<signed char>(), "int8" );
    EXPECT_EQ( type_signature<unsigned char>(), "uint8" );

    EXPECT_EQ( type_signature<int16_t>(), "int16" );
    EXPECT_EQ( type_signature<uint16_t>(), "uint16" );

    EXPECT_EQ( type_signature<int32_t>(), "int32" );
    EXPECT_EQ( type_signature<uint32_t>(), "uint32" );

    EXPECT_EQ( type_signature<int64_t>(), "int64" );
    EXPECT_EQ( type_signature<uint64_t>(), "uint64" );

    EXPECT_EQ( type_signature<float>(), "float32" );
    EXPECT_EQ( type_signature<double>(), "float64" );

    EXPECT_EQ( type_signature<std::string>(), "string" );
    EXPECT_EQ( type_signature<VString>(), "string" );

    EXPECT_EQ( (type_signature<std::vector<int32_t>>()), "vector<int32>" );

    EXPECT_EQ( (type_signature<std::array<int32_t,8>>()), "[int32,8]" );
    EXPECT_EQ( (type_signature<std::array<std::vector<int32_t>,8>>()),
               "[vector<int32>,8]" );

    EXPECT_EQ( (type_signature<std::tuple<>>()), "{}" );
    EXPECT_EQ( (type_signature<std::tuple<char,std::string>>()), "{char8,string}" );

    EXPECT_EQ( (type_signature<VSerialize_Example>()),
               "VSerialize_Example"
               "(ver 1.0, 09-10-2018, by Elapidae)"
               "{int32,uint32,char8}" );

    EXPECT_EQ( (type_signature<ABCD>()),
               "ABCD(label of ABCD){int32,uint32,char8,VSerialize_Example"
                                                "(ver 1.0, 09-10-2018, by Elapidae)"
                                                "{int32,uint32,char8}}" );
    //    EXPECT_EQ( (type_signature<>()), "" );
}
//=======================================================================================

struct Collision
{
    int i;
    uint u;
};
//=======================================================================================
//===================================================================================
static constexpr auto _tupline_Collision = []( const Collision &val )
{
    return std::make_tuple( val.u, val.i );
};
//-----------------------------------------------------------------------------------
template<> struct VSerializable<Collision>
{
    static VString label() { return "label of Collision"; }

    result_of_lambda< decltype(_tupline_Collision), Collision >
    operator()( const Collision& val )
    { return _tupline_Collision(val); }
};
//=======================================================================================


TEST_F( II_Serialization, min_sizes )
{
    EXPECT_EQ( min_size<int>(), sizeof(int) );
    EXPECT_EQ( (min_size<std::array<char,9>>()), 9 );
    EXPECT_EQ( (min_size<std::array<uint16_t,9>>()), 18 );

    EXPECT_TRUE( (min_size<std::string>()) == 1 );
    EXPECT_TRUE( (min_size<std::vector<int>>()) == 1 );
    EXPECT_EQ( (min_size<ABC>()), (min_size<serializable_tuple_type<ABC>>()) );

//    EXPECT_EQ( (min_size<>()), sizeof() );
}
//=======================================================================================

TEST_F( II_Serialization, enc_dec_simple )
{
    ABC abc{1,2,3};
    auto res = Encoder::encode( abc );
    EXPECT_EQ( res.to_Hex(), "01 00 00 00 02 00 00 00 03" );

    ABCD abcd{ 1, 2, 3, VSerialize_Example{-42, 42, '!'} };
    res = Encoder::encode( abcd );
    EXPECT_EQ( res.to_Hex(), "01 00 00 00 02 00 00 00 03 D6 FF FF FF 2A 00 00 00 21" );

    auto rabcd = AbstractDecoder::decode<ABCD>( res );
    //EXPECT_TRUE( rabcd.a, abcd.a );
    EXPECT_EQ( rabcd.a, abcd.a );
    EXPECT_EQ( rabcd.b, abcd.b );
    EXPECT_EQ( rabcd.c, abcd.c );

//    EXPECT_EQ( (min_size<>()), sizeof() );
}
//=======================================================================================

struct SSize
{
    VSerialize_Size sz;
};

template<>
struct VSerializable<SSize>
{
    std::tuple<VSerialize_Size>
    operator()( const SSize &ss )
    { return std::make_tuple(ss.sz); }
};


TEST_F( II_Serialization, serial_size )
{
//    vdeb << is_serialize_size<VSerialize_Size>();
    auto ss = SSize{ {1000000000} };
    auto str = Encoder::encode( ss );

    auto ss_dec = AbstractDecoder::decode<SSize>( str );
    EXPECT_EQ( ss.sz, ss_dec.sz );

    VSerialize_Size sz2 = 1234567890;
    str = Encoder::encode(sz2);
    vdeb << str.to_Hex();
    auto rsz2 = AbstractDecoder::decode<VSerialize_Size>( str );
    EXPECT_EQ( sz2, rsz2 );
}

//=======================================================================================


//=======================================================================================
struct Test0
{
    int64_t i64;
    uint16_t u16;
    bool b; // неициированный bool это что-то...
    char c;
    std::vector<float> vf;

//    bool operator == (const Test0& rhs) const
//    {
//        int b1 = b ? 1 : 0;
//        int b2 = rhs.b ? 1 : 0;
////        bool bb1 = b;
////        bool bb2 = rhs.b;
////        vdeb << (i64 == rhs.i64);
////        vdeb << (u16 == rhs.u16);
////        vdeb << b << rhs.b << (bool(b) == bool(rhs.b)) << (b1 == b2) << (bb1 == bb2);
////        vdeb << (c   == rhs.c);
////        vdeb << (vf  == rhs.vf);

//        return i64 == rhs.i64 &&
//               u16 == rhs.u16 &&
//               b1  == b2      &&
//               c   == rhs.c   &&
//               vf  == rhs.vf;
//    }
//    bool operator != (const Test0& rhs) const
//    { return !(*this == rhs); }
};
//---------------------------------------------------------------------------------------
static constexpr auto _tupline_Test0 = []( const Test0 &val )
{
    return std::make_tuple( val.i64,
                            val.u16,
                            val.b,
                            val.c,
                            val.vf );
};
//---------------------------------------------------------------------------------------
template<>
struct VSerializable<Test0>
{
    //static std::string label() { return "test0 description"; }
    std::result_of<decltype(_tupline_Test0)(Test0)>::type
    operator()( const Test0& val )
    { return _tupline_Test0(val); }
};
//=======================================================================================
struct Test1
{
    std::array<Test0,5> arr;
    std::vector<double> vd;
    std::tuple<> t0;
    std::tuple<int32_t,Test0,float,char,bool> t5;
    std::tuple<int32_t,Test0,float,char,bool> t5_2;

//    bool operator == (const Test1& rhs) const
//    {
//        for (int i = 0; i < 5; ++i )
//            if ( arr[i] != rhs.arr[i] )
//            {
//                vdeb << i;
//                return false;
//            }

//        return vd   == rhs.vd   &&
//               t0   == rhs.t0   &&
//               t5   == rhs.t5   &&
//               t5_2 == rhs.t5_2;
//    }
};
static constexpr auto _tupline_Test1 = []( const Test1 &val )
{
    return std::make_tuple( val.arr,
                            val.vd,
                            val.t0,
                            val.t5,
                            val.t5_2 );
};
//---------------------------------------------------------------------------------------
template<>
struct VSerializable<Test1>
{
    //static std::string label() { return "Test1 description"; }
    std::result_of<decltype(_tupline_Test1)(Test1)>::type
    operator()( const Test1& val )
    { return _tupline_Test1(val); }
};
//=======================================================================================

TEST_F( II_Serialization, test0 )
{
    Test0 t0{123456789, 321, true, '!', {1.2f, 3.4f, 5.6f} };
    Test1 t1;
    auto t0_str = Encoder::encode( t0 );
    auto t0_dec = AbstractDecoder::decode<Test0>( t0_str );
    EXPECT_TRUE( t0 == t0_dec );


    auto t1_str = Encoder::encode( t1 );
    auto t1_dec = AbstractDecoder::decode<Test1>( t1_str );
    vdeb << "about to compare";
    EXPECT_TRUE( t1 == t1_dec );

    ABCD v1{1,2,3, {} };
    auto v2 = v1;

    vdeb(v1 == v2);
}

//=======================================================================================

TEST_F( II_Serialization, encode_not_serials )
{
    {
        std::vector<int32_t> val{1,2,3,4,5,6,7,8};
        using Type = decltype(val);
        auto str = Encoder::encode( val );
        EXPECT_EQ( type_signature<Type>(), "vector<int32>" );
        auto res = AbstractDecoder::decode<Type>( str );
        EXPECT_EQ( val, res );
    }
    {
        int val{1};
        using Type = decltype(val);
        auto str = Encoder::encode( val );
        vdeb << str.to_Hex();
        auto res = AbstractDecoder::decode<Type>( str );
        EXPECT_EQ( val, res );
    }
    {
        std::tuple<int32_t,uint64_t,std::string> val{-1,2,"HW"};
        using Type = decltype(val);
        auto str = Encoder::encode( val );
        EXPECT_EQ( type_signature<Type>(), "{int32,uint64,string}" );
        auto res = AbstractDecoder::decode<Type>( str );
        EXPECT_EQ( val, res );
    }
    {
        // на одной машине, нечего бояться.
        std::tuple<int,uint,std::vector<VSerialize_Size>> val{-1,2,{1,800,234567,1,0}};
        using Type = decltype(val);
        auto str = Encoder::encode( val );
        vdeb << str.to_Hex();
        vdeb << type_signature<Type>();
        auto res = AbstractDecoder::decode<Type>( str );
        EXPECT_EQ( val, res );
    }
}

template<typename T>
class VSerial_Optional
{
public:
    // empty
    explicit VSerial_Optional()
    {}
    // with value
    explicit VSerial_Optional( const T& val )
    { _vec.push_back( val ); }

    explicit operator bool() const  { return has(); }
    bool has() const                { return !_vec.empty(); }

    T& value()                      { return _vec.at(0); }
    const T& value() const          { return _vec.at(0); }

//private:
//    friend struct AbstractDecoder::_tuple_reader;//<VSerial_Optional<T>>
    explicit VSerial_Optional( const std::vector<T>& val ) : _vec(val)
    { assert( _vec.size() <= 1 ); }

private:
    friend struct VSerializable<VSerial_Optional<T>>;
    const std::vector<T>& _real_place() const { return _vec; }

private:
    std::vector<T> _vec;
};

template<typename T>
struct VSerializable< VSerial_Optional<T> >
{
    std::tuple<std::vector<T>> operator()( const VSerial_Optional<T>& opt )
    {
        return std::make_tuple( opt._real_place() );
    }
};




//=======================================================================================
namespace std
{
    template<>
    template<typename T>
    struct hash<VSerializable<T>>
    {
        size_t operator()( const T& s ) const noexcept
        {
            return serialization::calc_hash( s );
        }
    };
    //-----------------------------------------------------------------------------------
    template<typename ... Ts>
    struct hash< std::tuple<Ts...> >
    {
        size_t operator()( const std::tuple<Ts...>& tup ) const noexcept
        {
            return serialization::calc_hash( tup );
        }
    };
}
//=======================================================================================


struct T1
{
    int i = 10;
};

//namespace std {
//    template<>
//    struct hash<T1>
//    {
//        size_t operator()(const T1& t1) const noexcept
//        {
//            return std::hash<int>()(t1.i);
//        }
//    };
//}

TEST_F( II_Serialization, udp_packets )
{
//    std::unordered_map<ABC,int> abcm;

    auto opt_abc = VSerial_Optional<ABC>( ABC{1,2,3} );

    vdeb << is_serializable<VSerial_Optional<ABC>>();
    vdeb << bool(opt_abc);
    auto sss = Encoder::encode( opt_abc );
    vdeb << sss.to_Hex();
    auto ropt = AbstractDecoder::decode<VSerial_Optional<ABC>>( sss );
    vdeb << (ropt == opt_abc);

    //exit(1);

    ABCD abcd{ 1, 2, 3, VSerialize_Example{-42, 42, '!'} };
    auto enc_str = Encoder::encode( abcd );

    auto pks = split_packets( enc_str,
                                       hash_of_name<ABCD>(),
                                       hash_of_signature<ABCD>(),
                                       "channel",
                                       25 );
    for (auto s: pks)
        vdeb << s.to_Hex();


    auto t1 = TransmitterByChannels::make<ABC>();
    t1.subscribe<ABC>( [](ABC abc){vdeb << "ABC" << abc.a << abc.b << int(abc.c);}, "ololo" );
    t1.subscribe<ABC>( [](ABC abc){vdeb << "ABC" << abc.a << abc.b << int(abc.c);}, "ololo" );
    t1.subscribe<ABC>( [](ABC abc){vdeb << "ABC" << abc.a << abc.b << int(abc.c);}, "ololo" );
    t1.subscribe<ABC>( [](ABC abc){vdeb << "ABC" << abc.a << abc.b << int(abc.c);}, "ololo" );
    t1.subscribe<ABC>( [](ABC abc){vdeb << "ABC" << abc.a << abc.b << int(abc.c);}, "ololo" );
    t1.subscribe_multi<ABC>( [](ABC abc,std::string c){vdeb << "multi" << abc.a << abc.b << int(abc.c) << c;} );
    sss = Encoder::encode( ABC{4,5,6} );
    t1.decode( sss, "ololo" );

    //std::unordered_map< std::tuple<int>, std::string> ddddd;
    //ddddd.insert( { {3},"{}" } );

    vdeb << std::hash<const char*>()("olo");
    vdeb << calc_hash( ABC{1,2,3} );
    auto abc = ABC{3,4,5};
    //vdeb << std::hash<Vserialize_Hash<ABC>>( Vserialize_Hash<ABC>(abc) );
    T1 t11;
    t11.i = 15;
    //vdeb << std::hash<T1>()( t11 ) << std::hash<int>()( 15 );
    //std::hash<VSerializable<ABC>> abchash;
    //vdeb << abchash( ABC{1,2,3} );
    exit(1);
}
//=======================================================================================

#pragma GCC diagnostic pop

