#include "nkeyfile_schema.h"

//#include "vlog_pretty.h"


//=======================================================================================
NKeyFile_Schema::ValidateException::ValidateException( string_cref msg )
    : std::runtime_error( msg )
{}
//=======================================================================================
NKeyFile_Schema::_value::_value( string_cref &group,
                                 string_cref &key)
    : _group ( group ),
      _key   ( key   )
{}
//=======================================================================================
NKeyFile_Schema::_value::~_value()
{}
//=======================================================================================
void NKeyFile_Schema::set_current_group( const std::string &group )
{
    _cur_group = group;
}
//=======================================================================================
//  Проверяет, что такого ключа с текущей группой еще не добавляли.
void NKeyFile_Schema::_check_unique( string_cref key , void *dst_ptr ) const
{
    for ( auto &v: _values )
    {
        if ( v->_group == _cur_group && v->_key == key )
        {
            throw std::logic_error( _group_key_str(v->_group,key) + " already exists." );
        }
        if ( v->is_destination(dst_ptr) )
        {
            auto msg = _group_key_str(_cur_group, key) + " has the same destination "
                       "as " + _group_key_str(v->_group, v->_key);
            throw std::logic_error( msg );
        }
    }
}
//=======================================================================================
std::string NKeyFile_Schema::_group_key_str( string_cref group, string_cref key )
{
    return "[" + group + "]" + "/" + key;
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, bool *dst, bool defval,
                              string_cref comment )
{
    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_bool, &NKeyFile::set_bool,
                                  _cur_group, key, dst, defval, comment) );
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, int *dst, int defval,
                              string_cref comment, validator<int> validat )
{
    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_int, &NKeyFile::set_int,
                                  _cur_group, key, dst, defval, comment, validat) );
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, int64_t *dst, int64_t defval,
                              string_cref comment, validator<int64_t> validat )
{
    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_int64, &NKeyFile::set_int64,
                                  _cur_group, key, dst, defval, comment, validat) );
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, uint64_t *dst, uint64_t defval,
                              string_cref comment, validator<uint64_t> validat )
{
    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_uint64, &NKeyFile::set_uint64,
                                  _cur_group, key, dst, defval, comment, validat) );
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, double *dst, double defval,
                              string_cref comment, validator<double> validat )
{
    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_double, &NKeyFile::set_double,
                                  _cur_group, key, dst, defval, comment, validat) );
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, string *dst, string_cref defval,
                              string_cref comment )
{
    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_string, &NKeyFile::set_string,
                                  _cur_group, key, dst, defval, comment) );
}
//=======================================================================================
static std::string msg_default_list_empty( const std::string &g, const std::string &k )
{
    return "Default value for key '" + k + "' in group '" + g + "' is empty."
           " Any list must has at least than one element.";
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, bool_list *dst, bool_list_cref defval,
                              string_cref comment )
{
    if ( defval.empty() )
        throw std::logic_error( msg_default_list_empty(_cur_group, key) );

    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_bool_list, &NKeyFile::set_bool_list,
                                  _cur_group, key, dst, defval, comment) );
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, int_list *dst, int_list_cref defval,
                              string_cref comment )
{
    if ( defval.empty() )
        throw std::logic_error( msg_default_list_empty(_cur_group, key) );

    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_int_list, &NKeyFile::set_int_list,
                                  _cur_group, key, dst, defval, comment) );
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, double_list *dst, double_list_cref defval,
                              string_cref comment )
{
    if ( defval.empty() )
        throw std::logic_error( msg_default_list_empty(_cur_group, key) );

    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_double_list, &NKeyFile::set_double_list,
                                  _cur_group, key, dst, defval, comment) );
}
//=======================================================================================
void NKeyFile_Schema::append( string_cref key, string_list *dst, string_list_cref defval,
                              string_cref comment )
{
    if ( defval.empty() )
        throw std::logic_error( msg_default_list_empty(_cur_group, key) );

    _check_unique( key, dst );
    _values.push_back( _make_spec(&NKeyFile::get_string_list, &NKeyFile::set_string_list,
                                  _cur_group, key, dst, defval, comment) );
}
//=======================================================================================


//=======================================================================================
//  Перегрузка сдвига для векторов нужна, чтобы при инстанцировании валидаторов не
// получать ошибок (там есть вывод сообщения, вызываться не будет).
template<class T>
static std::ostream& operator << (std::ostream&, const std::vector<T> &)
{
    throw std::logic_error("Bad vector casting.");
}
//=======================================================================================
void NKeyFile_Schema::capture( const NKeyFile &kf ) const
{
    for ( auto &val: _values )
    {
        val->capture( kf );
    }
}
//=======================================================================================
NKeyFile NKeyFile_Schema::build( NKeyFile_Schema::string_cref seed ) const
{
    auto res = NKeyFile::from_data( seed );
    fill( &res );
    return res;
}
//=======================================================================================
void NKeyFile_Schema::fill( NKeyFile *kf ) const
{
    for ( auto &val: _values )
    {
        val->save_defaults_into( kf );
    }
}
//=======================================================================================

