#include "vimage.h"

#include <assert.h>

//=======================================================================================
const VImage::data_t *VImage::line(int row) const
{
    assert( row < height() );
    return is_valid() ? data() + row * bytes_per_line() : nullptr;
}
//=======================================================================================
