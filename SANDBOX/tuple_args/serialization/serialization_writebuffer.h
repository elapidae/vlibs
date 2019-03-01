#ifndef SERIALIZATION_WRITEBUFFER_H
#define SERIALIZATION_WRITEBUFFER_H


#include "vstring.h"
#include "serialization/serialization_type_traits.h"


//=======================================================================================
namespace serialization
{
    //===================================================================================
    class WriteBuffer
    {
    public:
        void add_to_reserve( size_t reserve );

        template<typename T> typename std::enable_if< is_arithmetic<T>(),
        void>::type write( const T& val ) { _buf.append_LE( val ); }

        void write( const std::string& val );
        void write( bool val );

        void write_size( size_t sz );

        // Добавляет в конец как есть, без размера.
        void write_raw( const std::string& val );

        int size() const;
        const VString& result() const;

    private:
        size_t _reserve = 0;
        VString _buf;
    };
    //===================================================================================
} // namespace serialization
//=======================================================================================

#endif // SERIALIZATION_WRITEBUFFER_H
