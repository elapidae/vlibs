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


#ifndef OLD_COMPILER_VINVOKE_IFACE_H
#define OLD_COMPILER_VINVOKE_IFACE_H


//=======================================================================================
template<typename Derived>
class VInvoke_Iface
{
public:
    using InvokeFunc = std::function<void()>;

    //===================================================================================
    template< typename Fn >
    void invoke( Fn fn )
    {
        InvokeFunc f = fn;
        auto& d = static_cast<Derived&>(*this);
        d.do_invoke( std::move(f) );
    }
    //-----------------------------------------------------------------------------------
    template< typename Fn, typename A1 >
    void invoke( Fn fn, const A1& a1 )
    {
        InvokeFunc f = [fn,a1](){ fn(a1); };
        auto& d = static_cast<Derived&>(*this);
        d.do_invoke( std::move(f) );
    }
    //===================================================================================

    //===================================================================================
    template< typename Cls, typename RetType >
    void invoke( Cls *cls, RetType(Cls::*func)() )
    {
        InvokeFunc f = [cls,func](){ (cls->*func)(); };
        auto& d = static_cast<Derived&>(*this);
        d.do_invoke( std::move(f) );
    }
    //-----------------------------------------------------------------------------------
    template< typename Cls, typename RetType, typename A1 >
    void invoke( Cls *cls, RetType(Cls::*func)(), const A1& a1 )
    {
        InvokeFunc f = [cls,func,a1](){ (cls->*func)(a1); };
        auto& d = static_cast<Derived&>(*this);
        d.do_invoke( std::move(f) );
    }
    //===================================================================================

protected: ~VInvoke_Iface() = default;
}; // VInvoke_Iface
//=======================================================================================


#endif // OLD_COMPILER_VINVOKE_IFACE_H
