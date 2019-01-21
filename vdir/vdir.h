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
        PermissionDenied, AlreadyExists, TooManyLinks, NotEnoughRoom, ParentReadOnly,
        NoSuchFileOrDirectory   // Ошибка в документации не прописанная, но вполне себе
                                // возникающая при отсутствии пути до создаваемой папки.
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
