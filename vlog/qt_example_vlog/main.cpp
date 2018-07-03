#include <iostream>

#include "vlog.h"
#include "vlog_pretty.h"

#include "vfilelog.h"
#include <thread>

using namespace std;

//=======================================================================================
//  Пример-затравка для пользовательской обработки логов.
void my_log_executer( const VLogEntry &entry )
{
    // Ниже приведены содержания из точки логгирования.
    // Их следует использовать для составления собственных сообщений.

    entry.timestamp();  // Метка времени создания вхождения.

    entry.level_char();  // Однобуквенный код типа сообщения { T, D, R, W, F }.
    entry.level_str();   // Трехбуквенный код типа сообщения { TRC, DBG, RUN, WRN, FLT }.
    entry.level();       // Тип enum class vlog::VLogEntry::Type.

    entry.filename();   // Имя файла без пути до него.
    entry.filepath();   // Полное имя файла (то, что дает __FILE__).
    entry.line();       // Номер строки в исходнике __LINE__
    entry.function();   // Что дает __FUNCTION__ (ИМХО __PRETTY_FUNCTION__ -- не pretty).

    entry.message();    // Составленное сообщение.

    entry.is_trace();   //  Для быстрой проверки к-л уровня.
    entry.is_debug();   //
    entry.is_runlog();  //
    entry.is_warning(); //
    entry.is_fatal();   //

    cout << "my_log_executer: " << entry.message() << endl;
}
//=======================================================================================

template<typename T>
class TD;

template<typename T>
void test(T)
{
    //TD<T> ttt;
}

template<typename T>
void f( T&& t )
{
    test( std::forward<T>(t) );
    TD< decltype(std::forward<T>(t)) > ddd;
}

#include <vector>

//=======================================================================================
int main( int, char **argv )
{
    // По умолчанию будет выводить в консоль.
    VRUNLOG << "Hello World!" << sizeof(VLogEntry) << sizeof(VTimePoint) << sizeof(string);

    double dd = 3.1415;
    float  ff = 2.718f;
    int    ii = 42;
    std::chrono::milliseconds ms(12345); // и такое выводим`c...

    VDEBUG; // пустая строка
    VDEBUG << "------- same syntax example.";
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
    VDEBUG.num(42, 5, '0');                     // то же самое, 00042
                                                // специально заточено под эту задачу.
    VDEBUG << "------------------------------";

    // Вывод без пробелов между аргументами:
    //auto prog_name = VString(argv[0]).split('/').back(); // удаляем путь к программе.
    string prog_name = argv[0];
    VTRACE.nospace()( "My program name is '", prog_name, "'." );

    // Теперь будем логгировать в cerr, удалим всех исполнителей и добавим исполнитель,
    // который будет писать в cerr (vlog::VLogger::_log_to_cerr).
    VLogger::clear_executers();
    VLogger::add_executer( VLogger::to_cerr );
    VRUNLOG << "Hello World in cerr!";

    // регистрируем своего исполнителя.
    VLogger::add_executer( my_log_executer );
    VWARNING("After register own executer.");


    // Удалим текущие логгеры и будем писать только в файлы.
    VLogger::clear_executers();

    // Будем вести историю максимум в двух файлах, размеры одного -- 2.5 кб.
    VCommonFileLog one_flog( vcat(argv[0], ".log"), 2500, 2 );
    one_flog.register_self(); // Он сам знает где и как регистрироваться.

    system("mkdir -p ./logs"); // если папки не будет -- это не проблема логгера.
    // Будем вести историю максимум в двух файлах, размеры одного -- 1 кб.
    VGroupFileLog group_flog( "./logs", 1000, 2 );
    group_flog.register_self();

    for (int i = 0; i < 10; ++i)
    {
        string msg = vcat("Testing records in file: ", i)
                         (", timestamp ms = ", VTimePoint::now().milliseconds());
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
