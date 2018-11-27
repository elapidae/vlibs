#ifndef VSTD_ATOMIC_MAP_H
#define VSTD_ATOMIC_MAP_H

#include <map>
#include <mutex>

//=======================================================================================
namespace vstd
{
    //===================================================================================
    template<typename K, typename V>
    class atomic_map
    {
    public:
        //using iterator = typename std::map<K,V>::iterator;
        using value_type = typename std::map<K,V>::value_type;

        template<typename... Args>
        bool emplace( Args&& ... args );

        void insert( std::initializer_list<value_type> list );

        bool empty() const;
        size_t size() const;

        V& at( const K& k );
        const V& at( const K& k ) const;

        bool contains( const K& key ) const;

        V& operator[]( const K& key );
        V& operator[]( K&& key );

        bool erase( const K& key );

    private:
        std::map<K,V> _map;
        mutable std::mutex _mutex;
    };
    //===================================================================================


    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    template<typename K, typename V>
    template<typename... Args>
    bool atomic_map<K, V>::emplace( Args&& ... args )
    {
        std::lock_guard<std::mutex> lock( _mutex );
        return _map.emplace( std::forward<Args>(args)... ).second;
    }
    //===================================================================================
    template<typename K, typename V>
    void atomic_map<K,V>::insert( std::initializer_list<value_type> list )
    {
        std::lock_guard<std::mutex> lock( _mutex );
        _map.insert( list );
    }
    //===================================================================================
    template<typename K, typename V>
    size_t atomic_map<K,V>::size() const
    {
        std::lock_guard<std::mutex> lock( _mutex );
        return _map.size();
    }
    //===================================================================================
    template<typename K, typename V>
    bool atomic_map<K,V>::empty() const
    {
        std::lock_guard<std::mutex> lock( _mutex );
        return _map.empty();
    }
    //===================================================================================
    template<typename K, typename V>
    V& atomic_map<K,V>::at( const K& k )
    {
        std::lock_guard<std::mutex> lock( _mutex );
        return _map.at( k );
    }
    //===================================================================================
    template<typename K, typename V>
    const V& atomic_map<K,V>::at( const K& k ) const
    {
        std::lock_guard<std::mutex> lock( _mutex );
        return _map.at( k );
    }
    //===================================================================================
    template<typename K, typename V>
    bool atomic_map<K,V>::contains( const K& key ) const
    {
        std::lock_guard<std::mutex> lock( _mutex );
        return _map.find(key) != _map.end();
    }
    //===================================================================================
    template<typename K, typename V>
    V& atomic_map<K,V>::operator[]( const K& key )
    {
        std::lock_guard<std::mutex> lock( _mutex );
        return _map[ key ];
    }
    //===================================================================================
    template<typename K, typename V>
    V& atomic_map<K,V>::operator[]( K&& key )
    {
        std::lock_guard<std::mutex> lock( _mutex );
        return _map[ std::move(key) ];
    }
    //===================================================================================
    template<typename K, typename V>
    bool atomic_map<K,V>::erase( const K& key )
    {
        std::lock_guard<std::mutex> lock( _mutex );
        auto res = _map.erase( key );
        return res == 1;
    }
    //===================================================================================
} // namespace vstd
//=======================================================================================


#endif // VSTD_ATOMIC_MAP_H
