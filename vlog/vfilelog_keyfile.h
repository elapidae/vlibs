#ifndef VFILELOG_KEYFILE_H
#define VFILELOG_KEYFILE_H

#include <memory>

#include "vfilelog.h"
#include "vfilelog_threaded.h"

#include "nkeyfile.h"

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
    using VGroupFileLog_SharedPtr          = std::shared_ptr<VGroupFileLog>;
    using VGroupFileLog_Threaded_SharedPtr = std::shared_ptr<VGroupFileLog_Threaded>;

    using VCommonFileLog_SharedPtr          = std::shared_ptr<VCommonFileLog>;
    using VCommonFileLog_Threaded_SharedPtr = std::shared_ptr<VCommonFileLog_Threaded>;


    //===================================================================================
    class VFilelog_KeyFile
    {
    public:
        //===============================================================================
        static VGroupFileLog_SharedPtr read_grouplog  (const NKeyFile &kf,
                                                        const std::string &group );

        static VCommonFileLog_SharedPtr read_commonlog( const NKeyFile &kf,
                                                        const std::string &group );

        static VGroupFileLog_Threaded_SharedPtr
                                read_grouplog_threaded( const NKeyFile &kf,
                                                        const std::string &group );

        static VCommonFileLog_Threaded_SharedPtr
                               read_commonlog_threaded( const NKeyFile &kf,
                                                        const std::string &group );


        //===============================================================================
        static void write_grouplog_params ( NKeyFile *dst,
                                            const std::string &group,
                                            bool need,
                                            const std::string &path,
                                            int fsize,
                                            int fcount );

        static void write_commonlog_params( NKeyFile *dst,
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
