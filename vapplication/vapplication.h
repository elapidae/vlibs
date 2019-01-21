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


#ifndef VAPPLICATION_H
#define VAPPLICATION_H

#include <string>
#include <vector>
#include <memory>

#include "vinvoke/vinvoke_iface.h"

//=======================================================================================
/*  24-09-2018      by Elapidae
 *
 *  VApplication -- аггрегатор:
 *      - аргументов командной строки;
 *      - pid приложения (его сохранения, удержания);
 *
 *      - UPD 23-11-2018 -- добавлен поллинг главного потока. Методы poll() и stop()
 *          позволяют слушать сокеты и порты, которые используют механизм VPoll.
 *      - Добавлен интерфейс VInvoke, позволяющий пробрасывать задачи в очередь главного
 *          потока.
*/
//=======================================================================================


//=======================================================================================
inline namespace tr1
{
    //===================================================================================
    //      VApplication
    //===================================================================================
    class VApplication final : public VInvoke_Iface<VApplication>
    {
    public:
        //-------------------------------------------------------------------------------
        using cstr = const std::string&;

        //-------------------------------------------------------------------------------
        static VApplication* app(); // Экземпляр, если был создан | nullptr.
        VApplication();
        VApplication( int argc, char const * const * const argv );
        ~VApplication();

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
        // Будут вызваны из деструктора ~VApplication().
        void add_post_routine( const InvokeFunc& func );

        void do_invoke( InvokeFunc&& func );

    private:
        class _pimpl; std::unique_ptr<_pimpl> p;
    }; // VApplication

    //===================================================================================
    //      Args
    //===================================================================================
    //  Методы take_* могут вызывать странные эффекты чтения аргументов:
    //  Пусть поступили аргументы: arg1 val1 flag arg2 val2
    //  Если запросить:
    //      take_std_value("arg1"); // =val1,  remain=flag arg2 val2
    //      take_std_value("arg2"); // =val2,  remain=flag
    //      take_has_flag("flag");  // =true,  remain is empty
    //  Все будет хорошо, а вот если устроить что-нибудь такое:
    //      take_std_value("val1"); // =flag,  remain=arg1 arg2 val2
    //      take_std_value("arg1"); // =arg2,  remain=val2
    //      take_has_flag("flag");  // =false, remain=val2
    //  То вырезанные первыми значения переместят аргументы с конца и выставят новый
    //  порядок.
    //  TODO: Вопрос: что делать и как жить дальше?
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
    //      Pid
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
