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


#ifndef VFILELOG_H
#define VFILELOG_H

#include "vlogentry.h"
#include "voutfile_with_rotate.h"

#include "vdir.h"

//=======================================================================================
/*      07-08-2018      by Elapidae
 *
 *      Файловое логгирование
 *
 *
*/
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
    using Ptr = std::shared_ptr<VFileLog_Leveled>;

    VFileLog_Leveled( const std::string &path,
                      ulong one_file_size,
                      uint rotate_files_count );

    ~VFileLog_Leveled() = default;

    void execute( const VLogEntry &entry );

    void register_self();

private:
    VDir::MkDirError _dir_created;
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
    using Ptr = std::shared_ptr<VFileLog_Shared>;

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
