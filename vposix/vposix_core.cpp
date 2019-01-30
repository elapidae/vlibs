/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


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
void Errno::throw_verror( const std::string &event ) const
{
    assert( !event.empty() );
    throw verror( vcat(event, ": ", str()).str() );
}
//=======================================================================================
bool Errno::again_or_wouldblock() const
{
    return _err == EAGAIN || _err == EWOULDBLOCK;
}
//=======================================================================================
bool Errno::resource_unavailable_try_again() const
{
    return again_or_wouldblock();
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
