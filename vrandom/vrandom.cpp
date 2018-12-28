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
