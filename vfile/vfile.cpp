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


#include "vfile.h"

#include <assert.h>
#include <verror.h>

//#include "vposix_errno.h"
#include "vposix_files.h"

#include <fcntl.h>


using namespace tr1;



//=======================================================================================
int VFile::helpers::mode_readwrite( VFile::Mode_ReadWrite mode )
{
    switch (mode)
    {
    case Mode_ReadWrite::ReadOnly:  return O_RDONLY;
    case Mode_ReadWrite::WriteOnly: return O_WRONLY;
    case Mode_ReadWrite::ReadWrite: return O_RDWR;
    }
    assert( false && "Bad Mode_RW." );
}
//=======================================================================================
//  Не работает...
//int VFile::helpers::mode_exclusive( VFile::Mode_Exclusive mode )
//{
//    switch (mode)
//    {
//    case Mode_Exclusive::Yes:   return O_EXCL;
//    case Mode_Exclusive::No:    return 0;
//    }
//    assert( false && "Bad Mode_Exclusive." );
//}
//=======================================================================================


//=======================================================================================
VFile::VFile( cstr fname, Mode_ReadWrite rw )
{
    int flags = O_CLOEXEC | O_CREAT;
    flags |= helpers::mode_readwrite( rw );
    //flags |= helpers::mode_exclusive( exclusive );

    mode_t mode = 0666;

    _fd = vposix::Files::open_mode( fname, flags, mode );
}
//=======================================================================================
void VFile::write( VFile::cstr buffer )
{
    auto count = vposix::Files::write( _fd, buffer );

    if ( count != ssize_t(buffer.size()) )
        throw verror << "count != buffer.size()";
}
//=======================================================================================



//=======================================================================================
//VFileExclusive::VFileExclusive( VFile::cstr fname, VFile::Mode_ReadWrite rw )
//    : VFile( fname, rw, Mode_Exclusive::Yes )
//{}
//=======================================================================================
