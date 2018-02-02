#ifndef VSTRINGREF_H
#define VSTRINGREF_H

#include <string>
#include <vector>
#include <stdexcept>




//=======================================================================================
//      VStringRef
//=======================================================================================
class VStringRef
{
public:
    //-----------------------------------------------------------------------------------
    explicit VStringRef( std::string *data ) noexcept;

    //-----------------------------------------------------------------------------------
    // Нечувствительна к регистру, все символы, кроме набора hex игнорируются.
    // NB! При нечетном количестве годных символов, считается, что первый -- ноль.
    static std::string from_hex( const std::string &src );

    // Сделаны статическими специально, чтобы не было сигнатурной перегрузки c VString.
    static std::string tohex  ( const std::string &s );  // сплошным текстом, строчными.
    static std::string toHex  ( const std::string &s );  // сплошным текстом, Заглавными.
    static std::string to_hex ( const std::string &s );  // с пробелами, строчными.
    static std::string to_Hex ( const std::string &s );  // с пробелами, Заглавными.

    //-----------------------------------------------------------------------------------
    void prepend ( const std::string &s );
    void append  ( const std::string &s );
    template<typename It> void prepend ( It b, It e );   // Только для
    template<typename It> void append  ( It b, It e );   // однобайтовых типов.

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
    // Не особо касается этого класса, но может пригодится.
    template<typename T> static T reverse_T( T src );
    //-----------------------------------------------------------------------------------


private:
    std::string *_data;

    template<typename T> void _append_sys   ( const T &val );
    template<typename T> void _prepend_sys  ( const T &val );

    template<typename T> T _back_sys()   const;
    template<typename T> T _front_sys()  const;

    static inline void _check_big_or_little_endian();
    template<typename T> static inline void _check_that_arithmetic_and_1_2_4_8();
    template<typename T> void _check_that_arithmetic_and_enough_size() const;
};
//=======================================================================================
//      VStringRef
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
//      Public wrappers
//=======================================================================================
template<typename T>
void VStringRef::append_LE( T val )
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
void VStringRef::append_BE( T val )
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
void VStringRef::prepend_LE( T val )
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
void VStringRef::prepend_BE( T val )
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
T VStringRef::back_BE() const
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
T VStringRef::back_LE() const
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
T VStringRef::front_BE() const
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
T VStringRef::front_LE() const
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
void VStringRef::_check_big_or_little_endian()
{
static_assert( BYTE_ORDER == BIG_ENDIAN || BYTE_ORDER == LITTLE_ENDIAN,
               "Unknown byte order" );
}
//=======================================================================================
template<typename T>
void VStringRef::_check_that_arithmetic_and_1_2_4_8()
{
static_assert( std::is_arithmetic<T>::value, "!std::is_arithmetic<T>::value" );
static_assert( sizeof(T) == 1 || sizeof(T) == 2 ||
               sizeof(T) == 4 || sizeof(T) == 8, "Strange size of arithmetic type" );
}
//=======================================================================================
template<typename T>
void VStringRef::_check_that_arithmetic_and_enough_size() const
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    if ( _data->size() < sizeof(T) )
        throw std::out_of_range("VStringRef: remained size less than need T size.");
}
//=======================================================================================
//      Checking types
//=======================================================================================
//      append & prepend
//=======================================================================================
template<typename T>
void VStringRef::_append_sys( const T &val )
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    auto * ch = static_cast<const char*>( static_cast<const void*>(&val) );
    _data->append( ch, sizeof(T) );
}
//=======================================================================================
template<typename T>
void VStringRef::_prepend_sys( const T &val )
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    auto * ch = static_cast<char*>( static_cast<void*>(&val) );
    _data->insert( 0, ch, sizeof(T) );
}
//=======================================================================================
template<typename It>
void VStringRef::prepend( It b, It e )
{
    _data->insert( _data->begin(), b, e );
}
//=======================================================================================
template<typename It>
void VStringRef::append( It b, It e )
{
    _data->append( b, e );
}
//=======================================================================================
//      append & prepend
//=======================================================================================
//      front, back & pop_front, pop_back
//=======================================================================================
template<typename T>
T VStringRef::take_front_LE()
{
    auto res = front_LE<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VStringRef::take_front_BE()
{
    auto res = front_BE<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VStringRef::take_back_LE()
{
    auto res = back_LE<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VStringRef::take_back_BE()
{
    auto res = back_BE<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VStringRef::_front_sys() const
{
    _check_that_arithmetic_and_enough_size<T>();
    T res;
    auto *ch = static_cast<char*>(static_cast<void*>(&res));

    std::copy( _data->begin(), _data->begin() + sizeof(T), ch );
    return res;
}
//=======================================================================================
template<typename T>
T VStringRef::_back_sys() const
{
    _check_that_arithmetic_and_enough_size<T>();

    T res;
    auto *ch = static_cast<char*>(static_cast<void*>(&res));

    std::copy( _data->end() - sizeof(T), _data->end(), ch );
    return res;
}
//=======================================================================================
template<typename T>
T VStringRef::reverse_T( T val )
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    auto *ch = static_cast<char*>(static_cast<void*>(&val));

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





#endif // VSTRINGREF_H
