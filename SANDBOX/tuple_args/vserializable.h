#ifndef VSERIALIZABLE_H
#define VSERIALIZABLE_H

#include <string>
#include <tuple>


//=======================================================================================
template<typename T>
struct VSerializable;
//=======================================================================================
//  Используется для вывода типа
template<typename Lambda,typename SType>
using result_of_lambda = typename std::result_of<Lambda(SType)>::type;
//=======================================================================================
//  Специальный тип, с заковыркой... Он сериализуется в зависимости от значения в
//  последовательность от одного до пяти байт.
//  Сделано только для 32-х битных беззнаковых значений, чтобы не злоупотребляли...
struct VSerialize_Size final
{
    VSerialize_Size( uint32_t sz = 0 ) : _size(sz) {}

    using value_type = uint32_t;

    operator uint32_t() const { return _size; }
    operator uint32_t&()      { return _size; }

    uint32_t value() const    { return _size; }

private:
    uint32_t _size;
};
//=======================================================================================


//=======================================================================================
struct VSerialize_Example
{
    int32_t  i;
    uint32_t u;
    char     c;
};
//---------------------------------------------------------------------------------------
static constexpr auto _tupline_VSerialize_Example = []( const VSerialize_Example &val )
{
    return std::make_tuple( val.i, val.u, val.c );
};
//---------------------------------------------------------------------------------------
template<>
struct VSerializable<VSerialize_Example>
{
    //  Этот метод можно не писать.
    static constexpr const char* label()
    { return "ver 1.0, 09-10-2018, by Elapidae"; }

    std::result_of<decltype(_tupline_VSerialize_Example)(VSerialize_Example)>::type
    operator()( const VSerialize_Example& val ) const
    { return _tupline_VSerialize_Example(val); }
};
//=======================================================================================



#endif // VSERIALIZABLE_H
