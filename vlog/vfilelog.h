#ifndef VFILELOG_H
#define VFILELOG_H

#include "vlogentry.h"
#include "voutfile_with_rotate.h"

#include "vgio_keyfile.h"


//=======================================================================================
/**     07-08-2018      by Elapidae
 *
 *      Файловое логгирование
 *
 *
**/
//=======================================================================================



//=======================================================================================
//      VAbstractFileLog
//=======================================================================================
//  Введен чисто для того, чтобы объединить в одном месте формирование сообщений из
//  вхождений логов.
class VAbstractFileLog
{
public:
    // формируем строки из вхождения, с указанием типа / без оного.
    static std::string as_line_with_type    ( const VLogEntry &entry );
    static std::string as_line_without_type ( const VLogEntry &entry );

    // Используется при записи незначащей строки в начало логгирования.
    static std::string start_line();
};
//=======================================================================================
//      VAbstractFileLog
//=======================================================================================



//=======================================================================================
//      Leveled filelog -- создает для каждого типа лога свой файл.
//=======================================================================================
class VFileLog_Leveled : VAbstractFileLog
{
public:
    VFileLog_Leveled( const std::string &path,
                      ulong one_file_size,
                      uint rotate_files_count );

    ~VFileLog_Leveled() = default;

    void execute( const VLogEntry &entry );

    void register_self();

  //-------------------------------------------------------------------------------------
    using Ptr = std::shared_ptr<VFileLog_Leveled>;
    static Ptr  load_from_keyfile( const vgio::KeyFile &kf, const std::string &group );

    static void save_to_keyfile  (vgio::KeyFile *kf, const std::string &group,
                                   bool need_log,
                                   const std::string &path,
                                   int file_size,
                                   int rotates_count );
  //-------------------------------------------------------------------------------------

private:
    bool _dir_created;
    VOutFile_With_Rotate _trace, _deb, _runlog, _warn, _fatal;
};
//=======================================================================================
//      Leveled filelog
//=======================================================================================


//=======================================================================================
//      Shared filelog -- создает один файл на все сообщения.
//=======================================================================================
class VFileLog_Shared : VAbstractFileLog
{
public:
    VFileLog_Shared( const std::string &fname,
                     ulong one_file_size,
                     uint  rotate_files_count );

    ~VFileLog_Shared() = default;

    void execute( const VLogEntry &entry );

    void register_self();

private:
    VOutFile_With_Rotate _file;
};
//=======================================================================================
//      Shared filelog
//=======================================================================================





#endif // VFILELOG_H
