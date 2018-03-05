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
*/
//=======================================================================================



//=======================================================================================
class VBitArray
{
public:
    enum _MostSignificant { MostSignificant, LeastSignificant };

    explicit VBitArray();
    VBitArray( const std::string &data_to_bits,
               const _MostSignificant = MostSignificant );

    void push( char val, const _MostSignificant most = MostSignificant );

    int32_t  pop_i     ( int cnt );
    int32_t  pop_i_dop ( int cnt );
    uint32_t pop_u     ( int cnt );
    uint32_t pop_u_dop ( int cnt );

    bool empty()         const;
    int  remained_bits() const;
    bool front()         const;

private:
    template<typename T> T _pop_( int cnt, T initial );
    void _check_cnt( int cnt ) const;
    std::queue<uint8_t> _bools;
};
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
