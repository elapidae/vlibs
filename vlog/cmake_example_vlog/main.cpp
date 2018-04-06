#include <iostream>

#include "vlog.h"
#include "vfilelog_threaded.h"

using namespace std;

//=======================================================================================
//  Пример-затравка для пользовательской обработки логов.
void my_log_executer( const vlog::VLogEntry &entry )
{
    // Ниже приведены содержания из точки логгирования.
    // Их следует использовать для составления собственных сообщений.

    entry.char_type();  // Однобуквенный код типа сообщения. { T, D, R, W, F }
    entry.str_type();   // Трехбуквенный код типа сообщения { Trc, Dbg, Run, Wrn, Ftl }.
    entry.type();       // Тип enum class vlog::VLogEntry::Type.

    entry.filename();   // Имя файла без пути до него.
    entry.filepath();   // Полное имя файла (то, что дает __FILE__).
    entry.line();       // Номер строки в исходнике __LINE__
    entry.funcname();   // Что дает __FUNCTION__ (может надо будет __PRETTY_FUNCTION__?).

    entry.message();    // Составленное сообщение.

    entry.timestamp();  // Метка времени создания вхождения.

    entry.is_fatal();   // Флаг неприятного сообщения. Может захотите сделать exit();

    cout << "my_log_executer: " << entry.message() << endl;
}
//=======================================================================================


//=======================================================================================
int main( int, char **argv )
{
    // По умолчанию будет выводить в консоль.
    VRUNLOG << "Hello World!";

    double dd = 3.1415;
    float  ff = 2.718f;
    int    ii = 42;
    std::chrono::milliseconds ms(12345); // и такое выводим`c...

    VDEBUG; // пустая строка
    VDEBUG << dd << ff << ii << ms;   // Одно
    VDEBUG(dd, ff, ii, ms);           // и то
    VDEBUG(dd)(ff)(ii)(ms);           // же.

    // Примеры с манипуляторами вывода потока.
    double long_term_val = 1.0 / 3.0; // Значение с большим кол-вом знаков после запятой.
    VDEBUG << "------ precision example.";
    VDEBUG << long_term_val;                    // выведет мало знаков.
    VDEBUG.max_precision() << long_term_val;    // выведет максимальное кол-во знаков.
    VDEBUG << "------ fill & width example.";
    VDEBUG.fill_char('0').field_width(5) << 42; // 00042
    VDEBUG << "------------------------------";

    // Вывод без пробелов между аргументами:
    auto prog_name = VString(argv[0]).split('/').back(); // удаляем путь в программе.
    VTRACE.nospace()( "My program name is '", prog_name, "'." );

    // Теперь будем логгировать в cerr, удалим всех исполнителей и добавим исполнитель,
    // который будет писать в cerr (vlog::VLogger::_log_to_cerr).
    vlog::VLogger::clear_executers();
    vlog::VLogger::add_executer( vlog::VLogger::_log_to_cerr );
    VRUNLOG << "Hello World in cerr!";

    // регистрируем своего исполнителя.
    vlog::VLogger::add_executer( my_log_executer );
    VWARNING("After register own executer.");


    // Удалим текущие логгеры и будем писать только в файлы.
    vlog::VLogger::clear_executers();

    // Будем вести историю максимум в двух файлах, размеры одного -- 2.5 кб.
    vlog::VOneFileLog one_flog( vcat(argv[0], ".log"), 2500, 2 );
    one_flog.register_self(); // Он сам знает где и как регистрироваться.

    // UPD: Папка будет создана автоматически.
    // Будем вести историю максимум в двух файлах, размеры одного -- 1 кб.
    vlog::VGroupFileLog group_flog( "./logs-logs", 1000, 2 );
    group_flog.register_self();

    for (int i = 0; i <= 10; ++i)
    {
        auto msg = vcat("Testing records in file: ", i)
                       (", timestamp ms = ", VTimePoint::now().milliseconds()).str();
        VTRACE   (msg);
        VDEBUG   (msg);
        VRUNLOG  (msg);
        VWARNING (msg);
        VFATAL   (msg);
    }
    // См. логи около бинарника программы.

    return 0;
}
//=======================================================================================
