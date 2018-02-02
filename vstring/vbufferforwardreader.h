#ifndef VBUFFERFORWARDREADER_H
#define VBUFFERFORWARDREADER_H

#include "vstringref.h"



//=======================================================================================
/*  2018-02-01
 *
 * VBufferForwardReader -- класс для чтения константного буффера вперед, интерпретируя
 *  входной поток.
 *
 * NB! Строка или буффер не должен изменяться, иначе -- ваши проблемы.
 */
//=======================================================================================


//=======================================================================================
class VBufferForwardReader
{
public:
    explicit VBufferForwardReader( const std::string &buf );
    VBufferForwardReader( const char *buf, size_t size );

    std::string take_str( size_t sz );

    template<typename T> T take_LE();
    template<typename T> T take_BE();

    int remained() const;

private:
    const char *_buffer;
    int _remained;
};
//=======================================================================================




//=======================================================================================
template<typename T>
T VBufferForwardReader::take_LE()
{
    if ( _remained < sizeof(T) )
        throw std::out_of_range( "VBufferForwardReader::take_LE<T>(): not enouth data" );

    auto res = static_cast<const T*>( static_cast<const void*>(_buffer) );

    #if BYTE_ORDER == BIG_ENDIAN
    res = VStringRef::reverse_T( res );
    #endif

    _remained -= sizeof(T);
    _buffer   += sizeof(T);

    return res;
}
//=======================================================================================
template<typename T>
T VBufferForwardReader::take_BE()
{
    if ( _remained < sizeof(T) )
        throw std::out_of_range( "VBufferForwardReader::take_BE<T>(): not enouth data" );

    auto res = static_cast<const T*>( static_cast<const void*>(_buffer) );

    #if BYTE_ORDER == LITTLE_ENDIAN
    res = VStringRef::reverse_T( res );
    #endif

    _remained -= sizeof(T);
    _buffer   += sizeof(T);

    return res;
}
//=======================================================================================


#endif // VBUFFERFORWARDREADER_H
