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


#ifndef VFILELOG_KEYFILE_H
#define VFILELOG_KEYFILE_H

#include <memory>

#include "vfilelog.h"
#include "vfilelog_threaded.h"

#include "vgio_keyfile.h"

//=======================================================================================
/*  16-04-2018
 *  Задача класса -- считывать и записывать параметры логов в/из NKeyFile.
 *
*/
//=======================================================================================



//=======================================================================================
namespace vlog
{
    //===================================================================================
    using VGroupFileLog_SharedPtr          = std::shared_ptr<VFileLog_Leveled>;
    using VGroupFileLog_Threaded_SharedPtr = std::shared_ptr<VGroupFileLog_Threaded>;

    using VCommonFileLog_SharedPtr          = std::shared_ptr<VFileLog_Shared>;
    using VCommonFileLog_Threaded_SharedPtr = std::shared_ptr<VCommonFileLog_Threaded>;


    //===================================================================================
    class VFilelog_KeyFile
    {
    public:
        //===============================================================================
        static VGroupFileLog_SharedPtr read_grouplog  (const vgio::KeyFile &kf,
                                                        const std::string &group );

        static VCommonFileLog_SharedPtr read_commonlog( const vgio::KeyFile &kf,
                                                        const std::string &group );

        static VGroupFileLog_Threaded_SharedPtr
                                read_grouplog_threaded( const vgio::KeyFile &kf,
                                                        const std::string &group );

        static VCommonFileLog_Threaded_SharedPtr
                               read_commonlog_threaded( const vgio::KeyFile &kf,
                                                        const std::string &group );


        //===============================================================================
        static void write_grouplog_params ( vgio::KeyFile *dst,
                                            const std::string &group,
                                            bool need,
                                            const std::string &path,
                                            int fsize,
                                            int fcount );

        static void write_commonlog_params( vgio::KeyFile *dst,
                                            const std::string &group,
                                            bool need,
                                            const std::string &fname,
                                            int fsize,
                                            int fcount );

        //===============================================================================
    };
    //===================================================================================
}
//=======================================================================================




#endif // VFILELOG_KEYFILE_H
