#ifndef VSYSSIGNAL_H
#define VSYSSIGNAL_H

#include <functional>
#include <vector>

//=======================================================================================
/*  01-08-2018          by Elapidae
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
