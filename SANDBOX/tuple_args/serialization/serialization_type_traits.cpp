#include "serialization/serialization_type_traits.h"

#include <assert.h>
#include <limits>

#include "serialization/serialization_decoder.h"

//=======================================================================================

size_t serialization::size_of_size( size_t sz )
{
    if ( sz > std::numeric_limits<uint32_t>::max() )
        throw std::logic_error("Program not specified to write something > 2^32.");

    if ( sz <= 0x7F      ) return 1;
    if ( sz <= 0x3FFF    ) return 2;
    if ( sz <= 0x1FFFFF  ) return 3;
    if ( sz <= 0xFFFFFFF ) return 4;
    return 5;
}

//=======================================================================================

uint8_t serialization::_bool_to_byte(bool b)
{
    return b ? 0xAA : 0x11;
}

//=======================================================================================

bool serialization::_bool_from_byte(uint8_t u)
{
    if ( u == 0xAA ) return true;
    if ( u == 0x11 ) return false;
    throw AbstractDecoder::DecodeError("Boolean is not correct, must be 0xAA|0x11.");
}

//=======================================================================================
