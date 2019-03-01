#ifndef VTHREAD_APP_IMPL_H
#define VTHREAD_APP_IMPL_H

#include <memory>



//=======================================================================================
class VThread_App_Impl
{
public:
    enum _gen_thread { gen_thread };
    VThread_App_Impl();
    VThread_App_Impl( _gen_thread );

    void exec();

private:
    class Pimpl; std::unique_ptr<Pimpl> p;
};
//=======================================================================================




#endif // VTHREAD_APP_IMPL_H
