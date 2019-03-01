#ifndef ISHUMI_SERIALIZE_H
#define ISHUMI_SERIALIZE_H

#include <tuple>

template <class T> class TD;
template <int I> class TDI;

//=======================================================================================
namespace ishumi
{
    //===================================================================================
    //  1. Найти тип для сериализации.
    //  2. Сделать кортеж, позволяющий инициализировать этот тип. Сделано через лямбду,
    //     чтобы не выводить кортеж явно.
    //  3. Специализировать Serialize.
    //  3.1. Объявить статическую сущность с именем "id".
    //       То, что написано до первого пробела считается первичным именем,
    //       а вся строка вместе с порядком аргументов специализирует версионность.
    //  3.2. Объявить сущность с именем reduce, вызов которой даст кортеж для
    //       сериализации.
    //===================================================================================
    std::string extract_serialize_typename( const std::string &pretty_func );
    //===================================================================================
    struct Serialize_Example
    {
        int32_t  i;
        uint32_t u;
        char     c;
    };
    //===================================================================================
    //  Используется для вывода типа
    template<typename Lambda,typename SType>
    using result_of_arg1 = typename std::result_of<Lambda(SType)>::type;
    //===================================================================================
    //  Для "обучения" компилятора сериализации какого либо класса, надо
    //  создать специализацию этой структуры. См. пример ниже.
    template<typename T>
    struct Serialize;

    //===================================================================================
    constexpr auto _reduce_Serialize_Example = []( const Serialize_Example& val )
    {
        return std::make_tuple( val.i, val.u, val.c );
    };
    //===================================================================================
    template<>
    struct Serialize< Serialize_Example >
    {
        static constexpr const char* id()
        { return "Serialize_Example some description, 2018-10-04 by Elapidae"; }

        result_of_arg1<decltype(_reduce_Serialize_Example), Serialize_Example>
        reduce( const Serialize_Example& val )
        { return _reduce_Serialize_Example(val); }
    };
    //===================================================================================
} // namespace ishumi
//=======================================================================================

/*  1. Скопируйту и замените MyType на нужный тип.
 *  2. Исправьте список в лямбде.

Start of copy
<<<<<<<<<<<<<

//=======================================================================================
namespace ishumi
{
    //===================================================================================
    template<typename T> struct Serialize;
    //===================================================================================
    constexpr auto _reduce_MyType = []( const MyType& val )
    {
        return std::make_tuple( val.i, val.u, val.c );
    };
    //===================================================================================
    template<>
    struct Serialize< MyType >
    {
        static std::string id()
        {
            return extract_serialize_typename(__PRETTY_FUNCTION__) +
            "ver. 1.0 2018-10-06 by Elapidae";
        }

        result_of_arg1< decltype(_reduce_MyType), MyType >
        reduce( const MyType& val )
        { return _reduce_MyType(val); }
    };
    //===================================================================================
} // namespace ishumi
//=======================================================================================

>>>>>>>>>>>
End of copy */


#endif // ISHUMI_SERIALIZE_H
