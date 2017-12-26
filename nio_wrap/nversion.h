#ifndef NVERSION_H
#define NVERSION_H

#include <sys/types.h>
#include <string>

//#include "vdeb.h"

class NVersion
{
public:
    // Throws std::logic_error
    static void check_throw();

    static uint abi_major();
    static uint abi_minor();
    static uint abi_micro();
    static uint abi_binary_age();
    static uint abi_interface_age();

    static std::string check_version_msg( uint required_major,
                                          uint required_minor,
                                          uint required_micro );
    static bool check_version( uint required_major,
                               uint required_minor,
                               uint required_micro );

    static uint cur_major();
    static uint cur_minor();
    static uint cur_micro();
};

#endif // NVERSION_H
