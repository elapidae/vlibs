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


#ifndef NCONVERTINGHELPER_H
#define NCONVERTINGHELPER_H

#include <vector>
#include <string>

//=======================================================================================
namespace vgio
{
    //===================================================================================
    namespace _impl
    {
        //===============================================================================
        //  Вызывает g_strfreev в случае необходимости.
        std::vector<std::string> convert_and_free_list( char ** list );
        //===============================================================================
        //  Вызывает g_free в случае необходимости.
        std::string convert_and_free( char * raw );
        //===============================================================================

    } // _impl namespace
    //===================================================================================

} // vgio namespace
//=======================================================================================



#endif // NCONVERTINGHELPER_H
