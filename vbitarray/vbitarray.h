#ifndef VBITARRAY_H
#define VBITARRAY_H

#include <stdint.h>
#include <vector>
#include <assert.h>
#include <string>

class VBitArray
{
public:
    VBitArray();

    template<typename It>
    VBitArray( It b, const It &e )
    {
        static_assert( sizeof(*b) == 1, "not a byte format." );

        while(b != e)
        {
            uint8_t ch = *b++;
            for (int i = 8; i > 0; --i)
            {
//                _bits.push_back( ch & 0x80 );
//                ch <<= 1;
                _bits.push_back( ch & 0x01 );
                ch >>= 1;
            }
        }
    }

    template<typename Container>
    VBitArray( const Container &c )
        : VBitArray( c.begin(), c.end() )
    {}

    VBitArray( const char *ch )
        : VBitArray( std::string(ch) )
    {}

    template<typename Res>
    Res pop_front(int count)
    {
        assert(int(_bits.size()) >= count && count > 0);

        Res res = 0;

        auto it = _bits.begin();

        while (count--)
        {
            res <<= 1;
            res |= *it++ ? 1 : 0;
        }
        return res;
    }
    int pop_front(int count)
    {
        return pop_front<int>(count);
    }


private:
    std::vector<uint8_t> _bits;
};





#endif // VBITARRAY_H
