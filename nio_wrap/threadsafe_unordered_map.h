#ifndef THREADSAFE_UNORDERED_MAP_H
#define THREADSAFE_UNORDERED_MAP_H

#include <unordered_map>
#include <mutex>

template<class K, class T>
class ThreadSafe_Unordered_Map
{
public:

    void emplace( const K& key, const T& val )
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _map.emplace( key, val );
    }

    void erase( const K& key )
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _map.erase( key );
    }

    const T& at( const K& key )
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _map.at( key );
    }

private:
    std::unordered_map<K,T> _map;
    std::mutex _mutex;
};

#endif // THREADSAFE_UNORDERED_MAP_H
