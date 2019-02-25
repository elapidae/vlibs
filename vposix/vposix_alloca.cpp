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


#include "vposix_alloca.h"

#include "vlog.h"
#include <malloc.h>
#include "vposix_core.h"
#include <stdexcept>

using namespace vposix;

//=======================================================================================
void *Alloca::do_allocate( size_t sz )
{
    if ( do_trace() ) vtrace("V::alloca(", sz, ")" );

    auto res = alloca( sz );
    if ( !res ) throw std::bad_alloc();

    return res;
}
//=======================================================================================
