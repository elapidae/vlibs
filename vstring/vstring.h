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


#ifndef VSTRING_H
#define VSTRING_H

#include <string>
#include <vector>
#include <stdexcept>
#include <linux/swab.h>
#include <algorithm>
#include <sstream>

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
 *  UPD 04-10-2018
 *  Выпилены статические проверки соответствия типов, вместо них введено автоопределение
 *  арифметических типов через std::enable_if.
 *  -------------------------------------------------------------------------------------
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

    static bool is_hex_symbol( char ch );
    //-----------------------------------------------------------------------------------
    VString& prepend( const std::string &s );
    VString& append ( const std::string &s );

    template<typename It> VString& prepend ( It b, It e );  // Только для
    template<typename It> VString& append  ( It b, It e );  // однобайтовых типов.

    VString& prepend ( char ch );
    VString& append  ( char ch );
    //-----------------------------------------------------------------------------------
    template<typename T> VString& prepend_LE ( T val );
    template<typename T> VString& prepend_BE ( T val );

    template<typename T> VString& append_LE  ( T val );
    template<typename T> VString& append_BE  ( T val );

    template<typename T> VString& append_as_sys ( const T& val );
    template<typename T> VString& prepend_as_sys( const T& val );
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

    char take_front_ch();
    char take_back_ch();

    VString take_front_str ( size_t sz );
    VString take_back_str  ( size_t sz );

    //-----------------------------------------------------------------------------------
    //  Удаление n символов с разных сторон.
    //  Если размер меньше n, оставляет строку пустой.
    void chop_front ( size_t n );
    void chop_back  ( size_t n );

    //-----------------------------------------------------------------------------------
    //  Проверяет наличие указанной строки в начале/конце.
    bool begins_with ( const std::string& what ) const;
    bool ends_with   ( const std::string& what ) const;

    //-----------------------------------------------------------------------------------
    ///  Возвращает строку без начальных и конечных пробелов (детектирование пробелов
    ///  функцией isspace(), а также '\n' ).
    VString trimmed() const;

    Vector split( char splitter ) const;
    Vector split_without_empties( char splitter ) const;

    /// Разрезает текст, используя разделители всех мастей. Пустых не берем.
    Vector split_by_spaces() const;

    /// Проверяет символ функцией std::isspace (22.1.3 Convenience interfaces),
    /// NB! перенос строки \\n также считается пробелом!
    static bool is_any_space( char ch );
    //-----------------------------------------------------------------------------------
    /// Выворачивает байты наизнанку, т.е. <LE> <-> <BE>.
    template<typename T>
    static typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    reverse_T( T src );
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    // NB! Пока используется ForwardView нельзя изменять исходную строку!
    class ForwardView;
    ForwardView forward_view() const;
    // NB! Пока используется ForwardView нельзя изменять исходную строку!
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //  NB! Методы text_to_any() и any_to_text() не делают никаких внутренних проверок!
    //  Это просто обертки для вызовов поточного вывода через std::sstream;
    //  Сделаны, чтобы каждый раз не создавать это уродство с поточным вводом-выводом.
    template<typename T>
    T text_to_any() const;

    template<typename T>
    static T text_to_any( const std::string& val );

    template<typename T>
    static std::string any_to_text( const T& val );
    //-----------------------------------------------------------------------------------

private:
    template<typename T> typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    _back_sys() const;

    template<typename T> typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    _front_sys() const;

    void _check_enough_size( size_t sz ) const;
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

    int  remained() const;
    bool finished() const;

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
#include "_vstring_impl.h"
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================


#endif // VSTRING_H
