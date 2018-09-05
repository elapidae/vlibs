#ifndef VSTRING_H
#define VSTRING_H

#include <string>
#include <vector>
#include <stdexcept>
#include <linux/swab.h>
#include <algorithm>

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
    using Vector = std::vector<VString>;

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
    void prepend( const std::string &s );
    template<typename It> void prepend ( It b, It e );  // Только для однобайтовых типов.

    void append( const std::string &s );
    template<typename It> void append ( It b, It e );  // Только для однобайтовых типов.

    void prepend ( char ch );
    void append  ( char ch );
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

    VString front_str ( size_t sz ) const;
    VString back_str  ( size_t sz ) const;
    //-----------------------------------------------------------------------------------
    template<typename T> T take_front_LE();
    template<typename T> T take_front_BE();

    template<typename T> T take_back_LE();
    template<typename T> T take_back_BE();

    char take_front();
    char take_back();

    VString take_front_str ( size_t sz );
    VString take_back_str  ( size_t sz );

    //-----------------------------------------------------------------------------------
    //  Удаление n символов с разных сторон.
    //  Если размер меньше n, оставляет строку пустой.
    void chop_front ( size_t n );
    void chop_back  ( size_t n );

    //-----------------------------------------------------------------------------------
    bool begins_with ( const std::string& what ) const;
    bool ends_with   ( const std::string& what ) const;

    //  Возвращает строку без начальных и конечных пробелов (детектирование пробелов
    //  функцией isspace(), а также '\n' ).
    VString trimmed() const;

    //-----------------------------------------------------------------------------------
    Vector split( char splitter ) const;
    Vector split_without_empties( char splitter ) const;

    // Разрезает текст, используя разделители всех мастей. Пустых не берем.
    Vector split_by_spaces() const;

    //-----------------------------------------------------------------------------------
    // Выворачивает байты наизнанку, т.е. <LE> <-> <BE>.
    template<typename T> static T reverse_T( T src );
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    class ForwardView;
    ForwardView forward_view() const;
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
//      FORWARD VIEW
//=======================================================================================
class VString::ForwardView
{
public:
    //-----------------------------------------------------------------------------------

    size_t remained() const;
    bool   finished() const;

    //-----------------------------------------------------------------------------------

    template<typename T> T show_LE()  const;
    template<typename T> T show_BE()  const;

    VString show_str( size_t sz ) const;

    //-----------------------------------------------------------------------------------

    template<typename T> T take_LE();
    template<typename T> T take_BE();

    VString take_str( size_t sz );

    //-----------------------------------------------------------------------------------

    char     show_ch()        const         { return show_LE<char>();       }
    int8_t   show_i8()        const         { return show_LE<int8_t>();     }
    uint8_t  show_u8()        const         { return show_LE<uint8_t>();    }

    int16_t  show_i16_LE()    const         { return show_LE<int16_t>();    }
    int16_t  show_i16_BE()    const         { return show_BE<int16_t>();    }
    uint16_t show_u16_LE()    const         { return show_LE<uint16_t>();   }
    uint16_t show_u16_BE()    const         { return show_BE<uint16_t>();   }

    int32_t  show_i32_LE()    const         { return show_LE<int32_t>();    }
    int32_t  show_i32_BE()    const         { return show_BE<int32_t>();    }
    uint32_t show_u32_LE()    const         { return show_LE<uint32_t>();   }
    uint32_t show_u32_BE()    const         { return show_BE<uint32_t>();   }

    int64_t  show_i64_LE()    const         { return show_LE<int64_t>();    }
    int64_t  show_i64_BE()    const         { return show_BE<int64_t>();    }
    uint64_t show_u64_LE()    const         { return show_LE<uint64_t>();   }
    uint64_t show_u64_BE()    const         { return show_BE<uint64_t>();   }


    float    show_float_LE()  const         { return show_LE<float>();      }
    float    show_float_BE()  const         { return show_BE<float>();      }

    double   show_double_LE() const         { return show_LE<double>();     }
    double   show_double_BE() const         { return show_BE<double>();     }

    //-----------------------------------------------------------------------------------

    char     take_ch()                      { return take_LE<char>();       }
    int8_t   take_i8()                      { return take_LE<int8_t>();     }
    uint8_t  take_u8()                      { return take_LE<uint8_t>();    }

    int16_t  take_i16_LE()                  { return take_LE<int16_t>();    }
    int16_t  take_i16_BE()                  { return take_BE<int16_t>();    }
    uint16_t take_u16_LE()                  { return take_LE<uint16_t>();   }
    uint16_t take_u16_BE()                  { return take_BE<uint16_t>();   }

    int32_t  take_i32_LE()                  { return take_LE<int32_t>();    }
    int32_t  take_i32_BE()                  { return take_BE<int32_t>();    }
    uint32_t take_u32_LE()                  { return take_LE<uint32_t>();   }
    uint32_t take_u32_BE()                  { return take_BE<uint32_t>();   }

    int64_t  take_i64_LE()                  { return take_LE<int64_t>();    }
    int64_t  take_i64_BE()                  { return take_BE<int64_t>();    }
    uint64_t take_u64_LE()                  { return take_LE<uint64_t>();   }
    uint64_t take_u64_BE()                  { return take_BE<uint64_t>();   }


    float    take_float_LE()                { return take_LE<float>();      }
    float    take_float_BE()                { return take_BE<float>();      }

    double   take_double_LE()               { return take_LE<double>();     }
    double   take_double_BE()               { return take_BE<double>();     }

    //-----------------------------------------------------------------------------------

private:
    const char *_buffer;
    size_t      _remained;

    friend class VString;
    ForwardView( const VString *owner );
};
//=======================================================================================
//      FORWARD VIEW
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================


//=======================================================================================
//      VString
//      Constructors
//=======================================================================================
template <class InputIterator>
VString::VString( InputIterator first, InputIterator last )
    : std::string( first, last )
{}
//=======================================================================================
//      Constructors
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
//      append & prepend
//=======================================================================================
template<typename T>
void VString::_append_sys( const T &val )
{
    _check_that_arithmetic_and_1_2_4_8<T>();

    auto * ch = static_cast<const char*>( static_cast<const void*>(&val) );
    insert( size(), ch, sizeof(T) );
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
template<typename It>
void VString::append( It b, It e )
{
    static_assert( sizeof(*b) == 1, "sizeof(It::value_type) != 1" );
    insert( end(), b, e );
}
//=======================================================================================
//      append & prepend
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
    std::reverse( ch, ch + sizeof(T) );
    return val;

//  Эта гадость такое с float и double делает, что потом их не узнать вообще.
//    switch ( sizeof(T) )
//    {
//    case 2: return static_cast<T>( __swab16(val) );
//    case 4: return static_cast<T>( __swab32(val) );
//    case 8: return static_cast<T>( __swab64(val) );
//    }
//    return val; // Для единичного размера.
}
//=======================================================================================
//      front, back & pop_front, pop_back
//      VString
//=======================================================================================


//=======================================================================================
//      FORWARD VIEW
//=======================================================================================
template<typename T>
T VString::ForwardView::show_LE() const
{
    if ( _remained < sizeof(T) )
        throw std::out_of_range( "VString::ForwardView::show_LE<T>(): not enouth data" );

    auto res = * static_cast<const T*>( static_cast<const void*>(_buffer) );

    #if   BYTE_ORDER == LITTLE_ENDIAN
    #elif BYTE_ORDER == BIG_ENDIAN
    res = VString::reverse_T( res );
    #else
    #error "Unknown byte order"
    #endif

    return res;
}
//=======================================================================================
template<typename T>
T VString::ForwardView::show_BE() const
{
    if ( _remained < sizeof(T) )
        throw std::out_of_range( "VString::ForwardView::take_BE<T>(): not enouth data" );

    auto res = * static_cast<const T*>( static_cast<const void*>(_buffer) );

    #if BYTE_ORDER == LITTLE_ENDIAN
    res = VString::reverse_T( res );
    #elif BYTE_ORDER == BIG_ENDIAN
    #else
    #error "Unknown byte order"
    #endif

    return res;
}
//=======================================================================================
template<typename T>
T VString::ForwardView::take_LE()
{
    auto res = show_LE<T>();

    _remained -= sizeof(T);
    _buffer   += sizeof(T);

    return res;
}
//=======================================================================================
template<typename T>
T VString::ForwardView::take_BE()
{
    auto res = show_BE<T>();

    _remained -= sizeof(T);
    _buffer   += sizeof(T);

    return res;
}
//=======================================================================================
//      FORWARD VIEW
//=======================================================================================




#endif // VSTRING_H
