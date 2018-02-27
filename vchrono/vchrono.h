#ifndef VCHRONO_H
#define VCHRONO_H

#include <chrono>

class vchrono
{
public:
    using system_timestamp_t = decltype( std::chrono::system_clock::now() );
    using steady_timestamp_t = decltype( std::chrono::steady_clock::now() );

    static system_timestamp_t system_now() { return std::chrono::system_clock::now(); }
    static steady_timestamp_t steady_now() { return std::chrono::steady_clock::now(); }

    // По умолчанию, используется системное время.
    using timestamp_t = system_timestamp_t;
    static timestamp_t now()               { return system_now(); }
};

#endif // VCHRONO_H
