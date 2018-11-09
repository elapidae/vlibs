#ifndef VPOSIX_FILES_H
#define VPOSIX_FILES_H

#include <string>
#include "vposix_core.h"


//=======================================================================================
namespace vposix
{
    //===================================================================================
    class Files
    {
        static constexpr bool trace = true;
    public:
        using cstr = const std::string&;

        static int open( cstr name, int flags );
        static int open_mode( cstr name, int flags, mode_t mode );

        static ssize_t write_raw( int fd, const void *buf, size_t count );
        static ssize_t write( int fd, cstr buf);

        static int remove_raw( const char *pathname );
        static int remove( cstr pathname );

        static void close( int fd );
    };
    //===================================================================================

} // namespace vposix
//=======================================================================================

#endif // VPOSIX_FILES_H
