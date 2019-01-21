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


#ifndef VLOGENTRY_H
#define VLOGENTRY_H

#include "vcat.h"
#include "vtimepoint.h"


//=======================================================================================
/** 2018-07-03 by Elapidae
 *
 *  VLogEntry -- точка вхождения логгирующего сообщения.
 *  Самим его создавать не надо, только принимать на непосредственное логгирование.
 *  Методы д/б очевидны для использования, составляйте из них вкусные сообщения.
 *
 *  TODO: Доставить приличное описание.
 *
 *
**/
//=======================================================================================


//=======================================================================================
// [1]: 3-х символьное обозначение уровня: TRC, DBG, RUN, WRN, FLT;
//      Односимвольный код уровня: T, D, R, W, F.
//      Символьные обозначения применяются при записи логов, чтобы размеры поля
//      были одинаковыми. Также применяется при сериализации (гораздо проще тащить один
//      символ с очевидным значением).
//---------------------------------------------------------------------------------------
class VLogEntry final
{
public:

    //-----------------------------------------------------------------------------------

    enum class Level { Trace, Dbg, Runlog, Warning, Fatal };

    //-----------------------------------------------------------------------------------

    const std::string& message()    const;

    VTimePoint  timestamp()         const;

    std::string filename()          const;  //  только имя файла (путь отсечен).
    const char* filepath()          const;  //  полный путь, обычно ведет к build-папке.

    int32_t     line()              const;

    const char* function()          const;  //  Значение макроса __FUNCTION__.

    Level       level()             const;  //  См. [1]:
    std::string level_str()         const;  //  3-х символьное обозначение уровня.
    char        level_char()        const;  //  Односимвольный код уровня.

    bool        is_trace()          const;
    bool        is_debug()          const;
    bool        is_runlog()         const;
    bool        is_warning()        const;
    bool        is_fatal()          const;

                                            //  Возвращает конструкцию вида:
    std::string place()             const;  //  "[filename.cpp:123]"
    std::string place_func()        const;  //  "[filename.cpp:123=>function]"
    //-----------------------------------------------------------------------------------
    //  Сервисная часть, нормальным людям ни к чему.

    //  Здесь собраны более-менее стандартные способы представления вхождения в виде
    //  записи в журнале.
    class Record;
    const Record record() const;

    //  Обратная функция к level_char(). Нужно при десериализации.
    static Level level_from_char( char ch );

    //  Предназначен для использования внутри других механизмов, конечному пользователю
    //  конструировать этот объект не нужно.
    VLogEntry( Level                level,
               const VTimePoint&    stamp,
               const char*          file,
               int                  line,
               const char*          func,
               const std::string&   msg );

    //  Возвращает все что после последнего символа '/'.
    //  Вообще-то здесь этой задаче не место, но оставил здесь, чтобы было минимальное
    //  сцепление с другими частями vlibs.
    static std::string _extract_filename( const std::string & fpath );

    //-----------------------------------------------------------------------------------
private:

    Level           _level;
    VTimePoint      _stamp;
    const char*     _file;
    int             _line;
    const char*     _func;
    std::string     _msg;
};
//=======================================================================================
//=======================================================================================


//=======================================================================================
//=======================================================================================
//  В обозначениях:
//  place       --  [filename:123]
//  level       --  level_str() == TRC, DBG, RUN, WRN, FLT
//  time        --  yyyy-MM-dd hh:mm:ss.zzz
//  msg         --  message
//  nl          --  new line (\n)
class VLogEntry::Record
{
public:
    std::string place_level_msg() const;

    std::string time_place_msg_nl() const;

    std::string time_place_level_msg_nl() const;

    // Линия вида "======= BEGIN LOGGING ========= yyyy-MM-dd hh:mm:ss.zzz ======".
    static std::string begin_line_time_nl();

private:
    const VLogEntry *_entry;

    friend class VLogEntry;
    Record( const VLogEntry *entry );
};
//=======================================================================================
//=======================================================================================




#endif // VLOGENTRY_H
