#include "vbytearray.h"

#include <sstream>
#include <algorithm>

template<class T>
class TD;


//=======================================================================================
VByteArray::VByteArray()
{
    static_assert( std::is_same<value_type, char>::value, "!is_same<value_type,char>" );
    static_assert( sizeof(value_type) == 1, "Char size must be = 1");

    // Хорошо бы устроить статическую проверку на использование UTF-8...
}
//=======================================================================================
VByteArray::VByteArray( const std::string &rhs )
    : std::string( rhs )
{}
//=======================================================================================


//=======================================================================================
static auto constexpr hexs_syms = "0123456789abcdef";
static auto constexpr Hexs_Syms = "0123456789ABCDEF";
//=======================================================================================
//VByteArray VByteArray::_tohex( const char *syms ) const
//{
//    std::stringstream ss;
//    for ( auto ch: *this )
//        ss << syms[(ch >> 4) & 0xF] << syms[ch & 0xF];

//    return ss.str();
//}
//=======================================================================================
VByteArray VByteArray::_to_hex( const char *hsyms, bool with_space ) const
{
    std::stringstream ss;

    for ( auto ch: *this )
    {
        ss << hsyms[(ch >> 4) & 0xF] << hsyms[ch & 0xF];
        if ( with_space ) ss << " ";
    }

    auto res = ss.str();
    if ( !empty() && with_space ) res.pop_back(); // delete last space.
    return res;
}
//=======================================================================================
VByteArray VByteArray::tohex() const
{
    return _to_hex( hexs_syms, false );
}
//=======================================================================================
VByteArray VByteArray::toHex() const
{
    return _to_hex( Hexs_Syms, false );
}
//=======================================================================================
VByteArray VByteArray::to_hex() const
{
    return _to_hex( hexs_syms, true );
}
//=======================================================================================
VByteArray VByteArray::to_Hex() const
{
    return _to_hex( Hexs_Syms, true );
}
//=======================================================================================
VByteArray &VByteArray::prepend( const std::string &s )
{
    return prepend( s.begin(), s.end() );
}
//=======================================================================================
static int ch_from_hex(char ch)
{
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return 10 + ch - 'A';
    if (ch >= 'a' && ch <= 'f') return 10 + ch - 'a';
    return -1;
}
//---------------------------------------------------------------------------------------
VByteArray VByteArray::from_hex( const std::string &src )
{
    VByteArray res;
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

    res.chop_front( res.size() - real_res_size );
    return res;
}
//=======================================================================================


//=======================================================================================
void VByteArray::chop_front(size_t n)
{
    erase(0, n);
}
//=======================================================================================
void VByteArray::chop_back(size_t n)
{
    resize( size() > n ? n : size() );
}
//=======================================================================================

//=======================================================================================
bool VByteArray::begins_with(const std::string &mask) const
{
    return find(mask) == 0;
}
//=======================================================================================
bool VByteArray::ends_with(const std::string &mask) const
{
    if (mask.size() > size()) return false;
    return rfind(mask) == size() - mask.size();
}
//=======================================================================================
std::vector<VByteArray> VByteArray::split( char splitter ) const
{
    std::vector<VByteArray> res;

    auto cur = begin();
    auto next = std::find( begin(), end(), splitter );
    while ( cur != end() )
    {
        res.push_back( {cur, next} );
        if (next == end()) break;
        cur = next + 1;
        next = std::find( cur, end(), splitter );
    }

    return res;
}
//=======================================================================================
std::vector<VByteArray> VByteArray::split_without_empties(char splitter) const
{
    auto res = split( splitter );
    res.erase( std::remove( res.begin(), res.end(), VByteArray() ), res.end() );
    return res;
}
//=======================================================================================
//=======================================================================================


//=======================================================================================
//=======================================================================================
VByteArray::ForwardReader VByteArray::get_forward_reader() const
{
    return { this };
}
//=======================================================================================
void VByteArray::chop_to_position( const VByteArray::ForwardReader &freader )
{
    chop_front( freader._pos - c_str() );
}
//=======================================================================================
//=======================================================================================
VByteArray::ForwardReader::ForwardReader( const VByteArray *owner )
    : _pos      ( owner->c_str() )
    , _remained ( owner->size()  )
{}
//=======================================================================================
VByteArray VByteArray::ForwardReader::pop_str( int len )
{
    if ( len > _remained )
        throw std::out_of_range("Len > leaved in VByteArray::FrontReader::pop_str()");

    if ( len <= 0 ) return {};

    VByteArray res( _pos, _pos + len );
    _pos      += len;
    _remained -= len;
    return res;
}
//=======================================================================================
int VByteArray::ForwardReader::remained_bytes() const
{
    return _remained;
}
//=======================================================================================
//=======================================================================================
