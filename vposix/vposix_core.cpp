#include "vposix_core.h"

#include <vector>
#include <stdexcept>
#include <string.h>
#include <assert.h>

#include "vposix_alloca.h"

#include <unistd.h> // Здесь живет getpid(), правда логично?


using namespace vposix;

//=======================================================================================
pid_t Core::pid()
{
    return linux_call( ::getpid, "::getpid" );
}
//=======================================================================================


//=======================================================================================
Errno::Errno()
    : _err( errno )
{}
//=======================================================================================
int Errno::code() const
{
    return _err;
}
//=======================================================================================
//  http://man7.org/linux/man-pages/man3/strerror.3.html
std::string Errno::str() const
{
    //  TS версия.
    constexpr auto buf_size = 1024;
    auto buf = Alloca::allocate<char>( buf_size );
    return  strerror_r( _err, buf, buf_size );
}
//=======================================================================================
//[[noreturn]]
void Errno::throw_verror(const std::string &event ) const
{
    assert( !event.empty() );
    throw verror( vcat(event, ": ", str()).str() );
}
//=======================================================================================
bool Errno::eagain() const
{
    return _err == EAGAIN;
}
//=======================================================================================
bool Errno::resource_unavailable_try_again() const
{
    return eagain();
}
//=======================================================================================
bool Errno::operation_in_progress() const
{
    return _err == EINPROGRESS;
}
//=======================================================================================
bool Errno::connection_already_in_progress() const
{
    return _err == EALREADY;
}
//=======================================================================================
