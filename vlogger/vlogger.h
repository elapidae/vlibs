#ifndef VLOGGER_H
#define VLOGGER_H

#include <memory>
#include <string>
#include <functional>

#include <chrono>

#include "varg.h"


//=======================================================================================
// Пользование:
//      ...
//      trace  ( vlog("я далеко послала", "шесть с половиной байт.")                  );
//
//      deb    ( vlog("предназначено только для вывода в консоль, для разработки.")   );
//
//      runlog ( vlog("Навигатор был настроен корректно, начинаем прослушивание.")    );
//
//      warn   ( vlog("случилось что-то, не запланированное, но не страшное.")        );
//
//      fatal  ( vlog("экстерминатус -- скорее всего, программа не консистентна.")
//                   ("Сейчас бросается исключение, надо бы обсудить с коллективом.") );
//      ...
//      Можно писать через запятую, как удобнее.
//=======================================================================================



//=======================================================================================
//          LOGS CONTROL INTERFACE
//=======================================================================================
//  Передается по константной ссылке, НО cv-кастуется для того, чтобы выставить тип лога.
//  Если будет найден более лаконичный способ выставления типа, эти методы
//  надо будет пересмотреть.
class VLog;
void vdeb     ( const VLog &log );
void vtrace   ( const VLog &log );
void vrunlog  ( const VLog &log );
void vwarning ( const VLog &log );
void vfatal   ( const VLog &log );          // Бросает исключение VLogException(log);
void vassert  ( bool ok, const VLog &log ); // Бросает исключение если флаг !ok.

//=======================================================================================
//          LOGS CONTROL INTERFACE
//=======================================================================================



//=======================================================================================
//          VLog -- основной класс логгирования. Инстанцировать с помощью макроса vlog.
//=======================================================================================
#define vlog VLog( __FILE__, __FUNCTION__, __LINE__ )
//---------------------------------------------------------------------------------------
class VLog
{
public:
    // Вообще, этому здесь не место...
    using  SysTime = decltype(std::chrono::system_clock::now());
    static SysTime now() { return std::chrono::system_clock::now(); }
    // Вообще, этому здесь не место...
    using  SteadyTime = decltype( std::chrono::high_resolution_clock::now() );
    static SteadyTime steady_now() { return std::chrono::high_resolution_clock::now(); }

    template<class D> static int64_t nsec( const D &dur )
    { return std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count(); }

    template<class D> static int64_t usec( const D &dur )
    { return std::chrono::duration_cast<std::chrono::microseconds>(dur).count(); }

    template<class D> static int64_t msec( const D &dur )
    { return std::chrono::duration_cast<std::chrono::milliseconds>(dur).count(); }


    enum class Type
    {
        Deb,    // by default
        Trace,
        Runlog,
        Warn,
        Fatal
    };

    VLog( const char *file, const char *func, int line );

    template<typename ... Args>
    VLog &operator ()( const Args& ... args );


    std::string isoDateTime()   const;
    std::string sourcePoint()   const;
    std::string threadId()      const;

    std::string pretty_filename()   const;
    std::string func_name()         const;
    int line()                      const;

    std::string str() const;
    void print() const;

    Type type() const;
    void set_type( Type t );


    std::string to_json() const;
    static VLog from_json(const std::string &json, bool *ok = nullptr );

    // Здесь регистрируются функции, которые отвечают за обработку логов.
    struct OutControl
    {
        //  Определение своего логгировщика, функции v* будут вызывать его.
        //  По умолчанию, все просто выводится в консоль.
        using Handler = std::function< void (const VLog&) >;

        using Deleter = std::shared_ptr<int>;

        static void clear_all_loggers();

        // Сохраните возвращаемое значение, при его удалении произойдет удаление
        // логгера.
        static Deleter add_logger( const Handler &h );

        static Handler default_logger();
    };

private:    
    VLog(); // for straping from json.

    class Pimpl;
    std::shared_ptr<Pimpl> p;
    varg &_arg();
};
//=======================================================================================
//          VLog
//=======================================================================================



//=======================================================================================
//          VLOG EXCEPTION
//=======================================================================================
//  Наследуйтесь от этого исключения для того, чтобы удобно передавать точку
//  бросания исключения.
class VLogException : public std::exception
{
public:
    VLogException( const VLog &log );

    const VLog &log() const noexcept;

    const char* what() const noexcept override;

private:
    VLog _log;
    std::string _what;
};
//=======================================================================================
//          VLOG EXCEPTION
//=======================================================================================



//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================
template< typename ... Args >
VLog& VLog::operator ()( const Args& ... args )
{
    _arg()( args... );
    return *this;
}
//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================


#endif // VLOGGER_H
