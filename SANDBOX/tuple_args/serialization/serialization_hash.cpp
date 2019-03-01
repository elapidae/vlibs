#include "serialization/serialization_hash.h"

#include "vcrc.h"
#include <set>
#include <mutex>

//=======================================================================================
serialization::hash_type serialization::_hash_func( const std::string &signature)
{
    return vcrc::poly_04C11DB7( signature );
}
//=======================================================================================
void serialization::_collisions_check( serialization::hash_type check )
{
    static std::set<serialization::hash_type> hashes;
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock( mutex );

    auto res = hashes.emplace( check );

    //  Если сюда попадем, значит надо с названиями разбираться, конфликт в кишках.
    if ( !res.second )
        throw std::logic_error( "Signature collision detected." );
}

//=======================================================================================

serialization::channel_hash_type
serialization::hash_of_channel( const std::string &channel )
{
    return _hash_func( channel );
}

//=======================================================================================
