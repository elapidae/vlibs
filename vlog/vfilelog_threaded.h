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


#ifndef VFILELOG_THREADED_H
#define VFILELOG_THREADED_H

#include "vthread.h"
#include "vfilelog.h"
#include <memory>

//=======================================================================================
class VGroupFileLog_Threaded final
{
public:
    VGroupFileLog_Threaded( const std::string &path,
                            long one_file_size,
                            int  rotate_files_count );
    ~VGroupFileLog_Threaded();

    void execute( const VLogEntry &entry );

    void register_self();

    int queued_entries() const;

private:
    std::unique_ptr<VFileLog_Leveled> _log;
    VThread _thread;
};
//=======================================================================================
class VCommonFileLog_Threaded final
{
public:
    VCommonFileLog_Threaded( const std::string &fname,
                             long one_file_size,
                             int  rotate_files_count );
    ~VCommonFileLog_Threaded();

    void execute( const VLogEntry &entry );

    void register_self();

    int queued_entries() const;

private:
    std::unique_ptr<VFileLog_Shared> _log;
    VThread _thread;
};
//=======================================================================================



#endif // VFILELOG_THREADED_H
