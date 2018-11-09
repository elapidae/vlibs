#ifndef VPOSIX_ALLOCA_H
#define VPOSIX_ALLOCA_H

#include <stddef.h>
#include <type_traits>

namespace vposix
{
    //  Выделение памяти на стеке.
    class Alloca
    {
    public:
        static void* do_allocate( size_t sz );

        template<typename T>
        static T* allocate( size_t elem_sz );
    };


    template<typename T>
    T* Alloca::allocate( size_t elem_sz )
    {
        static_assert( std::is_trivial<T>::value, "" );
        return static_cast<T*>( do_allocate(elem_sz * sizeof(T)) );
    }


} // namespace vposix

#endif // VPOSIX_ALLOCA_H
