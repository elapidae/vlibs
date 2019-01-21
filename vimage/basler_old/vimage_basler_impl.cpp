/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


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

