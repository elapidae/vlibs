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


#ifndef VSYSSIGNAL_H
#define VSYSSIGNAL_H

#include <functional>
#include <vector>

//=======================================================================================
/*  UPD 27-11-2018
 *  Класс и подход устарел, следует пользоваться VApplication, который решает вопросы
 *  с сигналами автоматически. Он предлагает механизм остановки поллинга по сигналам.
 *  Предположительное время удаления класса из vlibs -- январь 2019г.
 *  =====================================================================================
 *
 *  01-08-2018          by Elapidae
 *
 *  VSysSignal -- регистратор обработчиков системных сигналов.
 *
 *  Это пробная версия. Сделана затем, чтобы делать обработчики сигналов не
 *  прибитыми к статической функции, а к нормальным функторам.
 *
 *  Регистрируются перехваты для сигналов SIGINT, SIGKILL, SIGTERM.
 *
 *  Пользую как-то так:
    VSysSignal::watch( [&](int s)
    {
        zcm_stereo.stop();
        zcm_lidar.stop();
        zcm_way.stop();

        vtrace << "Killed with signal" << s;
    });
*/
//=======================================================================================



//=======================================================================================
class VSysSignal
{
public:
    using Stopper0 = std::function<void()>;
    using Stopper1 = std::function<void(int)>;

    static void watch( Stopper0 s0 );
    static void watch( Stopper1 s1 );


private:
    static void _on_signals(int s);

    static std::vector<Stopper0> _s0;
    static std::vector<Stopper1> _s1;

    static bool _cb_registered;
    static void _register_cb();

    VSysSignal() = delete;
};
//=======================================================================================



#endif // VSYSSIGNAL_H
