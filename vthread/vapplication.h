#ifndef VAPPLICATION_H
#define VAPPLICATION_H

#include <thread>
#include <vthreadqueue/vthreadqueue.h>

class VApplication final
{
public:

    //static VThreadQueue* this_queue();
    static VApplication *app();

    VApplication();
    VApplication(int argc, char** argv);
    ~VApplication();

    int exec();
    void quit(int retcode);

    std::thread::id app_thread_id() const;

    int queue_size() const;

    // Имеется ввиду параметры типа "param_name param_value",
    // например так "--cfg-file /etc/navigation/navigation.cfg".
    // Если значение не будет найдено, вернет пустую строку.
    std::string series_param( const std::string &param_name ) const;

    bool has_param( const std::string &pname ) const;

private:
    class Pimpl;
    std::unique_ptr<Pimpl> p;
    //Pimpl *p;
};


#endif // VAPPLICATION_H
