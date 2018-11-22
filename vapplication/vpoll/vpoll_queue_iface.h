#ifndef VPOLL_QUEUE_IFACE_H
#define VPOLL_QUEUE_IFACE_H

#include <functional>

//=======================================================================================
class VPoll_Queue_Iface
{
public:
    using InvokeFunc = std::function<void()>;
    virtual ~VPoll_Queue_Iface() = default;

    template< typename Fn, typename ... Args >
    void invoke( Fn fn, const Args& ... args );

    template< typename Cls, typename RetType, typename ... Args >
    void invoke( Cls *cls, RetType(Cls::*func)(Args...), const Args& ... args );

protected:
    //-----------------------------------------------------------------------------------
    virtual void do_invoke( InvokeFunc&& func ) = 0;
    //-----------------------------------------------------------------------------------
}; // VPoll_Queue_Iface
//=======================================================================================


//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template< typename Fn, typename ... Args >
void VPoll_Queue_Iface::invoke( Fn fn, const Args& ... args )
{
    InvokeFunc f = [=](){ fn(args...); };
    do_invoke( std::move(f) );
}
//=======================================================================================
template< typename Cls, typename RetType, typename ... Args >
void VPoll_Queue_Iface::invoke( Cls *cls, RetType(Cls::*func)(Args...),
                                const Args& ... args )
{
    InvokeFunc f = [=](){ (cls->*func)(args...); };
    do_invoke( std::move(f) );
}
//=======================================================================================


#endif // VPOLL_QUEUE_IFACE_H
