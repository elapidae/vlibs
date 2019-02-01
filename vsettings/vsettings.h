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


#ifndef VSETTINGS_H
#define VSETTINGS_H

#include <memory>
#include <stdint.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "vstring.h"

//=======================================================================================

class VSettings final
{
public:
    using str      = std::string;           using cstr      = const str&;
    using vec_str  = std::vector<str>;      using cvec_str  = const vec_str&;

    class Schema;
    Schema& schema();

    explicit VSettings();
    explicit VSettings( const VString& ini_data );
    ~VSettings();

    void enter_group( cstr name );
    void leave_group();
    void leave_to_root_group();
    int  group_level()   const; //  Вложенность текущей группы. 0 -- root группа.
    cstr    cur_group()  const;
    vec_str cur_groups() const;
    vec_str cur_keys()   const;

    std::string view()   const;  //  Выносится только первая группа.

    //  Добавляются построчно. Можно накидывать много.
    void add_comment  ( cstr     comment  );
    void add_comments ( cvec_str comments );

    const VString& get( cstr key ) const;
    void set( cstr key, const VString& val );

private:
    class Pimpl; std::unique_ptr<Pimpl> p;
};

//=======================================================================================

class VSettings::Schema
{
public:
    using vec_int = std::vector<int64_t>;   using cvec_int = const vec_int&;
    using vec_dbl = std::vector<double>;    using cvec_dbl = const vec_dbl&;

    template<typename T> class validator;

    void enter_group( cstr name );
    void leave_group();

    template<typename T>
    void append( cstr key, T* dst, cstr comment = str() );

    template<typename T>
    void append( cstr key, T* dst, const validator<T>& validator, cstr comment = str() );

private:
    class Pimpl; std::unique_ptr<Pimpl> p;
};
//=======================================================================================
template<typename T>
class VSettings::Schema::validator
{
public:
    validator(); // not activated
    validator( const T& min, const T& max ); // activated

    bool is_valid( const T& val ) const;

private:
    bool _activated = false;
    T _min;
    T _max;
};
//=======================================================================================

#endif // VSETTINGS_H
