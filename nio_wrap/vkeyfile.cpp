#include "vkeyfile.h"

#include "nkeyfile.h"
#include <iostream>
#include "nfile.h"

using namespace std;


//=======================================================================================
class VKeyFile::Pimpl
{
public:
    NKeyFile def;
    NKeyFile cfg;
    string str_defaults;
};
//=======================================================================================
VKeyFile::VKeyFile( const VKeyFile::str &cfg_fname,
                    const VKeyFile::str &defaults_cfg,
                    NError *err,
                    char list_separator )
    : p( new Pimpl )
{
    p->str_defaults = defaults_cfg;

    p->cfg = NKeyFile::from_file( cfg_fname, NKeyFile::OpenFlag::ReadOnly, err );

    p->cfg.set_list_separator( list_separator );

    p->def = NKeyFile::from_data( defaults_cfg );
    p->def.set_list_separator( list_separator );
}
//=======================================================================================
void VKeyFile::write_defaults_to( const string &fname ) const
{
    auto f = NFile::for_path( fname );
    auto outs = f.replace();
    outs.write( p->str_defaults );
}
//=======================================================================================
void VKeyFile::print_defaults() const
{
    cout << p->str_defaults << endl;
}
//=======================================================================================
VKeyFile::str VKeyFile::get_string( const str &group, const str &key ) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_string( group, key );
}
//=======================================================================================
bool VKeyFile::get_bool( const str &group, const str &key ) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_bool( group, key );
}
//=======================================================================================
int VKeyFile::get_int(const str &group, const str &key) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_int( group, key );
}
//=======================================================================================
int64_t VKeyFile::get_int64(const str &group, const str &key) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_int64( group, key );
}
//=======================================================================================
uint64_t VKeyFile::get_uint64(const str &group, const str &key) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_uint64( group, key );
}
//=======================================================================================
double VKeyFile::get_double(const str &group, const str &key) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_double( group, key );
}
//=======================================================================================
VKeyFile::StringList VKeyFile::get_string_list(const str &group, const str &key) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_string_list( group, key );
}
//=======================================================================================
VKeyFile::BoolList VKeyFile::get_bool_list(const str &group, const str &key) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_bool_list( group, key );
}
//=======================================================================================
VKeyFile::IntList VKeyFile::get_int_list(const str &group, const str &key) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_int_list( group, key );
}
//=======================================================================================
VKeyFile::DoubleList VKeyFile::get_double_list(const str &group, const str &key) const
{
    auto & kf = p->cfg.has_group(group) && p->cfg.has_key(group,key) ? p->cfg : p->def;
    return kf.get_double_list( group, key );
}
//=======================================================================================


//=======================================================================================
void VKeyFile::set_string( const str &group, const str &key, const str &val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_string( group, key, val );
}
//=======================================================================================
void VKeyFile::set_bool( const str &group, const str &key, bool val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_bool( group, key, val );
}
//=======================================================================================
void VKeyFile::set_int( const str &group, const str &key, int val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_int( group, key, val );
}
//=======================================================================================
void VKeyFile::set_int64( const str &group, const str &key, int64_t val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_int64( group, key, val );
}
//=======================================================================================
void VKeyFile::set_uint64( const str &group, const str &key, uint64_t val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_uint64( group, key, val );
}
//=======================================================================================
void VKeyFile::set_double( const str &group, const str &key, double val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_double( group, key, val );
}
//=======================================================================================
void VKeyFile::set_string_list( const str &group, const str &key,
                                const VKeyFile::StringList &val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_string_list( group, key, val );
}
//=======================================================================================
void VKeyFile::set_bool_list( const str &group, const str &key,
                              const VKeyFile::BoolList &val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_bool_list( group, key, val );
}
//=======================================================================================
void VKeyFile::set_int_list( const str &group, const str &key,
                             const VKeyFile::IntList &val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_int_list( group, key, val );
}
//=======================================================================================
void VKeyFile::set_double_list( const str &group, const str &key,
                                const VKeyFile::DoubleList &val ) const
{
    auto & kf = p->cfg.is_valid() ? p->cfg : p->def;
    kf.set_double_list( group, key, val );
}
//=======================================================================================
