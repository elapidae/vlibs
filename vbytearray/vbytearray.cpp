#include "vbytearray.h"

#include <sstream>
#include <assert.h>

using namespace std;


//=======================================================================================
VByteArray::VByteArray()
    : _Base()
{
    static_assert( sizeof(value_type) == 1, "VByteArray::value_type is not byte size." );
}
//=======================================================================================
VByteArray::VByteArray(size_t reserve)
    : _Base(reserve)
{}
//=======================================================================================
VByteArray::VByteArray( const std::string &str )
    : _Base(str.begin(), str.end())
{}
//=======================================================================================
VByteArray::VByteArray( const char *ch )
    : VByteArray( std::string(ch) )
{}
//=======================================================================================
VByteArray::VByteArray(std::initializer_list<vector::value_type> il)
    : _Base( il )
{}
//=======================================================================================
VByteArray::value_type VByteArray::pop_front()
{
    return pop_front_little<VByteArray::value_type>();
}
//=======================================================================================
VByteArray::value_type VByteArray::pop_back()
{
    return pop_back_little<value_type>();
//    auto res = back();
//    _Base::pop_back();
//    return res;
}
//=======================================================================================
std::string VByteArray::to_string() const
{
    return string(begin(), end());
}
//=======================================================================================
string VByteArray::str() const
{
    return to_string();
}
//=======================================================================================

//=======================================================================================
static auto constexpr hexs = "0123456789abcdef";
//=======================================================================================
string VByteArray::tohex() const
{
    std::stringstream ss;
    for (auto b: *this)
        ss << hexs[(b >> 4) & 0xF] << hexs[b & 0xF];

    return ss.str();
}
//=======================================================================================
string VByteArray::to_hex() const
{
    std::stringstream ss;
    for (auto b: *this)
        ss << hexs[(b >> 4) & 0xF] << hexs[b & 0xF] << " ";

    auto res = ss.str();
    res.pop_back(); // pop last space
    return res;
}
//=======================================================================================
static int ch_from_hex(char ch)
{
    if (ch >= 'A' && ch <= 'F') return 10 + ch - 'A';
    if (ch >= 'a' && ch <= 'f') return 10 + ch - 'a';
    if (ch >= '0' && ch <= '9') return ch - '0';
    return -1;
}
//=======================================================================================
VByteArray VByteArray::from_hex( const string &str )
{
    VByteArray res( (str.size() + 1)/2 );
    auto pos = res.data();

    bool in_char = false;
    for (auto ch: str)
    {
        int tmp = ch_from_hex(ch);
        if (tmp < 0) continue;

        if (in_char)
        {
            *pos <<= 4;
            *pos++ |= tmp;
        }
        else
        {
            *pos = tmp;
        }
        in_char = !in_char;
    }

    int corr_size = in_char ? 1 : 0;
    res.resize( pos - res.data() + corr_size );
    return res;
}
//=======================================================================================
VByteArray &VByteArray::operator +=(const VByteArray &rhs)
{
    append( rhs );
    return *this;
}
//=======================================================================================

//=======================================================================================
void VByteArray::append(char ch)
{
    push_back( ch );
}
//=======================================================================================
void VByteArray::operator +=(char ch)
{
    append( ch );
}
//=======================================================================================
VByteArray VByteArray::left(int count) const
{
    if ( count < 0 )
        count = 0;

    auto e = count > int(size())
                ? end()
                : begin() + count;

    return VByteArray( begin(), e );
}
//=======================================================================================
VByteArray VByteArray::pop_left( int count )
{
    if( count > int(size()) && count < 0 )
        throw out_of_range( "VByteArray::pop_left(int count)" );

    auto res = left( count );
    chop_front( count );
    return res;
}
//=======================================================================================

//=======================================================================================
void VByteArray::chop_front( int count )
{
    if ( (count < 0) || count > int(size()) )
    {
        throw std::length_error( "void VByteArray::chop_front(int count): "
                                 "count more than size" );
    }
    erase( begin(), begin() + count );
}
//=======================================================================================
void VByteArray::chop_back( int count )
{
    if ( (count < 0) || count > int(size()) )
    {
        throw std::length_error( "void VByteArray::chop_back(int count): "
                                 "count more than size" );
    }

    resize( size() - count );
}
//=======================================================================================


//=======================================================================================
ostream &operator <<(ostream &s, const VByteArray &arr)
{
    s << arr.to_string();
    return s;
}
//=======================================================================================
VByteArray operator + ( VByteArray lhs, const VByteArray &rhs )
{
    lhs.append( rhs );
    return lhs;
}
//=======================================================================================
