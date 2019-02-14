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


#ifndef VGIT_H
#define VGIT_H

#include <string>


//=======================================================================================
class VGit
{
public:
    static std::string revcount();
    static std::string hash();
    static std::string date();
    static std::string author();
    static std::string branch();

    // Метка времени компиляции.
    // К git отношения не имеет, но здесь вполне уместно...
    static std::string compile_datetime();

    // принимает --vgit-branch, --vgit-hash, --vgit-revcount, --vgit-date, vgit-author,
    //           --vgit-full.
    // Возвращает, соответственно. По умолчанию и при ошибках использует --vgit-full
    static std::string as_message( const std::string &query = "--vgit-full" );

    // ищет параметры вида --vgit*, если найдет, печатает соответствующее сообщение
    // и выходит по exit(retcode);
    static void print_and_exit_if_need( int argc,
                                        const char * const * const argv,
                                        int retcode = 0 );
};
//=======================================================================================


#endif // VGIT_H
