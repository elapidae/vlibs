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

    switch (errno)
    {
    case EACCES: return MkDirError::PermissionDenied;
    case EEXIST: return MkDirError::AlreadyExists;
    case EMLINK: return MkDirError::TooManyLinks;
    case ENOSPC: return MkDirError::NotEnoughRoom;
    case EROFS:  return MkDirError::ParentReadOnly;
    default:
        throw std::runtime_error("Cannot define mkdir error type...");
    }
}
//=======================================================================================

