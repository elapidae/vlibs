#include "vgio_keyfile_schema.h"

#include "verror.h"

#include <assert.h>


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
class KeyFile_Schema::_value
{
public:
    str group;
    str key;

    virtual ~_value() = default;

    virtual void capture ( const KeyFile &kf )      const = 0;
    virtual void save_defaults_into ( KeyFile *kf ) const = 0;
    virtual bool is_destination ( void *ptr )       const = 0;
};
//=======================================================================================


//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
template<typename T, typename Getter, typename Setter>
class Spec_Value : public KeyFile_Schema::_value
{
public:
    void capture( const KeyFile &kf )      const override;
    void save_defaults_into( KeyFile *kf ) const override;
    bool is_destination ( void *ptr )      const override;

    Getter getter;
    Setter setter;

    T* dst;
    T  def_val;

    str comment;
};
#pragma GCC diagnostic pop
//=======================================================================================
template<typename T, typename Getter, typename Setter>
void Spec_Value<T,Getter,Setter>::capture( const KeyFile &kf ) const
{
    // Если захотим проверять на поле ошибку, то nullptr надо заменить на Error.
    *dst = (kf.*getter)(group, key, nullptr);
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
void Spec_Value<T,Getter,Setter>::save_defaults_into( KeyFile *kf ) const
{
    (kf->*setter)(group, key, def_val);

    if ( !comment.empty() )
        kf->set_comment( group, key, comment );
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
bool Spec_Value<T,Getter,Setter>::is_destination( void *ptr ) const
{
    return dst == ptr;
}
//=======================================================================================

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
template<typename T, typename Getter, typename Setter>
class Spec_Value_Validate : public Spec_Value<T,Getter,Setter>
{
    using Base = Spec_Value<T,Getter,Setter>;
public:
    void capture( const KeyFile &kf ) const override;

    KeyFile_Schema::validator<T> validator;
};
#pragma GCC diagnostic pop
//=======================================================================================
template<typename T, typename Getter, typename Setter>
void Spec_Value_Validate<T,Getter,Setter>::capture( const KeyFile &kf ) const
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
template<typename T, typename Getter, typename Setter>
static void fill_spec( Spec_Value<T,Getter,Setter> *spec,
                       Getter   getter,     Setter   setter,
                       cstr     group,      cstr     key,
                       T*       dst,        const T& def_val,
                       cstr     comment )
{
    if ( group.empty() )
        throw verror( "Before set key '" + key + "', set the group, first." );

    if ( key.empty() )
        throw verror( "Key is empty." );

    if ( !dst )
        throw verror( "Set destination, please." );

    assert( getter );
    assert( setter );

    spec->group   = group;
    spec->key     = key;

    spec->getter  = getter;
    spec->setter  = setter;

    spec->dst     = dst;
    spec->def_val = def_val;

    spec->comment = comment;
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
static KeyFile_Schema::_value_ptr make_spec (
                Getter   getter,     Setter   setter,
                cstr     group,      cstr     key,
                T*       dst,        const T& def_val,
                cstr     comment )
{
    using spec_type = Spec_Value<T, Getter, Setter>;
    auto res = std::make_shared<spec_type>();

    fill_spec( res.get(), getter, setter, group, key, dst, def_val, comment );

    return res;
}
//=======================================================================================

//=======================================================================================
template<typename T, typename Getter, typename Setter>
static KeyFile_Schema::_value_ptr make_spec_validate (
                Getter   getter,     Setter   setter,
                cstr     group,      cstr     key,
                T*       dst,        const T& def_val,
                cstr     comment,
                KeyFile_Schema::validator<T> validator )
{
    if ( !validator.is_ok(def_val) )
        throw verror( group_key_str(group,key), ": default value out of valid range!" );

    using spec_validate_type = Spec_Value_Validate<T, Getter, Setter>;
    auto res = std::make_shared<spec_validate_type>();

    fill_spec( res.get(), getter, setter, group, key, dst, def_val, comment );

    res->validator = validator;

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
//  Проверяет, что такого ключа с текущей группой еще не добавляли.
void KeyFile_Schema::_check_unique( cstr key, void *dst_ptr ) const
{
    for ( auto &v: _values )
    {
        if ( v->group == _cur_group && v->key == key )
        {
            throw verror( group_key_str(v->group,key) + " already exists." );
        }
        if ( v->is_destination(dst_ptr) )
        {
            auto msg = group_key_str(_cur_group, key) + " has the same destination "
                       "as " + group_key_str(v->group, v->key);
            throw verror( msg );
        }
    }
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, bool *dst, bool def_val, cstr comment )
{
    _check_unique( key, dst );

    auto getter = &KeyFile::get_bool;
    auto setter = &KeyFile::set_bool;

    auto spec = make_spec( getter, setter, _cur_group, key, dst, def_val, comment );

    _values.push_back( spec );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, int *dst, int defval,
                             cstr comment, validator<int> validator )
{
    _check_unique( key, dst );

    auto getter = &KeyFile::get_int;
    auto setter = &KeyFile::set_int;

    auto res = make_spec_validate( getter, setter, _cur_group, key, dst, defval, comment,
                                   validator );
    _values.push_back( res );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, double *dst, double defval,
                             cstr comment, validator<double> validator )
{
    _check_unique( key, dst );

    auto getter = &KeyFile::get_double;
    auto setter = &KeyFile::set_double;

    auto res = make_spec_validate( getter, setter, _cur_group, key, dst, defval, comment,
                                   validator );
    _values.push_back( res );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, str *dst, cstr defval, cstr comment )
{
    _check_unique( key, dst );

    auto getter = &KeyFile::get_string;
    auto setter = &KeyFile::set_string;

    auto res = make_spec( getter, setter, _cur_group, key, dst, defval, comment );

    _values.push_back( res );
}
//=======================================================================================
static std::string msg_default_list_empty( const std::string &g, const std::string &k )
{
    return "Default value for key '" + k + "' in group '" + g + "' is empty."
           " Any list must has at least than one element.";
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, bool_list *dst, cbool_list defval, cstr comment )
{
    if ( defval.empty() )
        throw std::logic_error( msg_default_list_empty(_cur_group, key) );

    _check_unique( key, dst );

    auto getter = &KeyFile::get_bool_list;
    auto setter = &KeyFile::set_bool_list;

    auto res = make_spec( getter, setter, _cur_group, key, dst, defval, comment );

    _values.push_back( res );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, int_list *dst, cint_list defval, cstr comment )
{
    if ( defval.empty() )
        throw std::logic_error( msg_default_list_empty(_cur_group, key) );

    _check_unique( key, dst );

    auto getter = &KeyFile::get_int_list;
    auto setter = &KeyFile::set_int_list;

    auto res = make_spec( getter, setter, _cur_group, key, dst, defval, comment );

    _values.push_back( res );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, double_list *dst, cdouble_list defval,
                             cstr comment )
{
    if ( defval.empty() )
        throw std::logic_error( msg_default_list_empty(_cur_group, key) );

    _check_unique( key, dst );

    auto getter = &KeyFile::get_double_list;
    auto setter = &KeyFile::set_double_list;

    auto res = make_spec( getter, setter, _cur_group, key, dst, defval, comment );

    _values.push_back( res );
}
//=======================================================================================
void KeyFile_Schema::append( cstr key, string_list *dst, cstr_list defval, cstr comment )
{
    if ( defval.empty() )
        throw std::logic_error( msg_default_list_empty(_cur_group, key) );

    _check_unique( key, dst );

    auto getter = &KeyFile::get_string_list;
    auto setter = &KeyFile::set_string_list;

    auto res = make_spec( getter, setter, _cur_group, key, dst, defval, comment );

    _values.push_back( res );
}
//=======================================================================================


//=======================================================================================
void KeyFile_Schema::capture( const KeyFile &kf ) const
{
    for ( auto &val: _values )
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
    for ( const auto & val: _values )
    {
        val->save_defaults_into( kf );
    }
}
//=======================================================================================
