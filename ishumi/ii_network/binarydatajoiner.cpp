#include "binarydatajoiner.h"

using namespace ii;
using namespace std;
using namespace std::chrono;



//=======================================================================================
BinaryDataJoiner::BinaryDataJoiner(int fragments_count)
    : _fragments(fragments_count)
{
    if (fragments_count <= 1)
        throw logic_error("(fragments_count <= 1)");

    _count.reserve( fragments_count );

    for ( int i = fragments_count; i > 0; --i )
    {
        _waiting_frags.insert( i );
    }
}
//=======================================================================================
int BinaryDataJoiner::push( int fragment, const VByteArray &data )
{
    _last_usage = steady_clock::now();

    if ( fragment > _fragments || fragment <= 0 )
        return _fragments + 1;

    auto res = _count[fragment]++;

    if (res == 0)
    {
        _data[fragment] = data;
        _waiting_frags.erase( fragment );
    }

    return res;
}
//=======================================================================================
int BinaryDataJoiner::remained() const
{
    return _waiting_frags.size();
}
//=======================================================================================
bool BinaryDataJoiner::is_ready() const
{
    return remained() == 0;
}
//=======================================================================================
VByteArray BinaryDataJoiner::join() const
{
    assert( is_ready() );

    VByteArray res;

    for ( int i = 1; i <= fragments_count(); ++i )
        res.append( _data.at(i) );

    return res;
}
//=======================================================================================
steady_clock_t BinaryDataJoiner::last_usage() const
{
    return _last_usage;
}
//=======================================================================================
int BinaryDataJoiner::fragments_count() const
{
    return _fragments;
}
//=======================================================================================

