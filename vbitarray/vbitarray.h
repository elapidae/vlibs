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


//=======================================================================================
#ifndef VBITARRAY_H
#define VBITARRAY_H

#include <queue>
#include <stdexcept>
#include <string>


//=======================================================================================
/*  2018-01-29 revision.
 *
 *  VBitArray -- класс предназначен для парсинга коротких сообщений, в которых данные
 *  содержаться в битовых полях длиной не более 31 бита, находящихся в произвольных
 * позициях относительно байтовых границ.
 *
 *  UPD: 2018-03-06
 *  Инициализация битовых данных может быть произведена в конструкторе (из строки) или
 *  методом push(). Есть выбор с какой стороны читать биты, по умолчанию -- со старшего.
 *
 *  Методы извлечения данных /n -- кол-во бит/:
 *  pop_uint     ( n ) -- Просто извлекает нужное количество бит. В подавляющем
 *                        большинстве случаев вам понадобится именно этот метод.
 *
 *  pop_uint_neg ( n ) -- Извлекает беззнаковое число, но интерпретирует его
 *                        в дополнительном коде (что бы это ни значило).
 *
 *  pop_int      ( n ) -- Извлекает число СО ЗНАКОМ! Т.е. если установлен первый бит,
 *                        будет возвращено соответствующее отрицательное число.
 *
 *  pop_int_neg  ( n ) -- Извлекает число СО ЗНАКОМ, интерпретируется
 *                        в дополнительном коде.
*/
//=======================================================================================



//=======================================================================================
//      Bit Array
//=======================================================================================
class VBitArray
{
public:
    enum _MostSignificant { MostSignificant, LeastSignificant };

    explicit VBitArray();
    VBitArray( const std::string &data_to_bits,
               const _MostSignificant = MostSignificant );

    void push ( char val, const _MostSignificant most = MostSignificant );

    int32_t  pop_int      ( int cnt );
    int32_t  pop_int_neg  ( int cnt );
    uint32_t pop_uint     ( int cnt );
    uint32_t pop_uint_neg ( int cnt );

    bool empty()         const;
    int  remained_bits() const;
    bool front()         const;

private:
    template<typename T> T _pop_( int cnt, T initial );
    void _check_cnt( int cnt ) const;
    std::queue<uint8_t> _bools;
};
//=======================================================================================
//      Bit Array
//=======================================================================================




//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template<typename T>
T VBitArray::_pop_( int cnt, T res )
{
    _check_cnt( cnt );

    while ( cnt-- )
    {
        res <<= 1;
        if ( _bools.front() )
            res |= 1;
        _bools.pop();
    }
    return res;
}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================




#endif // VBITARRAY_H
//=======================================================================================
