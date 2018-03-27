#ifndef VSTRING_H
#define VSTRING_H

#include <string>
#include <vector>
#include <stdexcept>

//=======================================================================================
/*  2018-02-02
 *
 *  VString  -- буфер для сырых данных. Также может использоваться для удобства, если
 * есть пожелания касательно добавления к-л функциональности, милости прошу.
 *
*/
//=======================================================================================




//=======================================================================================
//      VString
//=======================================================================================
class VString : public std::string
{
public:
    using vector = std::vector<VString>;

    //-----------------------------------------------------------------------------------
    // Часть конструкторов приходится перегружать...
    using std::string::string;
    VString()                           noexcept;
    VString( std::string &&str )        noexcept;
    VString( const std::string &str );

    VString( VString &&str )                    = default;
    VString( const VString &str )               = default;
    VString& operator = ( VString &&str )       = default;
    VString& operator = ( const VString &str )  = default;

    //-----------------------------------------------------------------------------------
    // Нечувствительна к регистру, все символы, кроме набора hex игнорируются.
    // NB! При нечетном количестве годных символов, считается, что первый -- ноль.
    static VString from_hex( const std::string &src );

    VString tohex () const;  // сплошным текстом, строчными.
    VString toHex () const;  // сплошным текстом, Заглавными.
    VString to_hex() const;  // с пробелами, строчными.
    VString to_Hex() const;  // с пробелами, Заглавными.

    //-----------------------------------------------------------------------------------
    void prepend ( const std::string &s );
    template<typename It> void prepend ( It b, It e );  // Только для однобайтовых типов.

    //-----------------------------------------------------------------------------------
    template<typename T> void prepend_LE ( T val );
    template<typename T> void prepend_BE ( T val );

    template<typename T> void append_LE  ( T val );
    template<typename T> void append_BE  ( T val );

    //-----------------------------------------------------------------------------------
    template<typename T> T front_LE() const;
    template<typename T> T front_BE() const;

    template<typename T> T back_LE()  const;
    template<typename T> T back_BE()  const;

    //-----------------------------------------------------------------------------------
    template<typename T> T take_front_LE();
    template<typename T> T take_front_BE();

    template<typename T> T take_back_LE();
    template<typename T> T take_back_BE();

    char take_front();
    char take_back();

    void append_byte_string     ( const std::string &str ); // throw error if bigger 255
    void append_word_string_LE  ( const std::string &str ); // throw error if bigger 2^16
    void append_dword_string_LE ( const std::string &str ); // throw error if bigger 2^32

    //-----------------------------------------------------------------------------------
    // удаление n символов с разных сторон.
    // Если размер меньше n, оставляет строку пустой.
    void chop_front ( size_t n );
    void chop_back  ( size_t n );

    //-----------------------------------------------------------------------------------
    bool begins_with ( const std::string &what ) const;
    bool ends_with   ( const std::string &what ) const;

    //-----------------------------------------------------------------------------------
    std::vector<std::string> split( char splitter ) const;
    std::vector<std::string> split_without_empties( char splitter ) const;

    //-----------------------------------------------------------------------------------
    // Выворачивает наизнанку. Не особо касается этого класса, но может пригодится.
    template<typename T> static T reverse_T( T src );
    //-----------------------------------------------------------------------------------


private:
    template<typename T> void _append_sys   ( const T &val );
    template<typename T> void _prepend_sys  ( const T &val );

    template<typename T> T _back_sys()   const;
    template<typename T> T _front_sys()  const;

    static void _check_big_or_little_endian();
    template<typename T> static void _check_that_arithmetic_and_1_2_4_8();
    template<typename T> void _check_that_arithmetic_and_enough_size() const;
};
//=======================================================================================
//      VString
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
//      Public wrappers
//=======================================================================================
template<typename T>
void VString::append_LE( T val )
{
    _check_big_or_little_endian();
    #if BYTE_ORDER == BIG_ENDIAN
    return _append_sys( reverse_T(val) );
    #else
    return _append_sys( val );
    #endif
}
//=======================================================================================
template<typename T>
void VString::append_BE( T val )
{
    _check_big_or_little_endian();
    #if BYTE_ORDER == BIG_ENDIAN
    return _append_sys( val );
    #else
    return _append_sys( reverse_T(val) );
    #endif
}
//=======================================================================================
template<typename T>
void VString::prepend_LE( T val )
{
    _check_big_or_little_endian();
    #if BYTE_ORDER == BIG_ENDIAN
    return _prepend_sys( reverse_T(val) );
    #else
    return _prepend_sys( val );
    #endif
}
//=======================================================================================
template<typename T>
void VString::prepend_BE( T val )
{
    _check_big_or_little_endian();
    #if BYTE_ORDER == BIG_ENDIAN
    return _prepend_sys( val );
    #else
    return _prepend_sys( reverse_T(val) );
    #endif
}
//=======================================================================================
//=======================================================================================
template<typename T>
T VString::back_BE() const
{
    _check_big_or_little_endian();
    #if BYTE_ORDER == BIG_ENDIAN
    return _back_sys<T>();
    #else
    return reverse_T( _back_sys<T>() );
    #endif
}
//=======================================================================================
template<typename T>
T VString::back_LE() const
{
    _check_big_or_little_endian();
    #if BYTE_ORDER == BIG_ENDIAN
    return reverse_T( _back_sys<T>() );
    #else
    return _back_sys<T>();
    #endif
}
//=======================================================================================
template<typename T>
T VString::front_BE() const
{
    _check_big_or_little_endian();
    #if BYTE_ORDER == BIG_ENDIAN
    return _front_sys<T>();
    #else
    return reverse_T( _front_sys<T>() );
    #endif
}
//=======================================================================================
template<typename T>
T VString::front_LE() const
{
    _check_big_or_little_endian();
    #if BYTE_ORDER == BIG_ENDIAN
    return reverse_T( _front_sys<T>() );
    #else
    return _front_sys<T>();
    #endif
}
//=======================================================================================
//      Public wrappers
//=======================================================================================
//      Checking types
//=======================================================================================
template<typename T>
void VString::_check_that_arithmetic_and_1_2_4_8()
{
    static_assert( std::is_arithmetic<T>::value, "!std::is_arithmetic<T>::value" );
    static_assert( sizeof(T) == 1 || sizeof(T) == 2 ||
                   sizeof(T) == 4 || sizeof(T) == 8, "Strange size of arithmetic type" );
}
//=======================================================================================
template<typename T>
void VString::_check_that_arithmetic_and_enough_size() const
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    if ( size() < sizeof(T) )
        throw std::out_of_range("VString: remained size less than need T size.");
}
//=======================================================================================
//      Checking types
//=======================================================================================
//      append & prepend
//=======================================================================================
template<typename T>
void VString::_append_sys( const T &val )
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    auto * ch = static_cast<const char*>( static_cast<const void*>(&val) );
    append( ch, sizeof(T) );
}
//=======================================================================================
template<typename T>
void VString::_prepend_sys( const T &val )
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    auto * ch = static_cast<const char*>( static_cast<const void*>(&val) );
    insert( 0, ch, sizeof(T) );
}
//=======================================================================================
template<typename It>
void VString::prepend( It b, It e )
{
    static_assert( sizeof(*b) == 1, "sizeof(It::value_type) != 1" );
    insert( begin(), b, e );
}
//=======================================================================================
//      append & prepend
//=======================================================================================
//      front, back & pop_front, pop_back
//=======================================================================================
template<typename T>
T VString::take_front_LE()
{
    auto res = front_LE<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VString::take_front_BE()
{
    auto res = front_BE<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VString::take_back_LE()
{
    auto res = back_LE<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VString::take_back_BE()
{
    auto res = back_BE<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VString::_front_sys() const
{
    _check_that_arithmetic_and_enough_size<T>();

    T res;
    auto *ch = static_cast<char*>(static_cast<void*>(&res));

    std::copy( begin(), begin() + sizeof(T), ch );
    return res;
}
//=======================================================================================
template<typename T>
T VString::_back_sys() const
{
    _check_that_arithmetic_and_enough_size<T>();

    T res;
    auto *ch = static_cast<char*>( static_cast<void*>(&res) );

    std::copy( end() - sizeof(T), end(), ch );
    return res;
}
//=======================================================================================
template<typename T>
T VString::reverse_T( T val )
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    auto *ch = static_cast<char*>( static_cast<void*>(&val) );

    constexpr auto tsize = sizeof(T);
    switch ( tsize )
    {
    case 8: std::swap( ch[3], ch[tsize-4] );
            std::swap( ch[2], ch[tsize-3] );
    case 4: std::swap( ch[1], ch[tsize-2] );
    case 2: std::swap( ch[0], ch[tsize-1] );
    }
    return val;
}
//=======================================================================================
//      front, back & pop_front, pop_back
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================


#endif // VSTRING_H
