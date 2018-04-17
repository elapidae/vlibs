#ifndef VFILELOG_H
#define VFILELOG_H

#include "vlogentry.h"
#include "voutfile_withrotate.h"


//=======================================================================================
namespace vlog
{
    //===================================================================================
    class VFileLog
    {
    public:
        // формируем строки из вхождения, с указанием типа / без оного.
        static std::string as_line_with_type( const VLogEntry &entry );
        static std::string as_line_without_type( const VLogEntry &entry );

        // Используется при записи незначащей строки в начало логгирования.
        static std::string start_line();
    };
    //===================================================================================


    //===================================================================================
    //      Group filelog -- создает для каждого типа лога свой файл.
    //===================================================================================
    class VGroupFileLog : VFileLog
    {
    public:
        VGroupFileLog( const std::string &path,
                       long one_file_size,
                       int  rotate_files_count );

        void execute( const VLogEntry &entry );

        void register_self();

    private:
        bool _dir_created;
        VOutFile_WithRotate
            _trace,
            _deb,
            _runlog,
            _warn,
            _fatal;
    };
    //===================================================================================
    //      Group filelog
    //===================================================================================


    //===================================================================================
    //      Common filelog -- создает один файл на все сообщения.
    //===================================================================================
    class VCommonFileLog : VFileLog
    {
    public:
        VCommonFileLog( const std::string &fname,
                     long one_file_size,
                     int  rotate_files_count );

        void execute(const VLogEntry &entry );

        void register_self();

    private:
        VOutFile_WithRotate _file;
    };
    //===================================================================================
    //      Common filelog
    //===================================================================================
} // vlog namespace
//=======================================================================================




#endif // VFILELOG_H
