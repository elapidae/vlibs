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
VString::VString( const std::string &str, size_t pos, size_t len )
    : std::string( str, pos, len )
{}
//=======================================================================================
VString::VString( const char *s )
    : std::string( s )
{}
//=======================================================================================
VString::VString( const char *s, size_t n )
    : std::string( s, n )
{}
//=======================================================================================
VString::VString( size_t n, char c )
    : std::string( n, c )
{}
//=======================================================================================
VString::VString(const std::initializer_list<char> &il )
    : std::string( il )
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
    size_t real_res_size = 0;

    bool in_char = false;
    for ( auto src_it = src.rbegin(); src_it != src.rend(); ++src_it )
    {
        int tmp = ch_from_hex( *src_it );
        if (tmp < 0) continue;

        if ( in_char )
        {
            *cur++ |= tmp << 4;
        }
        else
        {
            *cur = static_cast<char>( tmp );
            ++real_res_size;
        }
        in_char = !in_char;
    }

    return res.erase( 0, res.size() - real_res_size );
}
//---------------------------------------------------------------------------------------
VString VString::from_hex() const
{
    return from_hex( *this );
}
//---------------------------------------------------------------------------------------
//  Separator wiil ignore if with_separator == false.
static VString _to_hex( const std::string &src,
                        const char *hsyms,
                        bool with_separator,
                        char separator )
{
    std::stringstream ss;

    for ( auto ch: src )
    {
        ss << hsyms[(ch >> 4) & 0xF] << hsyms[ch & 0xF];

        if ( with_separator )
            ss << separator;
    }

    auto res = ss.str();

    if ( with_separator && !src.empty() )   // Delete last space.
        res.pop_back();                     //

    return res;
}
//=======================================================================================
VString VString::tohex() const
{
    return _to_hex( *this, hexs_syms, false, '\0' );
}
//=======================================================================================
VString VString::toHex() const
{
    return _to_hex( *this, Hexs_Syms, false, '\0' );
}
//=======================================================================================
VString VString::to_hex( char separator ) const
{
    return _to_hex( *this, hexs_syms, true, separator );
}
//=======================================================================================
VString VString::to_Hex( char separator ) const
{
    return _to_hex( *this, Hexs_Syms, true, separator );
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
template<typename SizeType, typename WhoPushSize>
static void append_sized_str( VString *self, WhoPushSize pushsz, const std::string &str )
{
    if ( str.size() > std::numeric_limits<SizeType>::max() )
        throw std::runtime_error( "String cannot be appended as sized, "
                                  "size > max of type..." );

    SizeType sz = static_cast<SizeType>( str.size() );
    (self->*pushsz)( sz );
    self->append( str.c_str(), sz );
}
//=======================================================================================
void VString::append_sized1_string( const std::string &str )
{
    append_sized_str<uint8_t>( this, &VString::append_LE<uint8_t>, str );
}
//=======================================================================================
void VString::append_sized2_string_LE(const std::string &str)
{
    append_sized_str<uint16_t>( this, &VString::append_LE<uint16_t>, str );
}
//=======================================================================================
void VString::append_sized2_string_BE(const std::string &str)
{
    append_sized_str<uint16_t>( this, &VString::append_BE<uint16_t>, str );
}
//=======================================================================================
void VString::append_sized4_string_LE( const std::string &str )
{
    append_sized_str<uint32_t>( this, &VString::append_LE<uint32_t>, str );
}
//=======================================================================================
void VString::append_sized4_string_BE(const std::string &str)
{
    append_sized_str<uint32_t>( this, &VString::append_BE<uint32_t>, str );
}
//=======================================================================================
//      append, prepend, takes
//=======================================================================================



//=======================================================================================
//      chops
//=======================================================================================
void VString::chop_front( size_t n )
{
    erase( 0, n );
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
VString VString::trimmed() const
{
    auto from = begin();
    while( from != end() && std::isspace(*from) )
        ++from;

    if ( from == end() ) return {};

    auto to = end() - 1;
    while( to != from && std::isspace(*to) )
        --to;

    return VString( from, to + 1 );
}
//=======================================================================================
static bool is_any_space(char ch)
{
    return std::isspace( ch ) ||
           ch == '\n';
}
//---------------------------------------------------------------------------------------
std::vector<VString> VString::split_by_spaces() const
{
    std::vector<VString> res;

    auto cur = begin();
    auto next = std::find_if( begin(), end(), [](char ch){ return is_any_space(ch); } );
    while ( cur != end() )
    {
        VString str( cur, next );
        if ( !str.empty() )
            res.push_back( str );

        if ( next == end() ) break;
        cur = next + 1;
        next = std::find_if( cur, end(), [](char ch){ return is_any_space(ch); } );
    }
    return res;
}
//=======================================================================================
//      patterns finding
//=======================================================================================

//=======================================================================================
//      Substrings
//=======================================================================================
VString VString::left( size_t sz ) const
{
    sz = std::min( sz, size() );

    return substr( 0, sz );
}
//=======================================================================================
VString VString::right( size_t sz ) const
{
    sz = std::min( sz, size() );

    return substr( size() - sz, sz );
}
//=======================================================================================
//      Substrings
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
