#include "vstring.h"


#include <sstream>
#include <algorithm>



//=======================================================================================
//      Init, ctors
//=======================================================================================
VString::VString() noexcept
    : std::string()
{}
//=======================================================================================
VString::VString( std::string &&str ) noexcept
    : std::string( std::move(str) )
{}
//=======================================================================================
VString::VString( const std::string &str )
    : std::string( str )
{}
//=======================================================================================
void VString::_check_big_or_little_endian()
{
    static_assert( BYTE_ORDER == BIG_ENDIAN || BYTE_ORDER == LITTLE_ENDIAN,
                   "Unknown byte order" );
}
//=======================================================================================
//      Init, ctors
//=======================================================================================



//=======================================================================================
//      HEX
//=======================================================================================
static auto constexpr hexs_syms = "0123456789abcdef";
static auto constexpr Hexs_Syms = "0123456789ABCDEF";
//---------------------------------------------------------------------------------------
static int ch_from_hex(char ch)
{
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return 10 + ch - 'A';
    if (ch >= 'a' && ch <= 'f') return 10 + ch - 'a';
    return -1;
}
//---------------------------------------------------------------------------------------
VString VString::from_hex( const std::string &src )
{
    std::string res;
    res.resize( (src.size() + 1)/2 );

    auto cur = res.rbegin();
    int real_res_size = 0;

    bool in_char = false;
    for ( auto src_it = src.rbegin(); src_it != src.rend(); ++src_it )
    {
        int tmp = ch_from_hex( *src_it );
        if (tmp < 0) continue;

        if (in_char)
        {
            *cur++ |= tmp << 4;
        }
        else
        {
            *cur = tmp;
            ++real_res_size;
        }
        in_char = !in_char;
    }

    return res.erase( 0, res.size() - real_res_size );
}
//---------------------------------------------------------------------------------------
static VString _to_hex( const std::string &src, const char *hsyms, bool with_space )
{
    std::stringstream ss;

    for ( auto ch: src )
    {
        ss << hsyms[(ch >> 4) & 0xF] << hsyms[ch & 0xF];
        if ( with_space ) ss << " ";
    }

    auto res = ss.str();
    if (with_space && !src.empty()) res.pop_back(); // delete last space.
    return res;
}
//=======================================================================================
VString VString::tohex() const
{
    return _to_hex( *this, hexs_syms, false );
}
//=======================================================================================
VString VString::toHex() const
{
    return _to_hex( *this, Hexs_Syms, false );
}
//=======================================================================================
VString VString::to_hex() const
{
    return _to_hex( *this, hexs_syms, true );
}
//=======================================================================================
VString VString::to_Hex() const
{
    return _to_hex( *this, Hexs_Syms, true );
}
//=======================================================================================
//      HEX
//=======================================================================================



//=======================================================================================
//      append, prepend, takes
//=======================================================================================
void VString::prepend( const std::string &s )
{
    return prepend( s.begin(), s.end() );
}
//=======================================================================================
char VString::take_front()
{
    return take_front_LE<char>();
}
//=======================================================================================
char VString::take_back()
{
    return take_back_LE<char>();
}
//=======================================================================================
void VString::append_byte_string( const std::string &str )
{
    if (str.size() > std::numeric_limits<uint8_t>::max() )
        throw std::runtime_error("Byte string cannot be serialize, size > 255...");

    uint8_t sz = static_cast<uint8_t>( str.size() );
    append_LE( sz );
    append( str.c_str(), sz );
}
//=======================================================================================
void VString::append_word_string_LE(const std::string &str)
{
    if ( str.size() > std::numeric_limits<uint16_t>::max() )
        throw std::runtime_error("Word string cannot be serialize, size > 2^16...");

    uint16_t sz = static_cast<uint16_t>( str.size() );
    append_LE( sz );
    append( str.c_str(), sz );
}
//=======================================================================================
void VString::append_dword_string_LE( const std::string &str )
{
    if ( str.size() > std::numeric_limits<uint32_t>::max() )
        throw std::overflow_error("String is bigger 2^32.");

    uint32_t sz = static_cast<uint32_t>( str.size() );
    append_LE( sz );
    append( str );
}
//=======================================================================================
//      append, prepend, takes
//=======================================================================================



//=======================================================================================
//      chops
//=======================================================================================
void VString::chop_front( size_t n )
{
    erase(0, n);
}
//=======================================================================================
void VString::chop_back( size_t n )
{
    auto new_size = size() > n
                        ? size() - n
                        : 0;

    resize( new_size );
}
//=======================================================================================
//      chops
//=======================================================================================



//=======================================================================================
//      patterns finding
//=======================================================================================
bool VString::begins_with( const std::string &what ) const
{
    return find(what) == 0;
}
//=======================================================================================
bool VString::ends_with( const std::string &what ) const
{
    if ( what.size() > size() ) return false;

    return rfind(what) == size() - what.size();
}
//=======================================================================================
//      patterns finding
//=======================================================================================



//=======================================================================================
//      splitting
//=======================================================================================
std::vector<std::string> VString::split( char splitter ) const
{
    std::vector<std::string> res;

    auto cur = begin();
    auto next = std::find( begin(), end(), splitter );
    while ( cur != end() )
    {
        res.push_back( {cur, next} );
        if ( next == end() ) break;
        cur = next + 1;
        next = std::find( cur, end(), splitter );
    }
    return res;

//    auto cur2 = begin();
//    do
//    {
//        auto next2 = std::find( cur2, end(), splitter );
//        res.push_back( {cur2, next2} );
//        if ( next2 == end() ) break;
//        cur2 = next2 + 1;
//    } while(1);
//    return res;
}
//=======================================================================================
std::vector<std::string> VString::split_without_empties( char splitter ) const
{
    auto res = split( splitter );
    res.erase( std::remove(res.begin(), res.end(), std::string()), res.end() );
    return res;
}
//=======================================================================================
//      splitting
//=======================================================================================
