#ifndef VCHRONO_H
#define VCHRONO_H

#include <chrono>



namespace vchrono
{
    using system_timestamp_t = decltype( std::chrono::system_clock::now() );
    using steady_timestamp_t = decltype( std::chrono::steady_clock::now() );
    using high_resolution_timestamp_t
                                 = decltype( std::chrono::high_resolution_clock::now() );


    system_timestamp_t system_now() { return std::chrono::system_clock::now(); }
    steady_timestamp_t steady_now() { return std::chrono::steady_clock::now(); }

    // По умолчанию, используется системное время.
    //using timestamp_t = system_timestamp_t;
    //timestamp_t now()               { return system_now(); }

    class TimeStamp final
    {
    public:
        static TimeStamp now();


        explicit TimeStamp();
        explicit TimeStamp( const system_timestamp_t &ts );


        system_timestamp_t as_timestamp_t() const;

        std::chrono::nanoseconds  nanosec()  const;
        std::chrono::microseconds microsec() const;
        std::chrono::milliseconds millisec() const;
        std::chrono::seconds      sec()      const;


        bool operator == ( const TimeStamp &rhs ) const;
        bool operator != ( const TimeStamp &rhs ) const;

        bool operator <  ( const TimeStamp &rhs ) const;
        bool operator >  ( const TimeStamp &rhs ) const;
        bool operator <= ( const TimeStamp &rhs ) const;
        bool operator >= ( const TimeStamp &rhs ) const;

        const TimeStamp & operator -= ( const TimeStamp &rhs );

    private:
        system_timestamp_t _ts;
    }; // TimeStamp

} // vchrono



#endif // VCHRONO_H
