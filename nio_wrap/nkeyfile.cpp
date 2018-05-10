#include "nkeyfile.h"

#include <assert.h>
#include "impl/nconvertinghelper.h"


using namespace std;


//=======================================================================================
NKeyFile NKeyFile::from_file( const str &fname, NKeyFile::OpenFlag flag , NError *err )
{
    NKeyFile res;
    res.p.reset( g_key_file_new(), g_key_file_unref );

    auto gflags = flag == OpenFlag::ReadOnly
                            ? G_KEY_FILE_NONE
                            : G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;

    _n_error_proxy err_proxy( err );
    auto ok = g_key_file_load_from_file( res.p.get(),
                                         fname.c_str(),
                                         GKeyFileFlags(gflags),
                                         err_proxy );
    if (!ok) res.p.reset();
    return res;
}
//=======================================================================================
NKeyFile NKeyFile::from_data( const str &data, NKeyFile::OpenFlag flag, NError *err )
{
    NKeyFile res;
    res.p.reset( g_key_file_new(), g_key_file_unref );

    auto gflags = flag == OpenFlag::ReadOnly
                            ? G_KEY_FILE_NONE
                            : G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;

    _n_error_proxy err_proxy( err );
    auto ok = g_key_file_load_from_data( res.p.get(),
                                         data.c_str(), data.size(),
                                         GKeyFileFlags(gflags),
                                         err_proxy );
    if (!ok) res.p.reset();
    return res;
}
//=======================================================================================
NKeyFile::NKeyFile()
    : p( g_key_file_new(), g_key_file_unref )
{}
//=======================================================================================
NKeyFile::str NKeyFile::to_string( NError *err ) const
{
    _n_error_proxy err_proxy( err );
    auto *ch = g_key_file_to_data( p.get(), nullptr, err_proxy );
    return n_convert_and_free( ch );
}
//=======================================================================================
bool NKeyFile::to_file( const str &fname, NError *err )
{
    _n_error_proxy err_proxy( err );
    return g_key_file_save_to_file( p.get(), fname.c_str(), err_proxy );
}
//=======================================================================================
void NKeyFile::set_list_separator(char sep)
{
    if (p) g_key_file_set_list_separator( p.get(), sep );
}
//=======================================================================================
bool NKeyFile::is_valid() const
{
    return bool(p);
}
//=======================================================================================
bool NKeyFile::has_group( const str &group ) const
{
    return p ? g_key_file_has_group( p.get(), group.c_str() ) : false;
}
//=======================================================================================
NKeyFile::StringList NKeyFile::get_groups() const
{
    assert( is_valid() );
    char ** glist = g_key_file_get_groups( p.get(), nullptr );
    return n_convert_and_free( glist );
}
//=======================================================================================
string NKeyFile::get_start_group() const
{
    assert( is_valid() );
    auto *g = g_key_file_get_start_group( p.get() );
    return n_convert_and_free( g );
}
//=======================================================================================
bool NKeyFile::has_key( const str &group, const str &key, NError *err ) const
{
    _n_error_proxy err_proxy( err );
    auto res = g_key_file_has_key( p.get(), group.c_str(), key.c_str(), err_proxy );
    return res;
}
//=======================================================================================
NKeyFile::StringList NKeyFile::get_keys( const str &group, NError *err ) const
{
    _n_error_proxy err_proxy( err );
    auto ** gkeys = g_key_file_get_keys( p.get(), group.c_str(), nullptr, err_proxy );
    return n_convert_and_free( gkeys );
}
//=======================================================================================
string NKeyFile::get_value( const str &group, const str &key, NError *err ) const
{
    _n_error_proxy err_proxy( err );
    auto * val = g_key_file_get_value( p.get(), group.c_str(), key.c_str(), err_proxy );
    return n_convert_and_free( val );
}
//=======================================================================================
string NKeyFile::get_string( const str &group, const str &key, NError *err ) const
{
    _n_error_proxy err_proxy( err );
    auto * val = g_key_file_get_string( p.get(), group.c_str(), key.c_str(), err_proxy );
    return n_convert_and_free( val );
}
//=======================================================================================
bool NKeyFile::get_bool( const str &group, const str &key, NError *err ) const
{
    _n_error_proxy err_proxy( err );
    return g_key_file_get_boolean( p.get(), group.c_str(), key.c_str(), err_proxy );
}
//=======================================================================================
int NKeyFile::get_int( const str &group, const str &key, NError *err ) const
{
    static_assert( is_same<int,decltype(g_key_file_get_integer(0,0,0,0))>::value, "" );
    _n_error_proxy err_proxy( err );
    return g_key_file_get_integer( p.get(), group.c_str(), key.c_str(), err_proxy );
}
//=======================================================================================
int64_t NKeyFile::get_int64( const str &group, const str &key, NError *err ) const
{
    static_assert( is_same<int64_t,decltype(g_key_file_get_int64(0,0,0,0))>::value, "" );
    _n_error_proxy err_proxy( err );
    return g_key_file_get_int64( p.get(), group.c_str(), key.c_str(), err_proxy );
}
//=======================================================================================
uint64_t NKeyFile::get_uint64( const str &group, const str &key, NError *err ) const
{
    using gtype = decltype(g_key_file_get_uint64(0,0,0,0));
    static_assert( is_same<uint64_t,gtype>::value, "" );
    _n_error_proxy err_proxy( err );
    return g_key_file_get_uint64( p.get(), group.c_str(), key.c_str(), err_proxy );
}
//=======================================================================================
double NKeyFile::get_double( const str &group, const str &key, NError *err ) const
{
    using gtype = decltype(g_key_file_get_double(0,0,0,0));
    static_assert( is_same<double,gtype>::value, "" );
    _n_error_proxy err_proxy( err );
    return g_key_file_get_double( p.get(), group.c_str(), key.c_str(), err_proxy );
}
//=======================================================================================
NKeyFile::StringList NKeyFile::get_string_list( const str &group, const str &key,
                                                NError *err ) const
{
    _n_error_proxy err_proxy( err );
    auto ** ch = g_key_file_get_string_list( p.get(), group.c_str(), key.c_str(),
                                             nullptr, err_proxy );
    return n_convert_and_free( ch );
}
//=======================================================================================
NKeyFile::BoolList NKeyFile::get_bool_list( const str &group, const str &key,
                                            NError *err ) const
{
    return _get_any_simple_list<bool>( group, key, g_key_file_get_boolean_list, err );
}
//=======================================================================================
NKeyFile::IntList NKeyFile::get_int_list( const str &group, const str &key,
                                          NError *err ) const
{
    return _get_any_simple_list<int>( group, key, g_key_file_get_integer_list, err );
}
//=======================================================================================
NKeyFile::DoubleList NKeyFile::get_double_list( const str &group, const str &key,
                                                NError *err ) const
{
    return _get_any_simple_list<double>( group, key, g_key_file_get_double_list, err );
}
//=======================================================================================
NKeyFile::str NKeyFile::get_comment( const str &group, const str &key,
                                     NError *err ) const
{
    _n_error_proxy err_proxy( err );
    auto *ch = g_key_file_get_comment( p.get(), group.c_str(), key.c_str(), err_proxy );
    return n_convert_and_free( ch );
}
//=======================================================================================

//=======================================================================================
NKeyFile::str NKeyFile::safe_value(const str &group, const str &key, const str &defval) const
{
    NError err;
    auto res = get_value( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
NKeyFile::str NKeyFile::safe_string(const str &group, const str &key, const str &defval) const
{
    NError err;
    auto res = get_string( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
bool NKeyFile::safe_bool(const str &group, const str &key, bool defval) const
{
    NError err;
    auto res = get_bool( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
int NKeyFile::safe_int(const str &group, const str &key, int defval) const
{
    NError err;
    auto res = get_int( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
int64_t NKeyFile::safe_int64(const str &group, const str &key, int64_t defval) const
{
    NError err;
    auto res = get_int64( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
uint64_t NKeyFile::safe_uint64(const str &group, const str &key, uint64_t defval) const
{
    NError err;
    auto res = get_uint64( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================
double NKeyFile::safe_double(const str &group, const str &key, double defval) const
{
    NError err;
    auto res = get_double( group, key, &err );
    return err.has() ? defval : res;
}
//=======================================================================================

//=======================================================================================
void NKeyFile::set_value( const str &group, const str &key, const str &val )
{
    g_key_file_set_value( p.get(), group.c_str(), key.c_str(), val.c_str() );
}
//=======================================================================================
void NKeyFile::set_string( const str &group, const str &key, const str &val )
{
    g_key_file_set_string( p.get(), group.c_str(), key.c_str(), val.c_str() );
}
//=======================================================================================
void NKeyFile::set_bool( const str &group, const str &key, bool val )
{
    g_key_file_set_boolean( p.get(), group.c_str(), key.c_str(), val );
}
//=======================================================================================
void NKeyFile::set_int( const str &group, const str &key, int val )
{
    g_key_file_set_integer( p.get(), group.c_str(), key.c_str(), val );
}
//=======================================================================================
void NKeyFile::set_int64( const str &group, const str &key, int64_t val )
{
    g_key_file_set_int64( p.get(), group.c_str(), key.c_str(), val );
}
//=======================================================================================
void NKeyFile::set_uint64( const str &group, const str &key, uint64_t val )
{
    g_key_file_set_uint64( p.get(), group.c_str(), key.c_str(), val );
}
//=======================================================================================
void NKeyFile::set_double( const str &group, const str &key, double val )
{
    g_key_file_set_double( p.get(), group.c_str(), key.c_str(), val );
}
//=======================================================================================
void NKeyFile::set_string_list( const str &group, const str &key, const StringList &val )
{
    vector<const char*> ptrs;
    for ( auto & s: val )
        ptrs.push_back( s.c_str() );

    g_key_file_set_string_list( p.get(), group.c_str(), key.c_str(),
                                ptrs.data(), ptrs.size() );
}
//=======================================================================================
void NKeyFile::set_bool_list( const str &group, const str &key, const BoolList &val )
{
    vector<gboolean> res( val.begin(), val.end() );
    g_key_file_set_boolean_list( p.get(), group.c_str(), key.c_str(),
                                 res.data(), val.size() );
}
//=======================================================================================
void NKeyFile::set_int_list( const str &group, const str &key,
                             const NKeyFile::IntList &val )
{
    g_key_file_set_integer_list( p.get(), group.c_str(), key.c_str(),
                                 const_cast<int*>(val.data()), val.size() );
}
//=======================================================================================
void NKeyFile::set_double_list( const str &group, const str &key, const DoubleList &val )
{
    g_key_file_set_double_list( p.get(), group.c_str(), key.c_str(),
                                const_cast<double*>(val.data()), val.size() );
}
//=======================================================================================
bool NKeyFile::set_comment( const str &group, const str &key, const str &val,
                            NError *err )
{
    _n_error_proxy err_proxy( err );
    return g_key_file_set_comment( p.get(), group.c_str(), key.c_str(), val.c_str(),
                                   err_proxy );
}
//=======================================================================================


//=======================================================================================
bool NKeyFile::remove_group( const str &group, NError *err )
{
    _n_error_proxy eproxy( err );
    return g_key_file_remove_group( p.get(), group.c_str(), eproxy );
}
//=======================================================================================
bool NKeyFile::remove_key( const str &group, const str &key, NError *err )
{
    _n_error_proxy eproxy( err );
    return g_key_file_remove_key( p.get(), group.c_str(), key.c_str(), eproxy );
}
//=======================================================================================
bool NKeyFile::remove_comment( const str &group, const str &key, NError *err )
{
    _n_error_proxy eproxy( err );
    return g_key_file_remove_comment( p.get(), group.c_str(), key.c_str(), eproxy );
}
//=======================================================================================
