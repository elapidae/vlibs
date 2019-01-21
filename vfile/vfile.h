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


#ifndef VFILE_H
#define VFILE_H

//=======================================================================================
//  TODO: утащить все сырые посиксовые неприятности в vposix_files.
//
//=======================================================================================


#include <string>


//=======================================================================================
namespace tr1
{
    //===================================================================================
    class VFile
    {
    public:
        using cstr = const std::string&;

        enum class Mode_ReadWrite { ReadOnly, WriteOnly, ReadWrite };
        //enum class Mode_Exclusive { Yes, No };

        //VFile( cstr fname, Mode_ReadWrite rw, Mode_Exclusive exclusive );
        VFile( cstr fname, Mode_ReadWrite rw = Mode_ReadWrite::ReadWrite );

        void write( cstr buffer );

    private:
        int _fd = 0;

        struct helpers
        {
            static int mode_readwrite( Mode_ReadWrite mode );
            //static int mode_exclusive( Mode_Exclusive mode );
        };
    };
    //===================================================================================
    //class VFileExclusive : public VFile
    //{
    //public:
    //    VFileExclusive( cstr fname, Mode_ReadWrite rw = Mode_ReadWrite::ReadWrite );
    //};
    //===================================================================================

} // namespace tr1
//=======================================================================================


#endif // VFILE_H
