#ifndef VKEYFILE_H
#define VKEYFILE_H

#include <vector>
#include <string>
#include <memory>
#include "nerror.h"

//=======================================================================================
//  VKeyFile -- надстройка для достаточно стандартного использования файлов
//  конфигурации. Предполагается, что существуют настройки по умолчанию, которые
//  загружаются при создании объекта вместе с имененм файла настроек.
//  При запросе значения, если он не указан в файле настроек, берется значение
//  по умолчанию. Таким образом, при написании не нужно проверять наличие ключа.
//=======================================================================================



//=======================================================================================
class VKeyFile
{
public:
    using StringList = std::vector<std::string>;
    using BoolList   = std::vector<bool>;
    using IntList    = std::vector<int>;
    using DoubleList = std::vector<double>;
    using str        = std::string;

    VKeyFile( const str &cfg_fname,
              const str &defaults_cfg,
              NError *err = nullptr,
              char list_separator = ',' );

    ~VKeyFile() = default;

    void write_defaults_to( const std::string &fname ) const;
    void print_defaults() const;

    str        get_string      ( const str &group, const str &key ) const;
    bool       get_bool        ( const str &group, const str &key ) const;
    int        get_int         ( const str &group, const str &key ) const;
    int64_t    get_int64       ( const str &group, const str &key ) const;
    uint64_t   get_uint64      ( const str &group, const str &key ) const;
    double     get_double      ( const str &group, const str &key ) const;

    StringList get_string_list ( const str &group, const str &key ) const;
    BoolList   get_bool_list   ( const str &group, const str &key ) const;
    IntList    get_int_list    ( const str &group, const str &key ) const;
    DoubleList get_double_list ( const str &group, const str &key ) const;

    void set_string      ( const str &group, const str &key, const str &val ) const;
    void set_bool        ( const str &group, const str &key, bool       val ) const;
    void set_int         ( const str &group, const str &key, int        val ) const;
    void set_int64       ( const str &group, const str &key, int64_t    val ) const;
    void set_uint64      ( const str &group, const str &key, uint64_t   val ) const;
    void set_double      ( const str &group, const str &key, double     val ) const;

    void set_string_list (const str &group, const str &key, const StringList &val) const;
    void set_bool_list   (const str &group, const str &key, const BoolList   &val) const;
    void set_int_list    (const str &group, const str &key, const IntList    &val) const;
    void set_double_list (const str &group, const str &key, const DoubleList &val) const;


private:
    class Pimpl; std::shared_ptr<Pimpl> p;
};
//=======================================================================================


#endif // VKEYFILE_H
