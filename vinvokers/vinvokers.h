#ifndef VINVOKERS_H
#define VINVOKERS_H


//=======================================================================================
/*      Инвокеры -- вспомогательные классы отложенного вызова к-л сущностей.
 * Применяются в очередях потоков, но могут быть использованы и для других целей.
 *
 *      Количество аргументов ограниченно (на 02.08.2017) тремя, если что, можно
 * дописать. Универсального решения /произвольное количество аргументов/ автор не знает,
 * т.к. необходимо захватывать аргументы внутрь инвокера.
 *
 *
 *      Invoker[0,1,2,...] -- классы, принимающие в качестве первого аргумента сущность,
 * имеющую оператор (), т.е. способную быть вызванной синтаксисом вызова функции.
 * Второй и последующие аргументы должны соответствовать аргументам вызова сущности,
 * номер в названии инвокера соответствует количеству передаваемых при вызове аргументов.
 *
 *      Если сущность имеет возвращаемое значение, оно игнорируется.
 *
 *
 *      В инвокеры можно передавать функции, функторы, лямбды и прочие
 * подобные сущности Стандарта.
 *
 * Примеры:
 *  - указатели на функции:
 *          void foo0() {};
 *          Invoker0 inv(foo);
 *          inv.invoke();           // call foo0();
 *
 *          void foo1(int a1) {};
 *          Invoker1 inv(foo, 42);
 *          inv.invoke();           // call foo1(42);
 *
 *  - функторы:
 *          class Functor {
 *              void operator()(string s, int i)
 *              {}
 *          };
 *          Invoker2 inv( Functor(), "hello world!", 42 );
 *          inv.invoke();
 *
 *  - лямбды:
 *          Invoker1 inv( [](int i){ cout << i; }, 42 );
 *          inv.invoke();
 *
 *      NB! Как сама сущность, так и аргументы копируются внутрь инвокера.
 *          Инвокер не защитит от вызова уже невалидных сущностей, например,
 *          уже несуществующих объектов, захваченных в лямбде.
 *          В общем, думайте головой что и когда может быть вызвано и использовано.
 *
 *      UPD: Добавлены методы отложенного вызова методов классов ClassInvoker[0,1,2,3]
 *      Синтаксис вызова:
 *          class Cls
 *          {
 *              void foo(int) {}
 *          } cls;
 *          ClassInvoker1 cinv( &cls, &Cls::foo, 42 );
 *          cinv.invoke();
 *
 *          TODO:
 *          Пока библиотека в пре-альфа стадии, стоит переделать передачу аргументов
 * /передавать по константным ссылкам, сделать синонимы в синтаксисом переноса/, убрать
 * реализацию в cpp файл, причесать код и т.д.
 *
**/
//=======================================================================================


#include <type_traits>
#include <memory>


//=======================================================================================
//      INVOKERS
//=======================================================================================
namespace std
{
    template<typename T>
    class shared_ptr;
}
//=======================================================================================
class Invoker
{
public:
    using shared = std::shared_ptr<Invoker>;
    virtual void invoke() = 0;
};
//=======================================================================================
template<typename Tinv>
class Invoker0 : public Invoker
{
public:
    Invoker0(Tinv inv) : _inv(inv) {}
    virtual void invoke() override { _inv(); }

private:
    typename std::remove_reference<Tinv>::type _inv;
};
//=======================================================================================
template<typename Tinv, typename A0>
class Invoker1 : public Invoker
{
public:
    Invoker1(const Tinv &inv, const A0 &a0) : _inv(inv), _a0(a0) {}
    virtual void invoke() override { _inv(_a0); }
private:
    typename std::remove_reference<Tinv>::type _inv;
    typename std::remove_reference<A0>::type   _a0;
};
//=======================================================================================
template<typename Tinv, typename A0, typename A1>
class Invoker2 : public Invoker
{
public:
    Invoker2(Tinv inv, A0 a0, A1 a1) : _inv(inv), _a0(a0), _a1(a1) {}
    virtual void invoke() override { _inv(_a0, _a1); }
private:
    typename std::remove_reference<Tinv>::type _inv;
    typename std::remove_reference<A0>::type   _a0;
    typename std::remove_reference<A1>::type   _a1;
};
//=======================================================================================
template<typename Tinv, typename A0, typename A1, typename A2>
class Invoker3 : public Invoker
{
public:
    Invoker3(Tinv inv, A0 a0, A1 a1, A2 a2) : _inv(inv), _a0(a0), _a1(a1), _a2(a2) {}
    virtual void invoke() override { _inv(_a0, _a1, _a2); }
private:
    typename std::remove_reference<Tinv>::type _inv;
    typename std::remove_reference<A0>::type   _a0;
    typename std::remove_reference<A1>::type   _a1;
    typename std::remove_reference<A2>::type   _a2;
};
//=======================================================================================
//      INVOKERS
//=======================================================================================



//=======================================================================================
//      CLASS INVOKERS
//=======================================================================================
template<typename Cls, typename Fn>
class ClassInvoker0 : public Invoker
{
public:
    ClassInvoker0(Cls *cls, Fn fn) : _cls(cls), _fn(fn) {}

    static shared create(Cls *cls,Fn fn)
    { return std::make_shared<ClassInvoker0<Cls,Fn>>(cls,fn); }

    virtual void invoke() override { (_cls->*_fn)(); }

private:
    Cls *_cls;
    Fn  _fn;
};
//=======================================================================================
template<typename Cls, typename Fn, typename A0>
class ClassInvoker1 : public Invoker
{
public:
    ClassInvoker1(Cls *cls, Fn fn, const A0& a0)
        : _cls(cls), _fn(fn), _a0(a0) {}

    virtual void invoke() override { (_cls->*_fn)(_a0); }

private:
    Cls *_cls;
    Fn  _fn;
    typename std::remove_reference<A0>::type _a0;
};
//=======================================================================================
template<typename Cls, typename Fn, typename A0, typename A1>
class ClassInvoker2 : public Invoker
{
public:
    ClassInvoker2(Cls *cls, Fn fn, const A0& a0, const A1& a1)
        : _cls(cls), _fn(fn), _a0(a0), _a1(a1) {}

    virtual void invoke() override { (_cls->*_fn)(_a0, _a1); }

private:
    Cls *_cls;
    Fn  _fn;
    typename std::remove_reference<A0>::type _a0;
    typename std::remove_reference<A1>::type _a1;
};
//=======================================================================================
template<typename Cls, typename Fn, typename A0, typename A1, typename A2>
class ClassInvoker3 : public Invoker
{
public:
    ClassInvoker3(Cls *cls, Fn fn, const A0& a0, const A1& a1, const A2& a2)
        : _cls(cls), _fn(fn), _a0(a0), _a1(a1), _a2(a2) {}

    virtual void invoke() override { (_cls->*_fn)(_a0, _a1, _a2); }

private:
    Cls *_cls;
    Fn  _fn;
    typename std::remove_reference<A0>::type _a0;
    typename std::remove_reference<A1>::type _a1;
    typename std::remove_reference<A1>::type _a2;
};
//=======================================================================================
//      CLASS INVOKERS
//=======================================================================================


//=======================================================================================
//      CLASS INVOKERS PROXY
//=======================================================================================
template<typename A1>
class _ArgInvokerProxy1
{
public:
    using shared = typename std::shared_ptr<_ArgInvokerProxy1<A1>>;

    virtual Invoker::shared make_invoker(const A1 &a1) = 0;
};
//=======================================================================================
template<typename Cls, typename Fn, typename A1>
class ClassInvokerProxy1 : public _ArgInvokerProxy1<A1>
{
public:
    static std::shared_ptr<_ArgInvokerProxy1<A1>> create(Cls *cls, Fn fn)
    { return std::make_shared<ClassInvokerProxy1<Cls,Fn,A1>>(cls,fn); }

    ClassInvokerProxy1(Cls *cls, Fn fn) : _cls(cls), _fn(fn) {}

    Invoker::shared make_invoker(const A1 &a1) override
    { return std::make_shared<ClassInvoker1<Cls,Fn,A1>>(_cls,_fn,a1); }

private:
    Cls *_cls;
    Fn  _fn;
};
//=======================================================================================
//=======================================================================================
template<typename A1, typename A2>
class _ArgInvokerProxy2
{
public:
    using shared = typename std::shared_ptr<_ArgInvokerProxy2<A1,A2>>;

    virtual Invoker::shared make_invoker(const A1& a1, const A2& a2) = 0;
};
//=======================================================================================
template<typename Cls, typename Fn, typename A1, typename A2>
class ClassInvokerProxy2 : public _ArgInvokerProxy2<A1,A2>
{
public:
    static std::shared_ptr<_ArgInvokerProxy2<A1,A2>> create(Cls *cls, Fn fn)
    { return std::make_shared<ClassInvokerProxy2<Cls,Fn,A1,A2>>(cls,fn); }

    ClassInvokerProxy2(Cls *cls, Fn fn) : _cls(cls), _fn(fn) {}

    Invoker::shared make_invoker(const A1& a1, const A2& a2) override
    { return std::make_shared<ClassInvoker2<Cls,Fn,A1,A2>>(_cls,_fn,a1,a2); }

private:
    Cls *_cls;
    Fn  _fn;
};
//=======================================================================================
//=======================================================================================
template<typename A1, typename A2, typename A3>
class _ArgInvokerProxy3
{
public:
    using shared = typename std::shared_ptr<_ArgInvokerProxy3<A1,A2,A3>>;

    virtual Invoker::shared make_invoker(const A1& a1, const A2& a2, const A3& a3) = 0;
};
//=======================================================================================
template<typename Cls, typename Fn, typename A1, typename A2, typename A3>
class ClassInvokerProxy3 : public _ArgInvokerProxy3<A1,A2,A3>
{
public:
    static std::shared_ptr<_ArgInvokerProxy3<A1,A2,A3>> create(Cls *cls, Fn fn)
    { return std::make_shared<ClassInvokerProxy3<Cls,Fn,A1,A2,A3>>(cls,fn); }

    ClassInvokerProxy3(Cls *cls, Fn fn) : _cls(cls), _fn(fn) {}

    Invoker::shared make_invoker(const A1& a1, const A2& a2, const A3& a3) override
    { return std::make_shared<ClassInvoker3<Cls,Fn,A1,A2,A3>>(_cls,_fn,a1,a2,a3); }

private:
    Cls *_cls;
    Fn  _fn;
};
//=======================================================================================
//      CLASS INVOKERS PROXY
//=======================================================================================




#endif // VINVOKERS_H
