#ifndef NKEYFILE_SCHEMA_H
#define NKEYFILE_SCHEMA_H

#include "nkeyfile.h"
#include "vcat.h"

//=======================================================================================
/*
 *  2018-05-10
 *  NKeyFile_Schema -- предназначен для захвата и записи полей из/в NKeyFile.
*/
//=======================================================================================



//=======================================================================================
//      NKeyFile_Schema
//=======================================================================================
class NKeyFile_Schema
{
public:
    //-----------------------------------------------------------------------------------
    //  Общие определения для сокращения записи аргументов.
    using string            = std::string;
    using string_cref       = const std::string&;

    using bool_list         = std::vector<bool>;
    using int_list          = std::vector<int>;
    using int64_list        = std::vector<int64_t>;
    using uint64_list       = std::vector<uint64_t>;
    using double_list       = std::vector<double>;
    using string_list       = std::vector<std::string>;

    using bool_list_cref    = const bool_list &;
    using int_list_cref     = const int_list &;
    using double_list_cref  = const double_list &;
    using string_list_cref  = const string_list &;

    // Валидатор, стандартное использование при вызове:
    //      append( ..., comment, {from, to} );
    template<class T> struct validator
    {
        validator  () {}
        validator  ( T lo, T hi );
        bool is_ok ( T val ) const;

        T _lo;
        T _hi;
        bool _activated = false;
    };
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //  User interface begins here
    //-----------------------------------------------------------------------------------

    class ValidateException : public std::runtime_error
    { public: ValidateException( string_cref msg ); };

    void set_current_group( const std::string &group );

    //-----------------------------------------------------------------------------------

    void append( string_cref key, bool* dst, bool defval,
                 string_cref comment = string() );

    void append( string_cref key, int* dst, int defval = 0,
                 string_cref comment = string(),
                 validator<int> validat = validator<int>() );

    void append( string_cref key, int64_t* dst, int64_t defval = 0,
                 string_cref comment = string(),
                 validator<int64_t> validat = validator<int64_t>() );

    void append( string_cref key, uint64_t* dst, uint64_t defval = 0,
                 string_cref comment = string(),
                 validator<uint64_t> validat = validator<uint64_t>() );

    void append( string_cref key, double* dst, double defval = 0,
                 string_cref comment = string(),
                 validator<double> validat = validator<double>() );

    void append( string_cref key, string* dst, string_cref defval,
                 string_cref comment = string() );

    //-----------------------------------------------------------------------------------

    ///  У всех списков убраны значения по умолчанию, т.к. при пустый списках ничего
    ///  записано не будет, соответственно, установка комментариев и дальнейшее чтение
    ///  дадут ошибку. Если вам нужен список, дайте список по умолчанию.
    void append( string_cref key, bool_list* dst, bool_list_cref defval,
                 string_cref comment = string() );

    void append( string_cref key, int_list* dst, int_list_cref defval,
                 string_cref comment = string() );

    void append( string_cref key, double_list* dst, double_list_cref defval,
                 string_cref comment = string() );

    void append( string_cref key, string_list* dst, string_list_cref defval,
                 string_cref comment = string() );

    //-----------------------------------------------------------------------------------

    /// Устанавливает все заранее перечисленные поля в значения из keyfile.
    /// В случае ошибок, бросит исключение NException.
    void capture( const NKeyFile &kf ) const;

    /// seed -- Затравка для NKeyFile. Обычно, в затравке передаю пару строк комментариев
    /// в начало. Будьте бдительны и не передавайте ничего, если не знаете что делаете.
    /// explicit NKeyFile_Schema( const std::string & seed = std::string() );
    NKeyFile build( string_cref seed = string() ) const;
    void fill( NKeyFile *kf ) const;

    //-----------------------------------------------------------------------------------
    //      IMPLEMENTATION
    //-----------------------------------------------------------------------------------
private:

    struct _value
    {
        const std::string _group;
        const std::string _key;

        _value( string_cref &group, string_cref &key );
        virtual ~_value();

        virtual void capture ( const NKeyFile &kf ) const = 0;
        virtual void save_defaults_into ( NKeyFile *kf ) const = 0;
        virtual bool is_destination ( void *ptr ) const = 0;
    };

    using _value_ptr = std::shared_ptr<_value>;

    //-----------------------------------------------------------------------------------

    template<typename T, typename Getter, typename Setter>
    struct _spec_value : public _value
    {
        _spec_value( Getter getter,         Setter setter,
                     string_cref &group,    string_cref &key,
                     T* dst,                const T& def_val,
                     string_cref comment,   validator<T> validat );

        void capture( const NKeyFile &kf ) const override;
        void save_defaults_into( NKeyFile *kf ) const override;
        bool is_destination ( void *ptr ) const override;

        T* const _dst ;
        T  const _def_val;

        const Getter _getter;
        const Setter _setter;

        const string _comment;
        const validator<T> _validator;
    };
    //-----------------------------------------------------------------------------------

    template<typename T, typename Getter, typename Setter>
    static _value_ptr _make_spec( Getter getter,        Setter setter,
                                  string_cref &group,   string_cref &key,
                                  T* dst,               const T& def_val,
                                  string_cref comment,
                                  validator<T> validat = validator<T>() );

    //-----------------------------------------------------------------------------------

    std::vector<_value_ptr> _values;
    std::string _cur_group;
    void _check_uniqe( string_cref key, void *dst_ptr ) const;

    static string _group_key_str( string_cref group, string_cref key );
};
//=======================================================================================
//      NKeyFile_Schema
//=======================================================================================


//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template<typename T, typename Getter, typename Setter>
NKeyFile_Schema::
_spec_value<T,Getter,Setter>::_spec_value( Getter getter,       Setter setter,
                                           string_cref &group,  string_cref &key,
                                           T *dst,              const T &def_val,
                                           string_cref comment, validator<T> validat )
    : _value( group, key )
    , _dst       ( dst     )
    , _def_val   ( def_val )
    , _getter    ( getter  )
    , _setter    ( setter  )
    , _comment   ( comment )
    , _validator ( validat )
{
    if ( !_dst )
        throw std::logic_error( _group_key_str(group, key) +
                                ": destination must not be null value." );

    if ( !_validator.is_ok(_def_val) )
        throw std::logic_error( _group_key_str(group, key) +
                                ": default value out of valid range!" );
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
void NKeyFile_Schema::_spec_value<T,Getter,Setter>::capture( const NKeyFile &kf ) const
{
    auto res = (kf.*_getter)(_group, _key, nullptr);
    if ( !_validator.is_ok(res) )
    {
        throw ValidateException( vcat("Setting of ", _group_key_str(_group, _key),
                                      " has to be in diapazone "
                                      "[", _validator._lo, ",", _validator._hi, "].") );
    }
    *_dst = res;
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
void NKeyFile_Schema::
_spec_value<T,Getter,Setter>::save_defaults_into( NKeyFile *kf ) const
{
    (kf->*_setter)(_group, _key, _def_val);

    if ( !_comment.empty() )
        kf->set_comment( _group, _key, _comment );
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
bool NKeyFile_Schema::_spec_value<T,Getter,Setter>::is_destination( void *ptr ) const
{
    return _dst == ptr;
}
//=======================================================================================
template<typename T, typename Getter, typename Setter>
NKeyFile_Schema::_value_ptr
NKeyFile_Schema::_make_spec( Getter getter,       Setter setter,
                             string_cref &group,  string_cref &key,
                             T* dst,              const T& def_val,
                             string_cref comment, validator<T> validat )
{
    if ( group.empty() )
        throw std::logic_error( "Before set key '" + key + "', set the group, first." );

    using spec_type = _spec_value<T, Getter, Setter>;
    return  std::make_shared<spec_type>( getter,  setter,
                                         group,   key,
                                         dst,     def_val,
                                         comment, validat );
}
//=======================================================================================
//      Validator
//=======================================================================================
template<class T>
NKeyFile_Schema::validator<T>::validator( T lo, T hi )
    : _lo( lo )
    , _hi( hi )
    , _activated( true )
{}
//=======================================================================================
template<class T>
bool NKeyFile_Schema::validator<T>::is_ok( T val ) const
{
    if ( !_activated ) return true;
    return _lo <= val && val <= _hi;
}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================



#endif // NKEYFILE_SCHEMA_H
