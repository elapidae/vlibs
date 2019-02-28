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


#include "vgio_keyfile.h"

#include <assert.h>
#include <glib.h>
#include "impl/vgio_converting_helper.h"
#include "vlog.h"

#define GNUC_VERSION_ELPD ((__GNUC__ * 100) + __GNUC_MINOR__)

#if GNUC_VERSION_ELPD <= 407
  #warning "using fstream version for writing keyfile."
  #include <fstream>
#endif

using namespace std;
using namespace vgio;
using namespace vgio::_impl;


//=======================================================================================
template<typename T, typename Fn>
static T any_get_and_err( GKeyFile *kf, const string &g, const string &k, Fn fn,
                          Error *err )
{
    error_proxy eproxy( err );
    auto res = fn( kf, g.c_str(), k.c_str(), eproxy );
    eproxy.flush();
    return res;
}
//=======================================================================================


//=======================================================================================
static auto constexpr open_flag
    = static_cast<GKeyFileFlags>(G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS);
//=======================================================================================
KeyFile KeyFile::from_file( cstr fname, Error *err )
{
    KeyFile res;

    error_proxy err_proxy( err );
    auto ok = g_key_file_load_from_file( res.p.get(),
                                         fname.c_str(),
                                         open_flag,
                                         err_proxy );

    err_proxy.flush();

    if (!ok) res.p.reset();
    return res;
}
//=======================================================================================
KeyFile KeyFile::from_data( cstr data, Error *err )
{
    KeyFile res;

    error_proxy err_proxy( err );
    auto ok = g_key_file_load_from_data( res.p.get(),
                                         data.c_str(), data.size(),
                                         open_flag,
                                         err_proxy );
    err_proxy.flush();

    if (!ok) res.p.reset();
    return res;
}
//=======================================================================================
KeyFile::KeyFile()
    : p( g_key_file_new(), g_key_file_unref )
{
    assert( p );
    set_list_separator( _default_list_separator );
}
//=======================================================================================
bool KeyFile::is_valid() const
{
    return bool( p );
}
//=======================================================================================
KeyFile::str KeyFile::to_data( Error *err ) const
{
    assert( p );
    error_proxy err_proxy( err );
    auto *ch = g_key_file_to_data( p.get(), nullptr, err_proxy );
    auto res = convert_and_free( ch );
    err_proxy.flush();
    return res;
}
//=======================================================================================


bool KeyFile::to_file( cstr fname, Error *err )
{
    assert( p );

  #if GNUC_VERSION_ELPD > 407
    error_proxy err_proxy( err );
    auto res = g_key_file_save_to_file( p.get(), fname.c_str(), err_proxy );
    err_proxy.flush();
    return res;
  #else
    ofstream o( fname, ios_base::trunc|ios_base::out );
    o << to_data();
    return o.good();
  #endif
}
//=======================================================================================
void KeyFile::set_list_separator( char sep )
{
    assert( p );
    g_key_file_set_list_separator( p.get(), sep );
}
//=======================================================================================
bool KeyFile::has_group( cstr group ) const
{
    assert( p );
    return g_key_file_has_group( p.get(), group.c_str() );
}
//=======================================================================================
KeyFile::StringList KeyFile::get_groups() const
{
    assert( p );
    char ** glist = g_key_file_get_groups( p.get(), nullptr );
    return convert_and_free_list( glist );
}
//=======================================================================================
string KeyFile::get_start_group() const
{
    assert( p );
    auto *g = g_key_file_get_start_group( p.get() );
    return convert_and_free( g );
}
//=======================================================================================
bool KeyFile::has_key( cstr group, cstr key, Error *err ) const
{
    assert( p );
    error_proxy err_proxy( err );
    auto res = g_key_file_has_key( p.get(), group.c_str(), key.c_str(), err_proxy );
    err_proxy.flush();
    return res;
}
//=======================================================================================
KeyFile::StringList KeyFile::get_keys( cstr group, Error *err ) const
{
    assert( p );
    error_proxy err_proxy( err );
    auto ** gkeys = g_key_file_get_keys( p.get(), group.c_str(), nullptr, err_proxy );
    auto res = convert_and_free_list( gkeys );
    err_proxy.flush();
    return res;
}
//=======================================================================================


//=======================================================================================
string KeyFile::get_string( cstr group, cstr key, Error *err ) const
{
    assert( p );
    error_proxy err_proxy( err );
    auto * val = g_key_file_get_string( p.get(), group.c_str(), key.c_str(), err_proxy );
    auto res = convert_and_free( val );
    err_proxy.flush();
    return res;
}
//=======================================================================================
bool KeyFile::get_bool( cstr group, cstr key, Error *err ) const
{
    assert( p );
    return any_get_and_err<bool>( p.get(), group, key, &g_key_file_get_boolean, err );
}
//=======================================================================================
int KeyFile::get_int( cstr group, cstr key, Error *err ) const
{
    assert( p );
    using gtype = decltype( g_key_file_get_integer(nullptr,nullptr,nullptr,nullptr) );
    static_assert( is_same<int,gtype>::value, "" );

    return any_get_and_err<int>( p.get(), group, key, &g_key_file_get_integer, err );
}
//=======================================================================================
double KeyFile::get_double( cstr group, cstr key, Error *err ) const
{
    assert( p );
    using gtype = decltype(g_key_file_get_double(nullptr,nullptr,nullptr,nullptr) );
    static_assert( is_same<double,gtype>::value, "" );

    return any_get_and_err<double>( p.get(), group, key, &g_key_file_get_double, err );
}
//=======================================================================================
KeyFile::StringList KeyFile::get_string_list( cstr group, cstr key, Error *err ) const
{
    assert( p );
    error_proxy err_proxy( err );
    auto ** ch = g_key_file_get_string_list( p.get(), group.c_str(), key.c_str(),
                                             nullptr, err_proxy );
    auto res = convert_and_free_list( ch );
    err_proxy.flush();
    return res;
}
//=======================================================================================
KeyFile::BoolList KeyFile::get_bool_list( cstr group, cstr key, Error *err ) const
{
    assert( p );
    return _get_any_simple_list<bool, gsize>( group, key,
                                              g_key_file_get_boolean_list, err );
}
//=======================================================================================
KeyFile::IntList KeyFile::get_int_list( cstr group, cstr key, Error *err ) const
{
    assert( p );
    return _get_any_simple_list<int, gsize>( group, key,
                                             g_key_file_get_integer_list, err );
}
//=======================================================================================
KeyFile::DoubleList KeyFile::get_double_list( cstr group, cstr key, Error *err ) const
{
    assert( p );
    return _get_any_simple_list<double, gsize>( group, key,
                                                g_key_file_get_double_list, err );
}
//=======================================================================================
KeyFile::str KeyFile::get_comment( cstr group, cstr key, Error *err ) const
{
    assert( p );
    error_proxy err_proxy( err );
    auto *ch = g_key_file_get_comment( p.get(), group.c_str(), key.c_str(), err_proxy );
    auto res = convert_and_free( ch );
    err_proxy.flush();
    return res;
}
//=======================================================================================


//=======================================================================================
KeyFile::str KeyFile::safe_string( cstr group, cstr key, cstr defval ) const
{
    assert( p );
    Error err;
    auto res = get_string( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
bool KeyFile::safe_bool( cstr group, cstr key, bool defval ) const
{
    assert( p );
    Error err;
    auto res = get_bool( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
int KeyFile::safe_int( cstr group, cstr key, int defval ) const
{
    assert( p );
    Error err;
    auto res = get_int( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
double KeyFile::safe_double( cstr group, cstr key, double defval ) const
{
    assert( p );
    Error err;
    auto res = get_double( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
KeyFile::StringList KeyFile::safe_string_list( cstr group, cstr key,
                                                 const StringList &defval ) const
{
    assert( p );
    Error err;
    auto res = get_string_list( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
KeyFile::BoolList KeyFile::safe_bool_list( cstr group, cstr key,
                                             const BoolList &defval ) const
{
    assert( p );
    Error err;
    auto res = get_bool_list( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
KeyFile::IntList KeyFile::safe_int_list( cstr group, cstr key,
                                           const IntList &defval ) const
{
    assert( p );
    Error err;
    auto res = get_int_list( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
KeyFile::DoubleList KeyFile::safe_double_list( cstr &group, cstr key,
                                                 const DoubleList &defval ) const
{
    assert( p );
    Error err;
    auto res = get_double_list( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
KeyFile::str KeyFile::safe_comment( cstr group, cstr key, cstr defval ) const
{
    assert( p );
    Error err;
    auto res = get_comment( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================


//=======================================================================================
void KeyFile::set_string( cstr group, cstr key, cstr val )
{
    assert( p );
    g_key_file_set_string( p.get(), group.c_str(), key.c_str(), val.c_str() );
}
//=======================================================================================
void KeyFile::set_bool( cstr group, cstr key, bool val )
{
    assert( p );
    g_key_file_set_boolean( p.get(), group.c_str(), key.c_str(), val );
}
//=======================================================================================
void KeyFile::set_int( cstr group, cstr key, int val )
{
    assert( p );
    g_key_file_set_integer( p.get(), group.c_str(), key.c_str(), val );
}
//=======================================================================================
void KeyFile::set_double( cstr group, cstr key, double val )
{
    assert( p );
    g_key_file_set_double( p.get(), group.c_str(), key.c_str(), val );
}
//=======================================================================================
void KeyFile::set_string_list( cstr group, cstr key, const StringList &val )
{
    assert( p );
    vector<const char*> ptrs;
    for ( auto & s: val )
        ptrs.push_back( s.c_str() );

    g_key_file_set_string_list( p.get(), group.c_str(), key.c_str(),
                                ptrs.data(), ptrs.size() );
}
//=======================================================================================
void KeyFile::set_bool_list( cstr group, cstr key, const BoolList &val )
{
    static_assert ( !is_same<gboolean,bool>::value, "Обязательная проверка, что в итоге "
            "не получим vector<bool>. По Стандарту, vector<bool> не соответствует "
            "следующим друг за другом bool-ам! Они там могут быть упакованы!" );

    assert( p );
    vector<gboolean> res( val.begin(), val.end() );
    g_key_file_set_boolean_list( p.get(), group.c_str(), key.c_str(),
                                 res.data(), val.size() );
}
//=======================================================================================
void KeyFile::set_int_list( cstr group, cstr key,
                             const KeyFile::IntList &val )
{
    assert( p );
    g_key_file_set_integer_list( p.get(), group.c_str(), key.c_str(),
                                 const_cast<int*>(val.data()), val.size() );
}
//=======================================================================================
void KeyFile::set_double_list( cstr group, cstr key, const DoubleList &val )
{
    assert( p );
    g_key_file_set_double_list( p.get(), group.c_str(), key.c_str(),
                                const_cast<double*>(val.data()), val.size() );
}
//=======================================================================================
bool KeyFile::set_comment( cstr group, cstr key, cstr val, Error *err )
{
    assert( p );
    error_proxy err_proxy( err );
    auto res = g_key_file_set_comment( p.get(), group.c_str(), key.c_str(), val.c_str(),
                                       err_proxy );
    err_proxy.flush();
    return res;
}
//=======================================================================================


//=======================================================================================
bool KeyFile::remove_group( cstr group, Error *err )
{
    assert( p );
    error_proxy eproxy( err );
    auto res = g_key_file_remove_group( p.get(), group.c_str(), eproxy );
    eproxy.flush();
    return res;
}
//=======================================================================================
bool KeyFile::remove_key( cstr group, cstr key, Error *err )
{
    assert( p );
    error_proxy eproxy( err );
    auto res = g_key_file_remove_key( p.get(), group.c_str(), key.c_str(), eproxy );
    eproxy.flush();
    return res;
}
//=======================================================================================
bool KeyFile::remove_comment( cstr group, cstr key, Error *err )
{
    assert( p );
    error_proxy eproxy( err );
    auto res = g_key_file_remove_comment( p.get(), group.c_str(), key.c_str(), eproxy );
    eproxy.flush();
    return res;
}
//=======================================================================================
void KeyFile::_g_free( void *ptr )
{
    assert( ptr );
    g_free( ptr );
}
//=======================================================================================
