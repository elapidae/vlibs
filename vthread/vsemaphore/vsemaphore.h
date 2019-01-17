#ifndef VSEMAPHORE_H
#define VSEMAPHORE_H
#include <memory>


//=======================================================================================
/**
 *      Стандартный семафор, реализованный на С++11 стандарте.
 *
 *      Подходит для стандартизированной передачи ресурсов между потоками.
**/
//=======================================================================================



//=======================================================================================
class VSemaphore
{
public:

    /// Передаем количество свободных сейчас ресурсов.
    explicit VSemaphore( int count = 0 );

    /// Вызываем, когда освобождаем путь к ресурсу.
    void notify();

    /// Вызываем, когда хотим ресурс захватить. Здесь будем ждать новых данных.
    void wait();

    /// Неблокирующий вызов с атомарностью.
    int count() const;

private:
    class Pimpl;
    std::shared_ptr<Pimpl> p;
};
//=======================================================================================



#endif // VSEMAPHORE_H
