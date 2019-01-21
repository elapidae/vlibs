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


#include "vdir.h"

#include <sys/stat.h>
#include <stdexcept>


//=======================================================================================
bool VDir::mkdir(const std::string &dname, uint32_t mode)
{
    return mkdir_e(dname, mode) == MkDirError::NoError;
}
//=======================================================================================
VDir::MkDirError VDir::mkdir_e( const std::string &dname, mode_t mode )
{
    static_assert( std::is_same<mode_t,uint32_t>::value ,"");

    if ( ::mkdir(dname.c_str(), mode) == 0 ) return MkDirError::NoError;

    auto err = errno;
    switch (err)
    {
    case EACCES: return MkDirError::PermissionDenied;
    case EEXIST: return MkDirError::AlreadyExists;
    case EMLINK: return MkDirError::TooManyLinks;
    case ENOSPC: return MkDirError::NotEnoughRoom;
    case EROFS:  return MkDirError::ParentReadOnly;
    case ENOENT: return MkDirError::NoSuchFileOrDirectory;
    default:
        throw std::runtime_error("Cannot define mkdir error type...");
    }
}
//=======================================================================================

