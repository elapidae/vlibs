#include "vgio_keyfile_schema.h"

#include "verror.h"
//#include "vlog_pretty.h"

#include <assert.h>

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
//=======================================================================================


//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
template<typename T, typename Getter, typename Setter>
class Spec_Field : public KeyFile_Schema::_field
{
public:
    void capture( const KeyFile &kf )      const override;
    void save_defaults_into( KeyFile *kf ) const override;
    bool is_destination ( void *ptr )      const override;

    Getter getter;
    Setter setter;

    T* dst;
    T  init_val;
};
#pragma GCC diagnostic pop
//=======================================================================================
template<typename T, typename Getter, typename Setter>
void Spec_Field<T,Getter,Setter>::capture( const KeyFile &kf ) const
{
    // Если захотим проверять на поле ошибку, то nullptr надо заменить на Error.
    *dst = (kf.*getter)(group, key, nullptr);
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
void Spec_Field<T,Getter,Setter>::save_defaults_into( KeyFile *kf ) const
{
    (kf->*setter)(group, key, init_val);

    if ( !comment.empty() )
        kf->set_comment( group, key, comment );
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
bool Spec_Field<T,Getter,Setter>::is_destination( void *ptr ) const
{
    return dst == ptr;
}
//=======================================================================================

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
template<typename T, typename Getter, typename Setter, typename Valid_T>
class Spec_Field_Validate : public Spec_Field<T,Getter,Setter>
{
    using Base = Spec_Field<T,Getter,Setter>;
public:
    void capture( const KeyFile &kf ) const override;

    KeyFile_Schema::validator<Valid_T> validator;
};
#pragma GCC diagnostic pop
//=======================================================================================
template<typename T, typename Getter, typename Setter, typename Valid_T>
void Spec_Field_Validate<T,Getter,Setter,Valid_T>::capture( const KeyFile &kf ) const
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
static void fill_spec( Spec_Field<T,Getter,Setter> *spec,
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
    spec->init_val = def_val;

    spec->comment = comment;
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
static KeyFile_Schema::_field_ptr make_spec (
                Getter   getter,     Setter   setter,
                cstr     group,      cstr     key,
                T*       dst,        const T& def_val,
                cstr     comment )
{
    using spec_type = Spec_Field<T, Getter, Setter>;
    auto res = std::make_shared<spec_type>();

    fill_spec( res.get(), getter, setter, group, key, dst, def_val, comment );

    return res;
}
//=======================================================================================

//=======================================================================================
template<typename T, typename Getter, typename Setter, typename Valid_T>
static KeyFile_Schema::_field_ptr make_spec_validate (
                Getter   getter,     Setter setter,
                cstr     group,      cstr   key,
                T*       dst,        T      init_val,
                cstr     comment,
                KeyFile_Schema::validator<Valid_T> validator )
{
    // Проверка на соблюдение диапазона начальным значением.
    if ( !validator.is_ok(init_val) )
        throw verror( group_key_str(group,key), ": Начальное значение вне диапазона: ",
                      double(init_val), " =/= [", validator.lo, ":", validator.hi, "].");

    using spec_validate_type = Spec_Field_Validate<T, Getter, Setter, Valid_T>;
    auto res = std::make_shared<spec_validate_type>();

    fill_spec( res.get(), getter, setter, group, key, dst, init_val, comment );

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
    auto alt_min = std::numeric_limits<Alt_T>::lowest();
    auto alt_max = std::numeric_limits<Alt_T>::max();


    if ( alt_min <= val && val <= alt_max ) return;

    throw verror << "Начальное значение для " << info
                 << " вне возможностей диапазона этого типа: "
                 << val << "=/= [" << double(alt_min) << ":" << double(alt_max) << "].";
}
//=======================================================================================
template<typename T>
void KeyFile_Schema::_append_any_int( cstr key, T* dst, int init_val,
                                      cstr comment, validator<int> validat )
{
    auto info = group_key_str( _cur_group, key );
    tune_alternate_validator<T>( &validat, info );
    check_alternate_value<T>( init_val, info );

    auto getter = &KeyFile::get_int;
    auto setter = &KeyFile::set_int;

    auto in_val = static_cast<T>(init_val);
    auto res = make_spec_validate( getter, setter, _cur_group, key, dst,
                                   in_val, comment, validat );
    _values.push_back( res );
}
//===================================================================================
void KeyFile_Schema::append_i8( cstr key, int8_t *dst, int init_val,
                                cstr comment, validator<int> validat )
{
    _append_any_int( key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append_u8( cstr key, uint8_t *dst, int init_val,
                                cstr comment, validator<int> validat )
{
    _append_any_int( key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append_i16(cstr key, int16_t *dst, int init_val,
                                 cstr comment, validator<int> validat )
{
    _append_any_int( key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append_u16(cstr key, uint16_t *dst, int init_val,
                                 cstr comment, validator<int> validat )
{
    _append_any_int( key, dst, init_val, comment, validat );
}
//=======================================================================================
void KeyFile_Schema::append_float( cstr key, float *dst, float init_val,
                                   cstr comment, validator<double> validat )
{
    using T = std::remove_reference<decltype(*dst)>::type;

    auto info = group_key_str( _cur_group, key );
    tune_alternate_validator<T>( &validat, info );
    check_alternate_value<T>( init_val, info );

    auto getter = &KeyFile::get_double;
    auto setter = &KeyFile::set_double;

    auto in_val = static_cast<T>(init_val);
    auto res = make_spec_validate( getter, setter, _cur_group, key, dst,
                                   in_val, comment, validat );
    _values.push_back( res );
}
//=======================================================================================
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
                             cstr comment, validator<double> validat )
{
    _check_unique( key, dst );

    auto getter = &KeyFile::get_double;
    auto setter = &KeyFile::set_double;

    auto res = make_spec_validate( getter, setter, _cur_group, key, dst, defval, comment,
                                   validat );
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
