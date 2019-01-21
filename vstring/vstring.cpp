/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#include "vstring.h"


#include <assert.h>
#include <sstream>
#include <algorithm>

//=======================================================================================
static_assert( BYTE_ORDER == BIG_ENDIAN || BYTE_ORDER == LITTLE_ENDIAN,
               "Unknown byte order" );
//=======================================================================================


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

    return VString( res );
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
bool VString::is_hex_symbol( char ch )
{
    return ch_from_hex(ch) >= 0;
}
//=======================================================================================
//      HEX
//=======================================================================================



//=======================================================================================
//      append, prepend, takes
//=======================================================================================
VString& VString::prepend( const std::string &s )
{
    return prepend( s.begin(), s.end() );
}
//=======================================================================================
VString& VString::append( const std::string &s )
{
    return append( s.begin(), s.end() );
}
//=======================================================================================
VString& VString::prepend( char ch )
{
    return prepend_as_sys( ch );
}
//=======================================================================================
VString& VString::append( char ch )
{
    return append_as_sys( ch );
}
//=======================================================================================
char VString::take_front_ch()
{
    return take_front_LE<char>();
}
//=======================================================================================
char VString::take_back_ch()
{
    return take_back_LE<char>();
}
//=======================================================================================
VString VString::take_front_str( size_t sz )
{
    auto res = front_str( sz );
    chop_front( sz );
    return res;
}
//=======================================================================================
VString VString::take_back_str( size_t sz )
{
    auto res = back_str( sz );
    chop_back( sz );
    return res;
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
    while( from != end() && is_any_space(*from) )
        ++from;

    if ( from == end() ) return {};

    auto to = end() - 1;
    while( to != from && is_any_space(*to) )
        --to;

    return VString( from, to + 1 );
}
//=======================================================================================
VString::Vector VString::split_by_spaces() const
{
    Vector res;

    auto cur = begin();    
    do
    {
        auto next = std::find_if( cur, end(), is_any_space );

        VString str( cur, next );
        if ( !str.empty() )
            res.push_back( str );

        if ( next == end() ) break;
        cur = next + 1;
    }
    while(1);

    return res;
}
//=======================================================================================
bool VString::is_any_space( char ch )
{
    return std::isspace( ch ) ||
           ch == '\n';
}
//=======================================================================================
//      patterns finding
//=======================================================================================

//=======================================================================================
//      Substrings
//=======================================================================================
VString VString::front_str( size_t sz ) const
{
    _check_enough_size( sz );
    return substr( 0, sz );
}
//=======================================================================================
VString VString::back_str( size_t sz ) const
{
    _check_enough_size( sz );
    return substr( size() - sz, sz );
}
//=======================================================================================
//      Substrings
//=======================================================================================



//=======================================================================================
//      splitting
//=======================================================================================
VString::Vector VString::split( char splitter ) const
{
    VString::Vector res;

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
VString::Vector VString::split_without_empties( char splitter ) const
{
    auto res = split( splitter );
    res.erase( std::remove(res.begin(), res.end(), std::string()), res.end() );
    return res;
}
//=======================================================================================
//      splitting
//=======================================================================================


//=======================================================================================
//      FORWARD VIEW
//=======================================================================================
VString::ForwardView VString::forward_view() const
{
    return ForwardView( this );
}
//=======================================================================================
void VString::_check_enough_size( size_t sz ) const
{
    if ( size() < sz )
        throw std::out_of_range( "VString: remained size less than need." );
}
//=======================================================================================
VString::ForwardView::ForwardView( const VString *owner )
    : _buffer( owner->c_str() )
    , _remained( owner->size() )
{}
//=======================================================================================
int VString::ForwardView::remained() const
{
    assert( _remained <= std::numeric_limits<int>::max() );
    return static_cast<int>( _remained );
}
//=======================================================================================
bool VString::ForwardView::finished() const
{
    return _remained == 0;
}
//=======================================================================================
VString VString::ForwardView::show_str( size_t sz ) const
{
    if ( sz > size_t(remained()) )
        throw std::out_of_range("VString::ForwardView::show_str -- not enouth data.");

    return VString( _buffer, sz );
}
//=======================================================================================
VString VString::ForwardView::take_str( size_t sz )
{
    auto res = show_str( sz );

    _remained -= sz;
    _buffer   += sz;

    return res;
}
//=======================================================================================
//      FORWARD VIEW
//=======================================================================================
