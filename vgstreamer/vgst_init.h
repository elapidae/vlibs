#ifndef VGST_INIT_H
#define VGST_INIT_H

#include <atomic>


class VGst_Init final
{
public:
    VGst_Init();

private:
    static std::atomic_int _count;
};

#endif // VGST_INIT_H
