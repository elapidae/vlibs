#ifndef RANGE_HPP
#define RANGE_HPP

#include "vlog_pretty.h"

#include <opencv2/opencv.hpp>

#include <ios>
#include <cstdint>

template< typename T >
class Range
{
public:
    Range() = delete;
    Range( T from, T to )
        :
            from( from ),
            to( to )
    {
        if ( from > to )
        {
            throw std::logic_error( "From value mast be less then To in Range constructor" );
        }
    }

    bool in_range( T val )
    {
        return val >= from && val < to;
    }

    friend std::ostream &operator<< ( std::ostream &output, const Range &R ) {
        output << "From : " << R.from << " To : " << R.to;
        return output;
    }
private:
    T from, to;
};


#endif // RANGE_HPP
