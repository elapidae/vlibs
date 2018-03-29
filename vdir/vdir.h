#ifndef VDIR_H
#define VDIR_H

#include <string>


/*
*/


//=======================================================================================
class VDir
{
public:

    //-----------------------------------------------------------------------------------

    static bool mkdir( const std::string &dname, uint32_t mode = 0755 );

    // Описание ошибок см. ниже, после класса.
    enum class MkDirError
    {
        NoError,
        PermissionDenied, AlreadyExists, TooManyLinks, NotEnoughRoom, ParentReadOnly
    };
    static MkDirError mkdir_e( const std::string &dname, uint32_t mode = 0755 );

    //-----------------------------------------------------------------------------------

};
//=======================================================================================



//=======================================================================================
//      enum class MkDirError:
// Взято отсюда: https://www.gnu.org/software/libc/manual/html_mono/libc.html
//
//PermissionDenied -- Write permission is denied for the parent directory in which the
//    new directory is to be added.
//
//AlreadyExists -- A file named filename already exists.
//
//TooManyLinks -- The parent directory has too many links (entries). Well-designed file
//    systems never report this error, because they permit more links than your disk
//    could possibly hold. However, you must still take account of the possibility of
//    this error, as it could result from network access to a file system on another
//    machine.
//
//NotEnoughRoom -- The file system doesn’t have enough room to create the new directory.
//
//ParentReadOnly -- The parent directory of the directory being created is on
//    a read-only file system and cannot be modified.
//=======================================================================================



#endif // VDIR_H
