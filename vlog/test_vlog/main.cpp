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


#include <iostream>
#include "gtest/gtest.h"

#include "vlog.h"
#include "vfilelog.h"

using namespace std;

//=======================================================================================
//  Пример-затравка для пользовательской обработки логов.
void my_log_executer( const VLogEntry &entry )
{
    // Ниже приведены содержания из точки логгирования.
    // Их следует использовать для составления собственных сообщений.

    entry.timestamp();  // Метка времени создания вхождения.

    entry.level_char(); // Однобуквенный код типа сообщения { T, D, R, W, F }.
    entry.level_str();  // Трехбуквенный код типа сообщения { TRC, DBG, RUN, WRN, FLT }.
    entry.level();      // Тип enum class vlog::VLogEntry::Type.

    entry.filename();   // Имя файла без пути до него.
    entry.filepath();   // Полное имя файла (то, что дает __FILE__).
    entry.line();       // Номер строки в исходнике __LINE__
    entry.function();   // Что дает __FUNCTION__ (ИМХО __PRETTY_FUNCTION__ - не pretty).

    entry.message();    //  Составленное сообщение.

    entry.is_trace();   //  Для быстрой проверки к-л уровня.
    entry.is_debug();   //
    entry.is_runlog();  //
    entry.is_warning(); //
    entry.is_fatal();   //

    cout << "my_log_executer: " << entry.message() << endl;
}
//=======================================================================================

class VLog_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VLog_Test, _1 )
{
    // По умолчанию будет выводить в консоль.
    vrunlog << "Hello World!"
            << "sizeof(VLogEntry):"  << sizeof(VLogEntry)
            << "sizeof(VTimePoint):" << sizeof(VTimePoint)
            << "sizeof(string):"     << sizeof(string);

    //  Вводные примеры, определим пару простых переменных и плюнем ими в консоль.
    double dd = 3.1415;
    float  ff = 2.718f;
    int    ii = 42;
    std::chrono::milliseconds ms(12345); // и такое выводим`c...

    vdeb; // пустая строка
    vdeb << "------- same syntax example.";
    vdeb << dd << ff << ii << ms;   // Одно
    vdeb(dd, ff, ii, ms);           // и то
    vdeb(dd)(ff)(ii)(ms);           // же.

    // Примеры с манипуляторами вывода потока.
    double long_term_val = 1.0 / 3.0; // Значение с большим кол-вом знаков после запятой.
    vdeb << "------ precision example.";
    vdeb << long_term_val;                    // выведет мало знаков.
    vdeb.max_precision() << long_term_val;    // выведет максимальное кол-во знаков.

    vdeb << "------ fill & width example.";
    vdeb.fill_char('0').field_width(5) << 42; // 00042
    vdeb.num(42, 5, '0');                     // то же самое, 00042
                                              // специально заточено под эту задачу.
    vdeb << "------------------------------";

    // Вывод без пробелов между аргументами:
    string prog_name = VLogEntry::_extract_filename( "some-dir/some-file.exe" );
    vtrace.nospace()( "filename is '", prog_name, "'." );

    // Теперь будем логгировать в cerr, удалим всех исполнителей и добавим исполнитель,
    // который будет писать в cerr (vlog::VLogger::_log_to_cerr).
    VLogger::clear_executers();
    VLogger::add_executer( VLogger::to_cerr );
    vrunlog << "Hello World in cerr!";

    // регистрируем своего исполнителя.
    VLogger::add_executer( my_log_executer );
    vwarning("After register own executer.");


    // Удалим текущие логгеры и будем писать только в файлы.
    VLogger::clear_executers();

    // Будем вести историю максимум в двух файлах, размеры одного -- 2.5 кб.
    VFileLog_Shared shared_flog( vcat("shared-log.log"), 2500, 2 );
    shared_flog.register_self(); // Он сам знает где и как регистрироваться.

    // Будем вести историю максимум в двух файлах, размеры одного -- 1 кб.
    VFileLog_Leveled leveled_flog( "./logs", 1000, 2 );
    leveled_flog.register_self();

    for (int i = 0; i < 10; ++i)
    {
        string msg = vcat("Testing records in file: ", i)
                         (", timestamp ms = ", VTimePoint::now().milliseconds());
        vtrace   (msg);
        vdeb   (msg);
        vrunlog  (msg);
        vwarning (msg);
        vfatal   (msg);
    }
    // См. логи около бинарника программы.
}
//=======================================================================================
