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


#include "vpid_saver.h"

#include <unistd.h>
#include "voutfile.h"
#include "vlog_pretty.h"
#include "vdir.h"
#include "verror.h"

//=======================================================================================
VPid_Saver::VPid_Saver( const std::string &path, const std::string &fname )
    : _fname( path + "/" + fname )
{
    system( ("mkdir -p " + path).c_str() );

    if ( path.empty() || fname.empty() )
        throw verror << "Путь или имя файла для сохранения PID процесса пусты.";

    VOutFile f(_fname);
    f.write( vcat(getpid()) );

    if ( !f.is_good() )
        throw verror << "Ошибка сохранения PID процесса в файле '" << _fname << "'.";
}
//=======================================================================================
VPid_Saver::~VPid_Saver()
{
    std::remove( _fname.c_str() );
}
//=======================================================================================
__pid_t get_pid()
{
    return ::getpid();
}
//=======================================================================================
