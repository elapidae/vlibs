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


#ifndef VPID_SAVER_H
#define VPID_SAVER_H


#include <string>

//=======================================================================================
__pid_t get_pid();
//=======================================================================================


//=======================================================================================
class VPid_Saver final
{
public:
    VPid_Saver( const std::string &path, const std::string &fname );
    ~VPid_Saver();

private:
    const std::string _fname;
};
//=======================================================================================


#endif // VPID_SAVER_H
