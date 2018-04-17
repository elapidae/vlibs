#ifndef NKEYFILE_H
#define NKEYFILE_H

#include <vector>
#include "nerror.h"


//=======================================================================================
//      NKeyFile
//=======================================================================================
class NKeyFile final
{
public:
    using StringList = std::vector<std::string>;
    using BoolList   = std::vector<bool>;
    using IntList    = std::vector<int>;
    using DoubleList = std::vector<double>;
    using str        = std::string;


    //-------------------------------------------------------------------------------
    enum class OpenFlag
    {
        ReadOnly,       // Don't save comment & locale (use G_KEY_FILE_NONE)
        ReadWrite       // (G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS)
    };

    static NKeyFile from_file( const str &fname,
                               OpenFlag flag = OpenFlag::ReadOnly,
                               NError *err = nullptr );

    static NKeyFile from_data( const str &data,                               
                               OpenFlag flag = OpenFlag::ReadOnly,
                               NError *err = nullptr );

    explicit NKeyFile();

    str  to_string( NError *err = nullptr ) const;
    bool to_file( const str &fname, NError *err = nullptr );
    //-------------------------------------------------------------------------------

    // Выставление обязательно перед использованием методов списков *_list().
    void set_list_separator( char sep );

    bool is_valid() const;

    bool has_group( const str &group ) const;
    StringList get_groups() const;
    str get_start_group() const;

    bool has_key( const str &group, const str &key, NError *err = nullptr ) const;
    StringList get_keys( const str &group, NError *err = nullptr ) const;
    //-------------------------------------------------------------------------------

    str      get_value ( const str &group, const str &key, NError *err = nullptr ) const;
    str      get_string( const str &group, const str &key, NError *err = nullptr ) const;
    bool     get_bool  ( const str &group, const str &key, NError *err = nullptr ) const;
    int      get_int   ( const str &group, const str &key, NError *err = nullptr ) const;
    int64_t  get_int64 ( const str &group, const str &key, NError *err = nullptr ) const;
    uint64_t get_uint64( const str &group, const str &key, NError *err = nullptr ) const;
    double   get_double( const str &group, const str &key, NError *err = nullptr ) const;

    StringList get_string_list ( const str &group, const str &key,
                                 NError *err = nullptr ) const;
    BoolList   get_bool_list   ( const str &group, const str &key,
                                 NError *err = nullptr ) const;
    IntList    get_int_list    ( const str &group, const str &key,
                                 NError *err = nullptr ) const;
    DoubleList get_double_list ( const str &group, const str &key,
                                 NError *err = nullptr ) const;

    str get_comment( const str &group, const str &key, NError *err = nullptr ) const;
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    //  Safety methods, don't throw exceptions, returns default vals.
    str      safe_value  ( const str &group, const str &key,
                           const str &defval = "" ) const;
    str      safe_string ( const str &group, const str &key,
                           const str &defval = "" ) const;
    bool     safe_bool   ( const str &group, const str &key,
                           bool defval = false ) const;
    int      safe_int    ( const str &group, const str &key,
                           int defval = 0 ) const;
    int64_t  safe_int64  ( const str &group, const str &key,
                           int64_t defval = 0 ) const;
    uint64_t safe_uint64 ( const str &group, const str &key,
                           uint64_t defval = 0 ) const;
    double   safe_double ( const str &group, const str &key,
                           double defval = 0 ) const;
    //-------------------------------------------------------------------------------


    void set_value  ( const str &group, const str &key, const str &val );
    void set_string ( const str &group, const str &key, const str &val );
    void set_bool   ( const str &group, const str &key, bool       val );
    void set_int    ( const str &group, const str &key, int        val );
    void set_int64  ( const str &group, const str &key, int64_t    val );
    void set_uint64 ( const str &group, const str &key, uint64_t   val );
    void set_double ( const str &group, const str &key, double     val );


    void set_string_list ( const str &group, const str &key, const StringList &val );
    void set_bool_list   ( const str &group, const str &key, const BoolList   &val );
    void set_int_list    ( const str &group, const str &key, const IntList    &val );
    void set_double_list ( const str &group, const str &key, const DoubleList &val );

    bool set_comment ( const str &group, const str &key, const str &val,
                       NError *err = nullptr );
    //-------------------------------------------------------------------------------

    bool remove_group   ( const str &group, NError *err = nullptr );
    bool remove_key     ( const str &group, const str &key, NError *err = nullptr );
    bool remove_comment ( const str &group, const str &key, NError *err = nullptr );


    //-------------------------------------------------------------------------------
private:
    std::shared_ptr<GKeyFile> p;

    template<typename T, typename gFn>
    std::vector<T> _get_any_simple_list( const str &group, const str &key,
                                         gFn fn, NError *err = nullptr ) const;
};
//=======================================================================================
//      NKeyFile
//=======================================================================================


//=======================================================================================
//      Implementation
//=======================================================================================
template<typename T, typename gFn>
std::vector<T> NKeyFile::_get_any_simple_list( const std::string &group,
                                               const std::string &key,
                                               gFn fn, NError *err ) const
{
    _NErrorProxy err_proxy( err );
    gsize len;
    auto * ptr = fn( p.get(), group.c_str(), key.c_str(), &len, err_proxy );

    auto res = ptr ? std::vector<T>(ptr, ptr + len) : std::vector<T>();
    if (ptr) g_free(ptr);
    return res;
}
//=======================================================================================
//      Implementation
//=======================================================================================



#endif // NKEYFILE_H
