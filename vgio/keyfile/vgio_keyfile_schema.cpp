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


#include "vgio_keyfile_schema.h"

#include <assert.h>
#include "verror.h"

//=======================================================================================
/*
 *  08-08-2018
 *
 *  Добавлены методы работы с "малыми" типами (u/i 8/16, float).
 *
 *  Принцип алгоритма такой:
 *  Информация по всем полям собирается в векторе _fileds, поля наследуются от _filed.
 *
 *  В полях, помимо очевидной, хранятся геттер и сеттер от KeyFile. Именно благодаря им
 *  возможно полиморфное поведение полей. Геттеры и сеттеры собраны в структуры
 *  GetSet. Их всего восемь.
 *
 *  Валидаторы прикладываются только к числовым полям. "Малые" типы при любом раскладе
 *  обзаводятся валидаторами, которые, если не установлены более жесткие условия,
 *  проверяют вхождения в допустимый для типа диапазон.
*/
//=======================================================================================

// Для отладки типов...
template<class T>
class TD;

using namespace vgio;

using str  = std::string;
using cstr = const std::string &;


//=======================================================================================
static str group_key_str( cstr group, cstr key )
{
    return "'[" + group + "]" + "/" + key + "'";
}
//=======================================================================================


//=======================================================================================
template<typename Getter, typename Setter>
struct GetSet
{
    GetSet( Getter g, Setter s) : getter(g), setter(s) {}
    Getter getter;
    Setter setter;
};

using Bool_GetSet= GetSet<decltype(&KeyFile::get_bool),decltype(&KeyFile::set_bool)>;
using Int_GetSet = GetSet<decltype(&KeyFile::get_int),decltype(&KeyFile::set_int)>;
using Dbl_GetSet = GetSet<decltype(&KeyFile::get_double),decltype(&KeyFile::set_double)>;
using Str_GetSet = GetSet<decltype(&KeyFile::get_string),decltype(&KeyFile::set_string)>;

using BoolList_GetSet
    = GetSet<decltype(&KeyFile::get_bool_list),decltype(&KeyFile::set_bool_list)>;
using IntList_GetSet
    = GetSet<decltype(&KeyFile::get_int_list),decltype(&KeyFile::set_int_list)>;
using DblList_GetSet
    = GetSet<decltype(&KeyFile::get_double_list),decltype(&KeyFile::set_double_list)>;
using StrList_GetSet
    = GetSet<decltype(&KeyFile::get_string_list),decltype(&KeyFile::set_string_list)>;

static Bool_GetSet bool_getset ( &KeyFile::get_bool,   &KeyFile::set_bool   );
static Int_GetSet  int_getset  ( &KeyFile::get_int,    &KeyFile::set_int    );
static Dbl_GetSet  dbl_getset  ( &KeyFile::get_double, &KeyFile::set_double );
static Str_GetSet  str_getset  ( &KeyFile::get_string, &KeyFile::set_string );

static
BoolList_GetSet boollist_getset ( &KeyFile::get_bool_list,   &KeyFile::set_bool_list   );
static
IntList_GetSet  intlist_getset  ( &KeyFile::get_int_list,    &KeyFile::set_int_list    );
static
DblList_GetSet  dbllist_getset  ( &KeyFile::get_double_list, &KeyFile::set_double_list );
static
StrList_GetSet  strlist_getset  ( &KeyFile::get_string_list, &KeyFile::set_string_list );
//=======================================================================================


//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wweak-vtables"
class KeyFile_Schema::_field
{
public:
    str group;
    str key;
    str comment;

    virtual ~_field() = default;

    virtual void capture ( const KeyFile &kf )      const = 0;
    virtual void save_defaults_into ( KeyFile *kf ) const = 0;
    virtual bool is_destination ( void *ptr )       const = 0;
};
#pragma GCC diagnostic pop
//=======================================================================================


//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
template<typename T, typename GetSet>
class Spec_Field : public KeyFile_Schema::_field
{
public:
    void capture( const KeyFile &kf )      const override;
    void save_defaults_into( KeyFile *kf ) const override;
    bool is_destination ( void *ptr )      const override;

    Spec_Field(GetSet gs) : get_set(gs) {}

    GetSet get_set;

    T* dst;
    T  init_val;
};
#pragma GCC diagnostic pop
//=======================================================================================
template<typename T, typename GetSet>
void Spec_Field<T,GetSet>::capture( const KeyFile &kf ) const
{
    // Если захотим проверять на поле ошибку, то nullptr надо заменить на Error.
    *dst = static_cast<T>( (kf.*get_set.getter)(group, key, nullptr) );
}
//=======================================================================================
template<typename T, typename GetSet>
void Spec_Field<T,GetSet>::save_defaults_into( KeyFile *kf ) const
{
    (kf->*get_set.setter)(group, key, init_val);

    if ( !comment.empty() )
        kf->set_comment( group, key, comment );
}
//=======================================================================================
template<typename T, typename GetSet>
bool Spec_Field<T,GetSet>::is_destination( void *ptr ) const
{
    return dst == ptr;
}
//=======================================================================================

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
template<typename T, typename GetSet, typename Valid_T>
class Spec_Field_Validate : public Spec_Field<T,GetSet>
{
    using Base = Spec_Field<T,GetSet>;
public:
    Spec_Field_Validate( GetSet gs ) : Base( gs ) {}

    void capture( const KeyFile &kf ) const override;

    KeyFile_Schema::validator<Valid_T> validator;
};
#pragma GCC diagnostic pop
//=======================================================================================
template<typename T, typename GetSet, typename Valid_T>
void Spec_Field_Validate<T,GetSet,Valid_T>::capture( const KeyFile &kf ) const
{
    Base::capture( kf );

    if ( !validator.is_ok(*Base::dst) )
    {
        auto msg = vcat( "Setting of ", group_key_str(Base::group, Base::key),
                         " has to be in diapazone "
                         "[", validator.lo, ",", validator.hi, "]." ).str();

        throw KeyFile_Schema::ValidateException( msg );
    }
}
//=======================================================================================

//=======================================================================================
template<typename T, typename GetSet>
static void fill_spec( Spec_Field<T,GetSet> *spec, cstr group, cstr key,
                       T* dst, T init_val, cstr comment )
{
    if ( group.empty() )
        throw verror( "Before set key '" + key + "', set the group, first." );

    if ( key.empty() )
        throw verror( "Key is empty." );

    if ( !dst )
        throw verror( "Set destination, please." );

    spec->group    = group;
    spec->key      = key;

    spec->dst      = dst;
    spec->init_val = init_val;

    spec->comment = comment;
}
//=======================================================================================
template<typename T, typename GetSet>
static KeyFile_Schema::_field_ptr make_spec( GetSet gs, cstr group, cstr key,
                                             T* dst, T init_val, cstr comment )
{
    using spec_type = Spec_Field<T, GetSet>;
    auto res = std::make_shared<spec_type>( gs );

    fill_spec( res.get(), group, key, dst, init_val, comment );

    return res;
}
//=======================================================================================
template<typename T, typename GetSet, typename Valid_T>
static KeyFile_Schema::_field_ptr make_spec_v( GetSet gs, cstr group, cstr key,
                                               T* dst, T init_val, cstr comment,
                                              KeyFile_Schema::validator<Valid_T> validat)
{
    // Проверка на соблюдение диапазона начальным значением.
    if ( !validat.is_ok(init_val) )
        throw verror( group_key_str(group,key), ": Начальное значение вне диапазона: ",
                      double(init_val), " =/= [", validat.lo, ":", validat.hi, "].");

    using spec_validate_type = Spec_Field_Validate<T, GetSet, Valid_T>;
    auto res = std::make_shared<spec_validate_type>( gs );

    fill_spec( res.get(), group, key, dst, init_val, comment );

    res->validator = validat;

    return res;
}
//=======================================================================================

//=======================================================================================
KeyFile_Schema::ValidateException::ValidateException( cstr msg )
    : std::runtime_error( msg )
{}
//=======================================================================================

//=======================================================================================
void KeyFile_Schema::set_current_group( const std::string &group )
{
    assert( !group.empty() );
    _cur_group = group;
}
//=======================================================================================
template<typename Alt_T, typename Base_T>
static void tune_alternate_validator( KeyFile_Schema::validator<Base_T> *valid,
                                      cstr info )
{
    auto alt_min = std::numeric_limits<Alt_T>::lowest();
    auto alt_max = std::numeric_limits<Alt_T>::max();

    if ( !valid->activated )
    {
        valid->lo = Base_T(alt_min);
        valid->hi = Base_T(alt_max);
        valid->activated = true;
        return;
    }

    if ( valid->lo < Base_T(alt_min) )
        throw verror( "У валидатора для ", info, " слишком малая нижняя граница. (",
                      valid->lo, " < ", alt_min, ").");

    if ( valid->hi > Base_T(alt_max) )
        throw verror( "У валидатора для ", info, " слишком большая верхняя граница. (",
                      valid->hi, " > ", alt_max, ").");
}
//=======================================================================================
template<typename Alt_T, typename Base_T>
static void check_alternate_value( Base_T val, cstr info )
{
    Base_T alt_min = static_cast<Base_T>( std::numeric_limits<Alt_T>::lowest() );
    Base_T alt_max = static_cast<Base_T>( std::numeric_limits<Alt_T>::max()    );

    if ( alt_min <= val && val <= alt_max ) return;

    throw verror << "Начальное значение для " << info
                 << " вне возможностей диапазона этого типа: "
                 << val << "=/= [" << alt_min << ":" << alt_max << "].";
}
//=======================================================================================
template<typename Dst_T, typename Base_T, typename GetSet>
void KeyFile_Schema::_append_any( GetSet gs, cstr key, Dst_T* dst, Base_T init_val,
                                  cstr comment )
{
    _check_unique( key, dst );

    auto in_val = static_cast<Dst_T>( init_val );
    auto res = make_spec( gs, _cur_group, key, dst, in_val, comment );
    _fields.push_back( res );
}
//=======================================================================================
template<typename Dst_T, typename Base_T, typename GetSet>
void KeyFile_Schema::_append_any_v( GetSet gs, cstr key, Dst_T* dst, Base_T init_val,
                                    cstr comment, validator<Base_T> validat )
{
    auto info = group_key_str( _cur_group, key );
    tune_alternate_validator<Dst_T>( &validat, info );
    check_alternate_value<Dst_T>( init_val, info );

    _check_unique( key, dst );

    auto in_val = static_cast<Dst_T>( init_val );
    auto res = make_spec_v( gs, _cur_group, key, dst, in_val, comment, validat );
    _fields.push_back( res );
}
//===================================================================================
void KeyFile_Schema::append( cstr key, int8_t *dst, int init_val, cstr comment,
                             validator<int> validat )
{
    _append_any_v( int_getset, key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, uint8_t *dst, int init_val, cstr comment,
                             validator<int> validat )
{
    _append_any_v( int_getset, key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, int16_t *dst, int init_val, cstr comment,
                             validator<int> validat )
{
    _append_any_v( int_getset, key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, uint16_t *dst, int init_val, cstr comment,
                             validator<int> validat )
{
    _append_any_v( int_getset, key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, float *dst, double init_val, cstr comment,
                             validator<double> validat )
{
    _append_any_v( dbl_getset, key, dst, init_val, comment, validat );
}
//=======================================================================================
//=======================================================================================
//  Проверяет, что такого ключа с текущей группой еще не добавляли.
//  Также проверяет, что приемник уникальный.
void KeyFile_Schema::_check_unique( cstr key, void *dst_ptr ) const
{
    for ( const auto &f: _fields )
    {
        if ( f->group == _cur_group && f->key == key )
        {
            throw verror << group_key_str(f->group,key) << " already exists.";
        }
        if ( f->is_destination(dst_ptr) )
        {
            throw verror << group_key_str(_cur_group, key)
                         << " has the same destination as "
                         << group_key_str(f->group, f->key);
        }
    } // for all fields
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, bool *dst, bool init_val, cstr comment )
{
    _append_any( bool_getset, key, dst, init_val, comment );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, int *dst, int init_val, cstr comment,
                             validator<int> validat )
{
    _append_any_v( int_getset, key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, double *dst, double init_val, cstr comment,
                             validator<double> validat )
{
    _append_any_v( dbl_getset, key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, str *dst, cstr defval, cstr comment )
{
    _append_any( str_getset, key, dst, defval, comment );
}
//=======================================================================================
static std::string msg_default_list_empty( const std::string &g, const std::string &k )
{
    return "Default value for " + group_key_str(g,k) + " is empty."
           " Any list must has, at least, one element.";
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, bool_list *dst, cbool_list defval, cstr comment )
{
    if ( defval.empty() ) throw verror << msg_default_list_empty(_cur_group, key);
    _append_any( boollist_getset, key, dst, defval, comment );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, int_list *dst, cint_list defval, cstr comment )
{
    if ( defval.empty() ) throw verror << msg_default_list_empty(_cur_group, key);
    _append_any( intlist_getset, key, dst, defval, comment );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, double_list *dst, cdouble_list defval,
                             cstr comment )
{
    if ( defval.empty() ) throw verror << msg_default_list_empty(_cur_group, key);
    _append_any( dbllist_getset, key, dst, defval, comment );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, string_list *dst, cstr_list defval, cstr comment )
{
    if ( defval.empty() ) throw verror << msg_default_list_empty(_cur_group, key);
    _append_any( strlist_getset, key, dst, defval, comment );
}
//=======================================================================================


//=======================================================================================
void KeyFile_Schema::capture( const KeyFile &kf ) const
{
    for ( auto &val: _fields )
    {
        val->capture( kf );
    }
}
//=======================================================================================
KeyFile KeyFile_Schema::build( KeyFile_Schema::cstr seed ) const
{
    auto res = KeyFile::from_data( seed );
    fill( &res );
    return res;
}
//=======================================================================================
void KeyFile_Schema::fill( KeyFile *kf ) const
{
    for ( const auto & val: _fields )
    {
        val->save_defaults_into( kf );
    }
}
//=======================================================================================
