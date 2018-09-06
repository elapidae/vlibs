#ifndef VCRC_H
#define VCRC_H

#include <stdint.h>
#include <string>

class vcrc
{
public:

    static uint32_t poly_04C11DB7( const std::string& buf );
};



#endif // VCRC_H
