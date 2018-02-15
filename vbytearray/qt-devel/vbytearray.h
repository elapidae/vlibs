#ifndef VBYTEARRAY_H
#define VBYTEARRAY_H

#include <string>
#include <vector>
#include <stdexcept>


//=======================================================================================
/*  2018-01-25 -- в рамках рефакторинга, оплаты тех. долга.
 *
 * VByteArray -- общий класс для передачи сырых данных, сериализации, десериализации
 * малых и больших объемов данных. Заточен для чтения с обеих сторон, НО,
 * со стороны front извлекаться данные должны медленнее. Можно сериализовывать только
 * простейшие типы (не пихайте сюда к-л структуры).
 *
*/
//=======================================================================================


//=======================================================================================
//      VByteArray
//=======================================================================================
class VByteArray : public std::string
{
public:
    //-----------------------------------------------------------------------------------
    using std::string::string;
    VByteArray();
    VByteArray( const std::string &rhs );

    //template<class Iter>
    //VByteArray( Iter b, Iter e );
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    // Нечувствительна к регистру, все символы, кроме набора hex игнорируются.
    // NB! При нечетном количестве годных символов, считается, что первый -- ноль.
    static VByteArray from_hex( const std::string &src );

    VByteArray tohex()  const;  // сплошным текстом, строчными.
    VByteArray toHex()  const;  // сплошным текстом, Заглавными.
    VByteArray to_hex() const;  // с пробелом между символами, строчными.
    VByteArray to_Hex() const;  // с пробелом между символами, Заглавными.
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    template<typename T> VByteArray& append_LE  ( T val );
    template<typename T> VByteArray& append_BE  ( T val );

    template<typename T> VByteArray& prepend_LE ( T val );
    template<typename T> VByteArray& prepend_BE ( T val );

    //  append() has in std::string
    VByteArray& prepend ( const std::string &s );
    template<typename It> VByteArray& prepend ( It b, It e );
    //-----------------------------------------------------------------------------------
    template<typename T> T front_LE() const;
    template<typename T> T front_BE() const;

    template<typename T> T back_LE()  const;
    template<typename T> T back_BE()  const;
    //-----------------------------------------------------------------------------------
    template<typename T> T pop_front_LE();
    template<typename T> T pop_front_BE();

    template<typename T> T pop_back_LE();
    template<typename T> T pop_back_BE();
    //-----------------------------------------------------------------------------------
    // удаление n символов с разных сторон.
    // Если размер меньше n, оставляет строку пустой.
    void chop_front ( size_t n );
    void chop_back  ( size_t n );
    //-----------------------------------------------------------------------------------
    bool begins_with ( const std::string &mask ) const;
    bool ends_with   ( const std::string &mask ) const;
    //-----------------------------------------------------------------------------------
    std::vector<VByteArray> split( char splitter ) const;
    std::vector<VByteArray> split_without_empties( char splitter ) const;
    //-----------------------------------------------------------------------------------
    //  Класс для последовательного чтения массива с начала вперед.
    //  NB! Как только массив будет изменен, объект станет недействительным.
    class ForwardReader;
    ForwardReader get_forward_reader() const;
    void chop_to_position( const ForwardReader &freader );
    //-----------------------------------------------------------------------------------

private:
    VByteArray _to_hex ( const char *hsyms , bool with_space ) const;

    template<typename T> VByteArray& _append   ( T val );
    template<typename T> VByteArray& _prepend  ( T val );

    template<typename T> T _back()   const;
    template<typename T> T _front()  const;

    friend class ForwardReader;
    template<typename T> static T _reverse_val( T src );

    static inline void _check_big_or_little_endian();
    template<typename T> static inline void _check_that_arithmetic_and_1_2_4_8();
    template<typename T> void _check_that_arithmetic_and_enough_size() const;
};
//=======================================================================================
//  Класс для чтения константной строки только вперед. Читать можно только примитивные,
// арифметические типы и подстроки. Контролируется выход за границы, но не контролируется
// сам массив-источник, если он изменился, результат не определен.
class VByteArray::ForwardReader
{
public:
    VByteArray pop_str(int len);

    template<typename T> T pop_BE();
    template<typename T> T pop_LE();

    int remained_bytes() const;

private:

    template<typename T> T _pop();

    friend class VByteArray;
    ForwardReader(const VByteArray *owner );
    const char *_pos;
    int _remained;
};
//=======================================================================================
//      VByteArray
//=======================================================================================










//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
//      ctors
//=======================================================================================
//template<class Iter>
//VByteArray::VByteArray( Iter b, Iter e )
//{
//    assign(b, e);
//}
//=======================================================================================
//      ctors
//=======================================================================================
//      Public wrappers
//=======================================================================================
template<typename T>
VByteArray& VByteArray::append_LE( T val )
{
    _check_big_or_little_endian();
  #if BYTE_ORDER == BIG_ENDIAN
    return _append( _reverse_val(val) );
  #else
    return _append( val );
  #endif
}
//=======================================================================================
template<typename T>
VByteArray& VByteArray::append_BE( T val )
{
    _check_big_or_little_endian();
  #if BYTE_ORDER == BIG_ENDIAN
    return _append( val );
  #else
    return _append( _reverse_val(val) );
  #endif
}
//=======================================================================================
template<typename T>
VByteArray& VByteArray::prepend_LE( T val )
{
    _check_big_or_little_endian();
  #if BYTE_ORDER == BIG_ENDIAN
    return _prepend( _reverse_val(val) );
  #else
    return _prepend( val );
  #endif
}
//=======================================================================================
template<typename T>
VByteArray& VByteArray::prepend_BE( T val )
{
    _check_big_or_little_endian();
  #if BYTE_ORDER == BIG_ENDIAN
    return _prepend( val );
  #else
    return _prepend( _reverse_val(val) );
  #endif
}
//=======================================================================================
//=======================================================================================
template<typename T>
T VByteArray::back_BE() const
{
    _check_big_or_little_endian();
  #if BYTE_ORDER == BIG_ENDIAN
    return _back<T>();
  #else
    return _reverse_val( _back<T>() );
  #endif
}
//=======================================================================================
template<typename T>
T VByteArray::back_LE() const
{
    _check_big_or_little_endian();
  #if BYTE_ORDER == BIG_ENDIAN
    return _reverse_val( _back<T>() );
  #else
    return _back<T>();
  #endif
}
//=======================================================================================
template<typename T>
T VByteArray::front_BE() const
{
    _check_big_or_little_endian();
  #if BYTE_ORDER == BIG_ENDIAN
    return _front<T>();
  #else
    return _reverse_val( _front<T>() );
  #endif
}
//=======================================================================================
template<typename T>
T VByteArray::front_LE() const
{
    _check_big_or_little_endian();
  #if BYTE_ORDER == BIG_ENDIAN
    return _reverse_val( _front<T>() );
  #else
    return _front<T>();
  #endif
}
//=======================================================================================
//      Public wrappers
//=======================================================================================
//      Checking types
//=======================================================================================
void VByteArray::_check_big_or_little_endian()
{
    static_assert( BYTE_ORDER == BIG_ENDIAN || BYTE_ORDER == LITTLE_ENDIAN,
                   "Unknown byte order" );
}
//=======================================================================================
template<typename T>
void VByteArray::_check_that_arithmetic_and_1_2_4_8()
{
    static_assert( std::is_arithmetic<T>::value, "!std::is_arithmetic<T>::value" );
    static_assert( sizeof(T) == 1 || sizeof(T) == 2 ||
                   sizeof(T) == 4 || sizeof(T) == 8, "Strange size of arithmetic type" );
}
//=======================================================================================
template<typename T>
void VByteArray::_check_that_arithmetic_and_enough_size() const
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    if ( size() < sizeof(T) )
        throw std::out_of_range("VByteArray size less than need T size...");
}
//=======================================================================================
//      Checking types
//=======================================================================================
//      append & prepend
//=======================================================================================
template<typename T>
VByteArray& VByteArray::_append( T val )
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    auto * ch = static_cast<char*>( static_cast<void*>(&val) );
    append( ch, sizeof(T) );

    return *this;
}
//=======================================================================================
template<typename T>
VByteArray& VByteArray::_prepend( T val )
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    auto * ch = static_cast<char*>( static_cast<void*>(&val) );
    insert( 0, ch, sizeof(T) );

    return *this;
}
//=======================================================================================
//template<typename T>
//VByteArray& VByteArray::_reverse_append( T val )
//{
//    return _direct_append( _reverse_val(val) );
//}
//=======================================================================================
//template<typename T>
//VByteArray& VByteArray::_reverse_prepend( T val )
//{
//    return _direct_prepend( _reverse_val(val) );
//}
//=======================================================================================
template<typename It>
VByteArray &VByteArray::prepend( It b, It e )
{
    insert( begin(), b, e );
    return *this;
}
//=======================================================================================
//      append & prepend
//=======================================================================================
//      front, back & pop_front, pop_back
//=======================================================================================
template<typename T>
T VByteArray::pop_front_LE()
{
    auto res = front_LE<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VByteArray::pop_front_BE()
{
    auto res = front_BE<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VByteArray::pop_back_LE()
{
    auto res = back_LE<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VByteArray::pop_back_BE()
{
    auto res = back_BE<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VByteArray::_front() const
{
    T res;
    auto *ch = static_cast<char*>(static_cast<void*>(&res));
    _check_that_arithmetic_and_enough_size<T>();

    std::copy( begin(), begin() + sizeof(T), ch );
    return res;
}
//=======================================================================================
//template<typename T>
//T VByteArray::_reverse_front() const
//{
//    return _reverse_val( _direct_front<T>() );
//}
//=======================================================================================
template<typename T>
T VByteArray::_back() const
{
    _check_that_arithmetic_and_enough_size<T>();

    T res;
    auto *ch = static_cast<char*>(static_cast<void*>(&res));

    std::copy( end() - sizeof(T), end(), ch );
    return res;
}
//=======================================================================================
//template<typename T>
//T VByteArray::_reverse_back() const
//{
//    return _reverse_val( _direct_back<T>() );
//}
//=======================================================================================
template<typename T>
T VByteArray::_reverse_val( T val )
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
//      Old versions of reversing.
//=======================================================================================
//template<typename T>
//VByteArray& VByteArray::_reverse_append( T val )
//{
//    _check_that_arithmetic_and_1_2_4_8<T>();

//    resize( size() + sizeof(T) );
//    auto * ch = static_cast<char*>( static_cast<void*>(&val) );
//    for ( auto it = rbegin(); it < rbegin() + sizeof(T); ++it )
//        *it = *ch++;

//    return *this;
//}
//=======================================================================================
//template<typename T>
//VByteArray& VByteArray::_reverse_prepend( T val )
//{
//    _check_that_arithmetic_and_1_2_4_8<T>();

//    insert( 0, sizeof(T), '\0' );
//    auto dst = begin();

//    auto * ch = static_cast<char*>( static_cast<void*>(&val) );
//    for ( auto it = ch + sizeof(T) - 1; ; --it )
//    {
//        *dst++ = *it;
//        if ( it == ch ) break;
//    }

//    return *this;
//}
//=======================================================================================
//template<typename T>
//T VByteArray::_reverse_front() const
//{
//    return _reverse_val( _direct_front<T>() );
//    T res;
//    auto *ch = static_cast<char*>(static_cast<void*>(&res));
//    _check_that_arithmetic_and_enough_size<T>();

//    for ( auto it = begin() + sizeof(T) - 1; ; --it )
//    {
//        *ch++ = *it;
//        if (it == begin()) break;
//    }
//    return res;
//}
//=======================================================================================
//template<typename T>
//T VByteArray::_reverse_back() const
//{
//    T res;
//    auto *ch = static_cast<char*>(static_cast<void*>(&res));
//    _check_that_arithmetic_and_enough_size<T>();

//    for ( auto it = rbegin(); it != rbegin() + sizeof(T); ++it )
//    {
//        *ch++ = *it;
//    }
//    return res;
//}
//=======================================================================================
//      Old versions of reversing.
//=======================================================================================
//      front, back & pop_front, pop_back
//=======================================================================================
//      FrontReader
//=======================================================================================
template<typename T>
T VByteArray::ForwardReader::pop_BE()
{
    _check_big_or_little_endian();
    _check_that_arithmetic_and_1_2_4_8<T>();

  #if BYTE_ORDER == BIG_ENDIAN
    return _pop<T>();
  #else
    return _reverse_val( _pop<T>() );
  #endif
}
//=======================================================================================
template<typename T>
T VByteArray::ForwardReader::pop_LE()
{
    _check_big_or_little_endian();
    _check_that_arithmetic_and_1_2_4_8<T>();

  #if BYTE_ORDER == BIG_ENDIAN
    return _reverse_val( _pop<T>() );
  #else
    return _pop<T>();
  #endif
}
//=======================================================================================
template<typename T>
T VByteArray::ForwardReader::_pop()
{
    if ( _remained < int(sizeof(T)) )
        throw std::out_of_range("VByteArray::FrontReader::pop<T>()");

    T res = *static_cast<const T*>(static_cast<const void*>(_pos));

    _pos      += sizeof(T);
    _remained -= sizeof(T);

    return res;
}
//=======================================================================================
//      FrontReader
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================




#endif // VBYTEARRAY_H
