#include "nversion.h"

#include <glib.h>

#include <stdexcept>


template<class T>
class TD;

void NVersion::check_throw()
{
    auto msg = check_version_msg( cur_major(), cur_minor(), cur_micro() );
    if (msg.empty()) return;
    throw std::logic_error( msg );
}

uint NVersion::abi_major()
{ return glib_major_version; }

uint NVersion::abi_minor()
{ return glib_minor_version; }

uint NVersion::abi_micro()
{ return glib_micro_version; }

uint NVersion::abi_binary_age()
{ return glib_binary_age; }

uint NVersion::abi_interface_age()
{ return glib_interface_age; }

std::string NVersion::check_version_msg( uint required_major,
                                         uint required_minor,
                                         uint required_micro )
{
    auto res = glib_check_version( required_major, required_minor, required_micro );
    return res ? res : std::string();
}

bool NVersion::check_version( uint required_major,
                              uint required_minor,
                              uint required_micro )
{ return GLIB_CHECK_VERSION(required_major, required_minor, required_micro); }

uint NVersion::cur_major()
{ return GLIB_MAJOR_VERSION; }

uint NVersion::cur_minor()
{ return GLIB_MINOR_VERSION; }

uint NVersion::cur_micro()
{ return GLIB_MICRO_VERSION; }
