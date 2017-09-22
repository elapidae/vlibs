#include "vthreadqueue.h"

#include <unordered_map>
#include <thread>
#include <assert.h>

using namespace std;


//=======================================================================================
int VThreadQueue::size() const
{
    return _queue.size();
}
//=======================================================================================
bool VThreadQueue::empty() const
{
    return _queue.empty();
}
//=======================================================================================
VThreadQueue::Func VThreadQueue::pop()
{
    return _queue.pop();
}
//=======================================================================================
