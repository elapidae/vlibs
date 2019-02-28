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


#ifndef VGIO_KEYFILE_H
#define VGIO_KEYFILE_H

#include <vector>
#include "vgio_error.h"
#include <stdint.h>

//=======================================================================================
/**
 *      KeyFile -- обертка над GKeyFile из GIO.
 *
 *  Задачи класса:
 *      - автоматизировать выделение/освобождение памяти;
 *      - обернуть plain-c вызовы;
 *      - следить за появлением ошибок;
 *
 *
 * NB! Методы, принимающие указатели на Error, в случае возникновения ошибки, ведут
 *     себя следующим образом: если передали реальный указатель на ошибку, то она будет
 *     устанавлена. А вот если передали nullptr, методы бросят исключение NException.
 *
 *
 *  Инициализация объекта возможна через статические методы
 *  from_data(string), from_file(filename) или создать пустой через конструктор
 *  по умолчанию.
 *
 *  Класс включает группы методов:
 *  T    get_T  ( group, key, *err = nullptr ); // читаем.
 *  T    safe_T ( group, key, default_value );  // читаем, если ошибка, получаем
 *                                              // значение по умолчанию.
 *  bool set_T  ( group, key, value );          // пишем значения.
 *
 *  // проверочные и обходные методы:
 *  bool        is_valid();
 *  StringList  get_groups();
 *  string      get_start_group();
 *  bool        has_group ( group );
 *  bool        has_key   ( group, key, *Error );
 *  StringList  get_keys  ( group, *Error );
 *
 *  // удаляем:
 *  bool remove_group   ( group, *Error );
 *  bool remove_key     ( group, key, *Error );
 *  bool remove_comment ( group, key, *Error );
**/
//=======================================================================================



//=======================================================================================
typedef struct _GKeyFile GKeyFile;
//=======================================================================================
namespace vgio
{
    //===================================================================================
    //      KeyFile
    //===================================================================================
    class KeyFile final
    {
        static constexpr char _default_list_separator = ';';
    public:
        //-------------------------------------------------------------------------------
        using StringList = std::vector<std::string>;
        using BoolList   = std::vector<bool>;
        using IntList    = std::vector<int>;
        using DoubleList = std::vector<double>;
        using str        = std::string;
        using cstr       = const str &;
        //-------------------------------------------------------------------------------

        static KeyFile from_file( cstr fname, Error *err = nullptr );
        static KeyFile from_data( cstr data,  Error *err = nullptr );

        explicit KeyFile();

        bool is_valid() const;

        str  to_data( Error *err = nullptr ) const;
        bool to_file( cstr fname, Error *err = nullptr );
        //-------------------------------------------------------------------------------
        // Выставление обязательно перед использованием методов списков *_list().
        void set_list_separator( char sep );

        bool has_group( cstr group )    const;
        StringList get_groups()         const;
        str get_start_group()           const;

        bool has_key ( cstr group, cstr key, Error *err = nullptr ) const;
        StringList get_keys ( cstr group, Error *err = nullptr ) const;
        //-------------------------------------------------------------------------------

        str      get_string ( cstr group, cstr key, Error *err = nullptr ) const;
        bool     get_bool   ( cstr group, cstr key, Error *err = nullptr ) const;
        int      get_int    ( cstr group, cstr key, Error *err = nullptr ) const;
        double   get_double ( cstr group, cstr key, Error *err = nullptr ) const;

        StringList get_string_list ( cstr group, cstr key, Error *err = nullptr ) const;
        BoolList   get_bool_list   ( cstr group, cstr key, Error *err = nullptr ) const;
        IntList    get_int_list    ( cstr group, cstr key, Error *err = nullptr ) const;
        DoubleList get_double_list ( cstr group, cstr key, Error *err = nullptr ) const;

        str get_comment( cstr group, cstr key, Error *err = nullptr ) const;
        //-------------------------------------------------------------------------------

        //-------------------------------------------------------------------------------
        //  Safety methods, don't throw exceptions, returns default vals.
        str      safe_string ( cstr group, cstr key, cstr   defval = ""    ) const;
        bool     safe_bool   ( cstr group, cstr key, bool   defval = false ) const;
        int      safe_int    ( cstr group, cstr key, int    defval = 0     ) const;
        double   safe_double ( cstr group, cstr key, double defval = 0     ) const;

        StringList safe_string_list ( cstr group, cstr key,
                                      const StringList &defval = StringList() ) const;

        BoolList   safe_bool_list   ( cstr group, cstr key,
                                      const BoolList &defval = BoolList() ) const;

        IntList    safe_int_list    ( cstr group, cstr key,
                                      const IntList &defval = IntList() ) const;

        DoubleList safe_double_list ( cstr group, cstr key,
                                      const DoubleList &defval = DoubleList() ) const;

        str safe_comment( cstr group, cstr key, cstr defval ) const;
        //-------------------------------------------------------------------------------

        void set_string ( cstr group, cstr key, cstr    val );
        void set_bool   ( cstr group, cstr key, bool    val );
        void set_int    ( cstr group, cstr key, int     val );
        void set_double ( cstr group, cstr key, double  val );

        void set_string_list ( cstr group, cstr key, const StringList &val );
        void set_bool_list   ( cstr group, cstr key, const BoolList   &val );
        void set_int_list    ( cstr group, cstr key, const IntList    &val );
        void set_double_list ( cstr group, cstr key, const DoubleList &val );

        bool set_comment ( cstr group, cstr key, cstr val, Error *err = nullptr );
        //-------------------------------------------------------------------------------

        bool remove_group   ( cstr group, Error *err = nullptr );
        bool remove_key     ( cstr group, cstr key, Error *err = nullptr );
        bool remove_comment ( cstr group, cstr key, Error *err = nullptr );


        //-------------------------------------------------------------------------------
    private:
        std::shared_ptr<GKeyFile> p;

        template<typename T, typename GSizeType, typename gFn>
        std::vector<T> _get_any_simple_list( cstr group, cstr key,
                                             gFn fn, Error *err = nullptr ) const;
        static void _g_free(void *ptr);
    };
    //===================================================================================
    //      vgio::KeyFile
    //===================================================================================



    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    template<typename T, typename GSizeType, typename gFn>
    std::vector<T> KeyFile::_get_any_simple_list( cstr group, cstr key,
                                                   gFn fn, Error *err ) const
    {
        _impl::error_proxy err_proxy( err );
        GSizeType len;
        auto * ptr = fn( p.get(), group.c_str(), key.c_str(), &len, err_proxy );

        auto res = ptr ? std::vector<T>(ptr, ptr + len) : std::vector<T>();
        if (ptr) _g_free(ptr);
        err_proxy.flush();
        return res;
    }
    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
} // namespace vgio
//=======================================================================================



#endif // VGIO_KEYFILE_H
