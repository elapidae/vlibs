#ifndef VFILELOG_THREADED_H
#define VFILELOG_THREADED_H

#include "vthread.h"
#include "vfilelog.h"
#include <memory>

//=======================================================================================
namespace vlog
{
    //===================================================================================
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
        std::unique_ptr<VGroupFileLog> _log;
        VThread _thread;
    };
    //===================================================================================
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
        std::unique_ptr<VCommonFileLog> _log;
        VThread _thread;
    };
    //===================================================================================
}
//=======================================================================================



#endif // VFILELOG_THREADED_H
