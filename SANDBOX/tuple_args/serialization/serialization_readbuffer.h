#ifndef SERIALIZATION_READBUFFER_H
#define SERIALIZATION_READBUFFER_H

#include "vstring.h"
#include "serialization/serialization_type_traits.h"


//=======================================================================================

namespace serialization
{
    //===================================================================================
    class ReadBuffer
    {
    public:
        ReadBuffer( const VString& buf );
        bool finished() const;

        template <typename T> typename std::enable_if< is_string<T>(),
        std::string>::type read();

        template <typename T> typename std::enable_if< is_arithmetic<T>(),
        T>::type read();

        template <typename T> typename std::enable_if< is_bool<T>(),
        T>::type read();

        uint32_t read_size();

    private:
        VString _buf;
        VString::ForwardView _view;
    };

    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    template <typename T> typename std::enable_if< is_string<T>(),
    std::string>::type ReadBuffer::read()
    {
        auto sz = read_size();
        return _view.take_str( sz );
    }
    //===================================================================================
    template <typename T> typename std::enable_if< is_arithmetic<T>(),
    T>::type ReadBuffer::read()
    {
        return _view.take_LE<T>();
    }
    //===================================================================================
    template <typename T> typename std::enable_if< is_bool<T>(),
    T>::type ReadBuffer::read()
    {
        return _bool_from_byte( _view.take_u8() );
    }
    //===================================================================================
} // namespace serialization
//=======================================================================================


#endif // SERIALIZATION_READBUFFER_H
