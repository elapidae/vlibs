#ifndef VSTRING_H
#define VSTRING_H

#include <string>
#include <vector>
#include <stdexcept>
#include <linux/swab.h>

//=======================================================================================
/*  2018-02-02
 *
 *  VString  -- буфер для сырых данных. Также может использоваться для удобства, если
 *  есть пожелания касательно добавления к-л функциональности, милости прошу.
 *
 *  Аббревиатуры BE/LE означают Big/Little Endian соответственно (идею честно подглядел
 *  на SDK лидаров).
 *  -------------------------------------------------------------------------------------
 *  UPD 17-08-2018
 *  Были реализованы все конструкторы из Стандарта, список которых был взят отсюда:
 *  http://www.cplusplus.com/reference/string/string/string/
 *
 *  Таким образом получена совместимость со старым компилятором, не поддерживающим
 *  using std::string::string;
 *
 *  Заодно, конструкторы само-в-коде-документированы.
 *  -------------------------------------------------------------------------------------
 *  UPD 21-08-2018
 *  Реверс между Little <-> Big endian реализован православным для линукса способом
 *  (через __swab(), он, по идее, транслируется в bswap).
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
    // Все конструкторы проксированы.

    VString()                                     noexcept;             // Default    (1)
    VString( const std::string& str );                                  // Copy       (2)

    VString( const std::string& str, size_t pos, size_t len = npos );   // Substring  (3)
    VString( const char* s );                                           // C-string   (4)
    VString( const char* s, size_t n );                                 // Buffer     (5)
    VString( size_t n, char c );                                        // Fill       (6)

    template <class InputIterator>
    VString( InputIterator first, InputIterator last );                 // Range      (7)

    VString( const std::initializer_list<char>& il );                   // Init list  (8)
    VString( std::string&& str )                  noexcept;             // Move       (9)


    VString( VString&& str )                    = default;
    VString( const VString& str )               = default;
    VString& operator = ( VString&& str )       = default;
    VString& operator = ( const VString& str )  = default;

    //-----------------------------------------------------------------------------------
    // Нечувствительна к регистру, все символы, кроме набора hex игнорируются.
    // NB! При нечетном количестве годных символов, считается, что первый -- ноль.
    static VString from_hex( const std::string &src );
    VString from_hex() const;

    VString tohex () const;                         // сплошным текстом, строчными.
    VString toHex () const;                         // сплошным текстом, Заглавными.
    VString to_hex( char separator = ' ' ) const;   // с разделителями, строчными.
    VString to_Hex( char separator = ' ' ) const;   // с разделителями, Заглавными.

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

    //-----------------------------------------------------------------------------------
    //  Методы - ускорители. Sized строками называются строки, перед которыми стоит их
    //  размер. Т.е. <size><string_data>. Размеры могут храниться в байтах, словах и
    //  двойных словах, притом слова и двойные слова размеров могут быть записаны
    //  в Big и little endian.
    //  В названиях, соответственно, размер в байтах указан после слова sized.
    //  Размер устанавливается перед строкой, читать можно только с начала.
    //
    //  Реализованы только append_* методы, т.к. с prepend совсем уж мясо получается,
    //  начинает хромать логика применения. Если что, пользуйтесь составными методами.

    void append_sized1_string     ( const std::string& str );

    void append_sized2_string_LE  ( const std::string& str );
    void append_sized2_string_BE  ( const std::string& str );

    void append_sized4_string_LE  ( const std::string& str );
    void append_sized4_string_BE  ( const std::string& str );

    //-----------------------------------------------------------------------------------
    // удаление n символов с разных сторон.
    // Если размер меньше n, оставляет строку пустой.
    void chop_front ( size_t n );
    void chop_back  ( size_t n );

    //-----------------------------------------------------------------------------------
    bool begins_with ( const std::string& what ) const;
    bool ends_with   ( const std::string& what ) const;

    // Возвращает строку без начальных и конечных пробелов (функция isspace()).
    VString trimmed() const;

    // Разрезает текст, используя разделители всех мастей. Пустых не берем.
    std::vector<VString> split_by_spaces() const;

    //-----------------------------------------------------------------------------------
    VString left  ( size_t sz ) const;
    VString right ( size_t sz ) const;

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
//      Constructors
//=======================================================================================
template <class InputIterator>
VString::VString( InputIterator first, InputIterator last )
    : std::string( first, last )
{}
//=======================================================================================
//      Constructors
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

    switch ( sizeof(T) )
    {
    case 2: return __swab16( val );
    case 4: return __swab32( val );
    case 8: return __swab64( val );
    }

    return val; // Для единичного размера.
}
//=======================================================================================
//      front, back & pop_front, pop_back
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================


#endif // VSTRING_H
