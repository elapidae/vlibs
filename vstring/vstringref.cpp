#include "vstringref.h"

#include <sstream>
#include <algorithm>


//=======================================================================================
//      Init, ctors
//=======================================================================================
VStringRef::VStringRef(std::string *data) noexcept
    : _data(data)
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
std::string VStringRef::from_hex( const std::string &src )
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
static std::string _to_hex(const std::string &src, const char *hsyms, bool with_space)
{
    std::stringstream ss;

    for ( auto ch: src )
    {
        ss << hsyms[(ch >> 4) & 0xF] << hsyms[ch & 0xF];
        if ( with_space ) ss << " ";
    }

    auto res = ss.str();
    if ( with_space && !src.empty() ) res.pop_back(); // delete last space.
    return res;
}
//=======================================================================================
std::string VStringRef::tohex( const std::string &s )
{
    return _to_hex( s, hexs_syms, false );
}
//=======================================================================================
std::string VStringRef::toHex( const std::string &s )
{
    return _to_hex( s, Hexs_Syms, false );
}
//=======================================================================================
std::string VStringRef::to_hex( const std::string &s )
{
    return _to_hex( s, hexs_syms, true );
}
//=======================================================================================
std::string VStringRef::to_Hex( const std::string &s )
{
    return _to_hex( s, Hexs_Syms, true );
}
//=======================================================================================
//      HEX
//=======================================================================================



//=======================================================================================
//      append, prepend
//=======================================================================================
void VStringRef::prepend( const std::string &s )
{
    return prepend( s.begin(), s.end() );
}
//=======================================================================================
void VStringRef::append( const std::string &s )
{
    return append( s.begin(), s.end() );
}
//=======================================================================================
//      append, prepend
//=======================================================================================



//=======================================================================================
//      chops
//=======================================================================================
void VStringRef::chop_front( size_t n )
{
    _data->erase(0, n);
}
//=======================================================================================
void VStringRef::chop_back( size_t n )
{
    auto new_size = _data->size() > n
                        ? _data->size() - n
                        : 0;

    _data->resize( new_size );
}
//=======================================================================================
//      chops
//=======================================================================================


//=======================================================================================
//      patterns finding
//=======================================================================================
bool VStringRef::begins_with( const std::string &what ) const
{
    return _data->find(what) == 0;
}
//=======================================================================================
bool VStringRef::ends_with( const std::string &what ) const
{
    if ( what.size() > _data->size() ) return false;

    return _data->rfind(what) == _data->size() - what.size();
}
//=======================================================================================
//      patterns finding
//=======================================================================================


//=======================================================================================
//      splitting
//=======================================================================================
std::vector<std::string> VStringRef::split( char splitter ) const
{
    std::vector<std::string> res;

    auto cur = _data->begin();
    auto next = std::find( _data->begin(), _data->end(), splitter );
    while ( cur != _data->end() )
    {
        res.push_back( {cur, next} );
        if (next == _data->end()) break;
        cur = next + 1;
        next = std::find( cur, _data->end(), splitter );
    }

    return res;
}
//=======================================================================================
std::vector<std::string> VStringRef::split_without_empties(char splitter) const
{
    auto res = split( splitter );
    res.erase( std::remove(res.begin(), res.end(), std::string()), res.end() );
    return res;
}
//=======================================================================================
//      splitting
//=======================================================================================
