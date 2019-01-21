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


#ifndef VRANDOM_H
#define VRANDOM_H

#include <random>


//=======================================================================================
class VRandom_mt19937
{
public:
    #if __LP64__
      using mt19937_type = std::mt19937_64;
    #else
      using mt19937_type = std::mt19937;
    #endif
    using result_type = mt19937_type::result_type;

    VRandom_mt19937();

    result_type operator()();

    uint32_t u32();
    uint64_t u64();

    template<typename T>
    T any();

private:
    mt19937_type _mt;
};
//=======================================================================================
template<typename T>
T VRandom_mt19937::any()
{
    static_assert( sizeof(T) <= sizeof(result_type), "sizeof(T) > sizeof(result_type)" );
    return static_cast<T>( (*this)() );
}
//=======================================================================================



#endif // VRANDOM_H
