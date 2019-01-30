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


#include "vrandom.h"


#include "vtimepoint.h"


//=======================================================================================
static std::random_device::result_type get_seed()
{
    static std::random_device rand_device;

    // Время используется на случай, если device псевдослучайное.
    auto nanos = VHighResolutionTimePoint::now().nanoseconds().count();

    return rand_device() ^ static_cast<std::random_device::result_type>(nanos);
}
//=======================================================================================




//=======================================================================================
VRandom_mt19937::VRandom_mt19937()
    : _mt( get_seed() )
{}
//=======================================================================================
VRandom_mt19937::mt19937_type::result_type VRandom_mt19937::operator()()
{
    return _mt();
}
//=======================================================================================
uint32_t VRandom_mt19937::u32()
{
    return static_cast<uint32_t>( (*this)() );
}
//=======================================================================================
uint64_t VRandom_mt19937::u64()
{
  #if __LP64__
    return (*this)();
  #else
    return ((*this)() << 32) | (*this)();
  #endif
}
//=======================================================================================
