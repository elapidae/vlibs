#ifndef VBUFFERFORWARDREADER_H
#define VBUFFERFORWARDREADER_H

#include "vstring.h"



//=======================================================================================
/*  2018-02-01
 *
 * VBufferForwardReader -- класс для чтения константного буффера вперед, интерпретируя
 *  [бинарный] входной поток.
 *
 * NB! Строка или буффер не должен изменяться, иначе -- ваши проблемы.
 */
//=======================================================================================




//=======================================================================================
//      VBufferForwardReader
//=======================================================================================
class VBufferForwardReader
{
public:

    //-----------------------------------------------------------------------------------

    explicit VBufferForwardReader( const std::string &buf );
    VBufferForwardReader( const char *buf, size_t size );

    int  remained() const;
    bool finished() const;

    //-----------------------------------------------------------------------------------

    template<typename T> T show_LE()  const;
    template<typename T> T show_BE()  const;
    std::string show_str( size_t sz ) const;

    //-----------------------------------------------------------------------------------

    template<typename T> T take_LE();
    template<typename T> T take_BE();
    std::string take_str( size_t sz );

    // Байтовая строка -- строка длиной не более 255 символов, начинается с размера.
    // [1 byte len] [len byte body]
    std::string take_byte_string();

    //-----------------------------------------------------------------------------------

    char     show_ch()                      { return show_LE<char>();       }
    int8_t   show_i8()                      { return show_LE<int8_t>();     }
    uint8_t  show_u8()                      { return show_LE<uint8_t>();    }

    int16_t  show_i16_LE()                  { return show_LE<int16_t>();    }
    int16_t  show_i16_BE()                  { return show_BE<int16_t>();    }
    uint16_t show_u16_LE()                  { return show_LE<uint16_t>();   }
    uint16_t show_u16_BE()                  { return show_BE<uint16_t>();   }

    int32_t  show_i32_LE()                  { return show_LE<int32_t>();    }
    int32_t  show_i32_BE()                  { return show_BE<int32_t>();    }
    uint32_t show_u32_LE()                  { return show_LE<uint32_t>();   }
    uint32_t show_u32_BE()                  { return show_BE<uint32_t>();   }

    int64_t  show_i64_LE()                  { return show_LE<int64_t>();    }
    int64_t  show_i64_BE()                  { return show_BE<int64_t>();    }
    uint64_t show_u64_LE()                  { return show_LE<uint64_t>();   }
    uint64_t show_u64_BE()                  { return show_BE<uint64_t>();   }


    float    show_float_LE()                { return show_LE<float>();      }
    float    show_float_BE()                { return show_BE<float>();      }

    double   show_double_LE()               { return show_LE<double>();     }
    double   show_double_BE()               { return show_BE<double>();     }

    //-----------------------------------------------------------------------------------

    char     take_ch()                      { return take_LE<char>();       }
    int8_t   take_i8()                      { return take_LE<int8_t>();     }
    uint8_t  take_u8()                      { return take_LE<uint8_t>();    }

    int16_t  take_i16_LE()                  { return take_LE<int16_t>();    }
    int16_t  take_i16_BE()                  { return take_BE<int16_t>();    }
    uint16_t take_u16_LE()                  { return take_LE<uint16_t>();   }
    uint16_t take_u16_BE()                  { return take_BE<uint16_t>();   }

    int32_t  take_i32_LE()                  { return take_LE<int32_t>();    }
    int32_t  take_i32_BE()                  { return take_BE<int32_t>();    }
    uint32_t take_u32_LE()                  { return take_LE<uint32_t>();   }
    uint32_t take_u32_BE()                  { return take_BE<uint32_t>();   }

    int64_t  take_i64_LE()                  { return take_LE<int64_t>();    }
    int64_t  take_i64_BE()                  { return take_BE<int64_t>();    }
    uint64_t take_u64_LE()                  { return take_LE<uint64_t>();   }
    uint64_t take_u64_BE()                  { return take_BE<uint64_t>();   }


    float    take_float_LE()                { return take_LE<float>();      }
    float    take_float_BE()                { return take_BE<float>();      }

    double   take_double_LE()               { return take_LE<double>();     }
    double   take_double_BE()               { return take_BE<double>();     }

    //-----------------------------------------------------------------------------------

private:
    const char *_buffer;
    size_t      _remained;
};
//=======================================================================================
//      VBufferForwardReader
//=======================================================================================




//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template<typename T>
T VBufferForwardReader::show_LE() const
{
    if ( _remained < sizeof(T) )
        throw std::out_of_range( "VBufferForwardReader::show_LE<T>(): not enouth data" );

    auto res = * static_cast<const T*>( static_cast<const void*>(_buffer) );

    #if BYTE_ORDER == LITTLE_ENDIAN
    #elif BYTE_ORDER == BIG_ENDIAN
    res = VString::reverse_T( res );
    #else
    #error "Unknown byte order"
    #endif

    return res;
}
//=======================================================================================
template<typename T>
T VBufferForwardReader::show_BE() const
{
    if ( _remained < sizeof(T) )
        throw std::out_of_range( "VBufferForwardReader::take_BE<T>(): not enouth data" );

    auto res = * static_cast<const T*>( static_cast<const void*>(_buffer) );

    #if BYTE_ORDER == LITTLE_ENDIAN
    res = VString::reverse_T( res );
    #elif BYTE_ORDER == BIG_ENDIAN
    #else
    #error "Unknown byte order"
    #endif

    return res;
}
//=======================================================================================
template<typename T>
T VBufferForwardReader::take_LE()
{
    auto res = show_LE<T>();

    _remained -= sizeof(T);
    _buffer   += sizeof(T);

    return res;
}
//=======================================================================================
template<typename T>
T VBufferForwardReader::take_BE()
{
    auto res = show_BE<T>();

    _remained -= sizeof(T);
    _buffer   += sizeof(T);

    return res;
}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================


#endif // VBUFFERFORWARDREADER_H
