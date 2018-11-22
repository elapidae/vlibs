#ifndef VAPPLICATION_H
#define VAPPLICATION_H

#include <string>
#include <vector>
#include <memory>

//#include "vpoll/vpoll_queue_iface.h"

//=======================================================================================
/*  24-09-2018      by Elapidae
 *
 *  VApplication -- аггрегатор:
 *      - аргументов командной строки;
 *      - pid приложения (его сохранения, удержания);
 *      - управление задачами главного потока (пока на распутье, с gio VS epoll);
 *
*/
//=======================================================================================


//=======================================================================================
inline namespace tr1
{
    //===================================================================================
    class VApplication final //: public VPoll_Queue_Iface
    {
    public:
        //-------------------------------------------------------------------------------
        using cstr = const std::string&;

        //-------------------------------------------------------------------------------
        VApplication();
        VApplication( int argc, char const * const * const argv );
        //~VApplication() override;

        //-------------------------------------------------------------------------------
        class Args;
        Args& args();
        const Args& args() const;

        //  Дублирует методы Args
        std::string app_name() const;       //  the_exec_file
        std::string app_path() const;       //  path/to/exec/
        std::string full_app_name() const;  //  path/to/exec/the_exec_file

        //-------------------------------------------------------------------------------
        class Pid;
        Pid& pid();

        //-------------------------------------------------------------------------------
        void poll();
        void stop();

    private:
        class _pimpl; std::unique_ptr<_pimpl> p;

        //void do_invoke( InvokeFunc&& func ) override;
    }; // VApplication
    //===================================================================================
    class VApplication::Args
    {
    public:
        Args( int argc, char const * const * const argv );

        std::string app_name() const;       //  the_exec_file
        std::string app_path() const;       //  path/to/exec/
        std::string full_app_name() const;  //  path/to/exec/the_exec_file

        bool has_flag           ( cstr name ) const;    // Имеются ввиду указано/нет.
        std::string std_value   ( cstr name ) const;    // по отсутствии бросается.
        std::string std_value_or( cstr name, cstr default_val ) const;

        bool take_has_flag           ( cstr name );
        std::string take_std_value   ( cstr name );
        std::string take_std_value_or( cstr name, cstr default_val );

        //  Что осталось.
        const std::vector<std::string>& remain() const;

        //  Бросается исключением, когда что-либо осталось. Удобно сообщать о неправильно
        //  написанных и нераспознанных аргументах.
        void throw_verror_if_not_empty();

    private:
        std::string _full_app_name;
        std::vector<std::string> _args;
    };
    //===================================================================================
    class VApplication::Pid final
    {
    public:
        static pid_t pid();                     //  Очевидно, пид процесса.

        Pid();
        ~Pid();

        void store( cstr path, cstr fname );    //  Весь класс из одного метода.

    private:
        class _pimpl; std::unique_ptr<_pimpl> p;
        Pid( const Pid& ) = delete; Pid& operator =( const Pid& ) = delete;
    };
    //===================================================================================

} // namespace tr1
//=======================================================================================


#endif // VAPPLICATION_H
