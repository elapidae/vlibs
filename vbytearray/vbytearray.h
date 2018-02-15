#ifndef VBYTEARRAY_H
#define VBYTEARRAY_H

#include <assert.h>
#include <vector>
#include <stdint.h>
#include <string>
#include <stdexcept>
#include <algorithm>


//=======================================================================================
class VByteArray : public std::vector<char>
{
    using _Base = std::vector<char>;

public:

    using Vector = std::vector<VByteArray>;

    //-------------------------------------------------------------------------------

    VByteArray();
    explicit VByteArray(size_t reserve);

    VByteArray( const char *ch );
    VByteArray( const std::string &str );
    VByteArray( std::initializer_list<value_type> il );

    template<typename It>
    VByteArray( const It& b, const It& e ) : _Base(b, e) {}

    template<typename Cont>
    VByteArray( const Cont& cont ) : VByteArray(cont.begin(), cont.end()) {}

    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    //  No no no!!!!
    value_type pop_front();
    value_type pop_back();
    //-------------------------------------------------------------------------------
    //          LITTLE AND BIG ENDIAN MANIPULATIONS
    //-------------------------------------------------------------------------------
    template<typename T> T front_big()      const;
    template<typename T> T back_big()       const;

    template<typename T> T front_little()   const;
    template<typename T> T back_little()    const;
    //-------------------------------------------------------------------------------
    template<typename T> T pop_front_big();
    template<typename T> T pop_back_big();

    template<typename T> T pop_front_little();
    template<typename T> T pop_back_little();
    //-------------------------------------------------------------------------------
    template<typename T> void push_front_little( const T& val );
    template<typename T> void push_back_little ( const T& val );

    template<typename T> void push_front_big   ( const T& val );
    template<typename T> void push_back_big    ( const T& val );
    //-------------------------------------------------------------------------------
    //          LITTLE AND BIG ENDIAN MANIPULATIONS
    //-------------------------------------------------------------------------------

    std::string to_string() const;
    std::string str()       const;    

    std::string tohex()     const;  //  print as '0123456789abcdef'
    std::string to_hex()    const;  //  print as '01 23 45 67 89 ab cd ef'

    //  Игнорирует все символы кроме адекватных,
    //  если адекватных символов будет нечетное количество, последний отсекается.
    static VByteArray from_hex( const std::string &str );
    //-------------------------------------------------------------------------------


    VByteArray &operator += ( const VByteArray &rhs );
    //-------------------------------------------------------------------------------

    template<typename Container>
    void append( const Container &cont )
    {
        insert( end(), cont.begin(), cont.end() );
    }
    template<typename It>
    void append( const It& b, const It& e )
    {
        insert(end(), b, e);
    }
    void append( char ch );

    void operator += ( char ch );

    template<typename Container>
    void prepend( const Container &cont )
    {
        insert( begin(), cont.begin(), cont.end() );
    }
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    VByteArray left ( int count ) const;

    VByteArray pop_left( int count );   // left & chop, throws out_of_range

    void chop_front ( int count );  // Выбросить count байт
    void chop_back  ( int count );  // с начала или с конца.
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    //  Начинается с такой последовательности
    template<typename Container>
    bool begins_with( const Container& msg ) const
    {
        return begins_with( msg.begin(), msg.end() );
    }
    //-------------------------------------------------------------------------------
    template<typename Iter>
    bool begins_with( Iter b, const Iter& e ) const
    {
        return match( begin(), b, e );
    }
    //-------------------------------------------------------------------------------
    template<typename Iter>
    bool match( const_iterator my_b, Iter b, const Iter& e ) const
    {
        assert( b != e ); // elsewhere always returns true...

        while ( b != e )
        {
            if ( my_b == end() )
                return false;

            if ( *my_b++ != value_type(*b++) )
                return false;
        }
        return true;
    }
    //-------------------------------------------------------------------------------
    template<typename Container>
    int find_substr( const Container &cont, int pos = 0 ) const
    {
        assert( pos >= 0 && pos <= int(size()) );
        assert( !cont.empty() ); // elsewhere always returns true...

        auto cur = begin() + pos;
        while ( cur != end() )
        {
            cur = std::find( cur, end(), value_type(*cont.begin()) );

            if ( cur == end() ||
                 match(cur, cont.begin(), cont.end()))
            {
                break;
            }

            ++cur;
        }
        return cur - begin();
    }
    //-------------------------------------------------------------------------------


    Vector split( value_type delimiter ) const
    {
        Vector res;

        auto it = begin();
        while ( 1 )
        {
            auto next = std::find( it, end(), delimiter );
            res.push_back( {it, next} );

            if ( next == end() )
                break;

            it = next + 1;
        }
        return res;
    }


private:
    static constexpr bool _is_little_endian();

    template<typename T, typename Iter>
    T _get_trivial( const Iter& b, const Iter& e ) const;

    template<typename T>
    void _push_front_trivial( const T& val, bool not_reverse );

    template<typename T>
    void _push_back_trivial( const T& val, bool not_reverse );
};
//=======================================================================================


//=======================================================================================
std::ostream& operator << (std::ostream &s, const VByteArray &arr);
//=======================================================================================


//=======================================================================================
constexpr bool VByteArray::_is_little_endian()
{
    #if BYTE_ORDER == LITTLE_ENDIAN
        return true;
    #elif BYTE_ORDER == BIG_ENDIAN
        return false;
    #else
      #error "Unknown byte order";
    #endif
}
//=======================================================================================
template<typename T>
T VByteArray::front_little() const
{
  #if BYTE_ORDER == LITTLE_ENDIAN
    auto b = begin();
    auto e = begin() + sizeof(T);
  #elif BYTE_ORDER == BIG_ENDIAN
    auto b = rend() - sizeof(T);
    auto e = rend();
  #else
    #error "Unknown byte order";
  #endif

    return _get_trivial<T>( b, e );
}
//=======================================================================================
template<typename T>
T VByteArray::back_little() const
{
  #if BYTE_ORDER == LITTLE_ENDIAN
    auto b = end() - sizeof(T);
    auto e = end();
  #elif BYTE_ORDER == BIG_ENDIAN
    auto b = rbegin();
    auto e = rbegin() + sizeof(T);
  #else
    #error "Unknown byte order";
  #endif

    return _get_trivial<T>( b, e );
}
//=======================================================================================
template<typename T>
T VByteArray::front_big() const
{
  #if BYTE_ORDER == BIG_ENDIAN
    auto b = begin();
    auto e = begin() + sizeof(T);
  #elif BYTE_ORDER == LITTLE_ENDIAN
    auto b = rend() - sizeof(T);
    auto e = rend();
  #else
    #error "Unknown byte order";
  #endif

    return _get_trivial<T>( b, e );
}
//=======================================================================================
template<typename T>
T VByteArray::back_big() const
{
  #if BYTE_ORDER == BIG_ENDIAN
    auto b = end() - sizeof(T);
    auto e = end();
  #elif BYTE_ORDER == LITTLE_ENDIAN
    auto b = rbegin();
    auto e = rbegin() + sizeof(T);
  #else
    #error "Unknown byte order";
  #endif

    return _get_trivial<T>( b, e );
}
//=======================================================================================
template<typename T>
T VByteArray::pop_front_little()
{
    auto res = front_little<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VByteArray::pop_front_big()
{
    auto res = front_big<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VByteArray::pop_back_little()
{
    auto res = back_little<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VByteArray::pop_back_big()
{
    auto res = back_big<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T, typename Iter>
T VByteArray::_get_trivial( const Iter& b, const Iter& e ) const
{
    static_assert( std::is_trivial<T>::value, "Value is not trivial." );

    if( size() < sizeof(T) )
        throw std::out_of_range( "VByteaArray: size() < sizeof(T)" );

    T res;
    void *vptr = &res;
    auto *dest_ptr = static_cast<value_type*>(vptr);

    std::copy( b, e, dest_ptr );

    return res;
}
//=======================================================================================


//=======================================================================================
template<typename T>
void VByteArray::push_front_little( const T& val )
{
    _push_front_trivial( val, _is_little_endian() );
}
//=======================================================================================
template<typename T>
void VByteArray::push_back_little( const T& val )
{
    _push_back_trivial( val, _is_little_endian() );
}
//=======================================================================================
template<typename T>
void VByteArray::push_front_big( const T& val )
{
    _push_front_trivial( val, !_is_little_endian() );
}
//=======================================================================================
template<typename T>
void VByteArray::push_back_big( const T& val )
{
    _push_back_trivial( val, !_is_little_endian() );
}
//=======================================================================================
template<typename T>
void VByteArray::_push_front_trivial(const T& val, bool not_reverse )
{
    VByteArray bval;
    bval._push_back_trivial( val, not_reverse );
    prepend(bval);
}
//=======================================================================================
template<typename T>
void VByteArray::_push_back_trivial( const T& val, bool not_reverse )
{
    static_assert( std::is_trivial<T>::value, "Value is not trivial." );

    const void *vptr = &val;
    auto src = static_cast<const value_type*>(vptr);

    auto end_it = src + sizeof(T);
    auto inserter = std::back_inserter(*this);

    if (not_reverse)
        std::copy( src, end_it, inserter );
    else
        std::reverse_copy( src, end_it, inserter );
}
//=======================================================================================

VByteArray operator + ( VByteArray lhs, const VByteArray &rhs );


#endif // VBYTEARRAY_H
