#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <cstdint>

// Пространство имён для хранения функций профилирования кода
namespace profiler
{
    // Функция вывода разницы во времени и сообщения между текущим моментом и предыдущим (параметр)
    void print_delay( const int64_t t0, const char* message );
}

#endif // PROFILER_HPP
