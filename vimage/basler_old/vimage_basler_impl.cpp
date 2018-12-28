#include "vimage_basler_impl.h"

#include <stdexcept>
#include <assert.h>

//=======================================================================================
VImage::Format VImage_BaslerRef_Impl::baslerFormat_to_format(BaslerPicFormat f)
{

}
//=======================================================================================
VImage_BaslerRef_Impl::VImage_BaslerRef_Impl( const BaslerFrame *frame )
    : _frame( frame )
{
    assert( _frame );
}
//=======================================================================================
bool VImage_BaslerRef_Impl::is_valid() const
{
    return _frame->is_valid();
}
//=======================================================================================
VImage::Format VImage_BaslerRef_Impl::format() const
{

}
//=======================================================================================
int VImage_BaslerRef_Impl::width() const
{

}

int VImage_BaslerRef_Impl::height() const
{

}

int VImage_BaslerRef_Impl::bytes_per_line() const
{

}

const VImage::data_t *VImage_BaslerRef_Impl::data() const
{

}

const VImage::data_t *VImage_BaslerRef_Impl::line(int row) const
{

}

void VImage_BaslerRef_Impl::detach()
{

}

