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


#include "vgio_error.h"

#include <glib.h>
#include <stdexcept>

#include "vcat.h"
#include "verror.h"

using namespace std;
using namespace vgio;



//=======================================================================================
//      Exception
//=======================================================================================
Exception::Exception( const std::string &msg )
    : runtime_error( msg )
{}
//=======================================================================================
//      Exception
//=======================================================================================



//=======================================================================================
//      Error
//=======================================================================================
Error::Error()
{}
//=======================================================================================
bool Error::has() const
{
    return bool( p );
}
//=======================================================================================
std::string Error::message() const
{
    return p ? p->message : std::string();
}
//=======================================================================================
uint32_t Error::domain() const
{
    return p ? p->domain : 0;
}
//=======================================================================================
int Error::code() const
{
    return p ? p->code : 0;
}
//=======================================================================================
string Error::debug_msg() const
{
    return p ? _deb_msg( p.get() ) : string();
}
//=======================================================================================
string Error::_deb_msg( GError *err )
{
    return vcat() << err->message << " [" << err->domain << ":" << err->code << "]";
}
//=======================================================================================
Error::Error( GError *err )
{
    _set( err );
}
//=======================================================================================
void Error::_set( GError *err )
{
    if (err) p.reset( err, g_error_free );
    else     p.reset();
}
//=======================================================================================
//      Error
//=======================================================================================



//=======================================================================================
//      _error_proxy
//=======================================================================================
_impl::error_proxy::error_proxy( Error *err )
    : _target( err )
{}
//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wexceptions"
#pragma GCC diagnostic ignored "-Wterminate"
_impl::error_proxy::~error_proxy()
{
    // Я знаю, что нельзя бросать исключения из деструктора, но здесь обратный случай,
    // когда класс используется для оповещения об ошибке.
    if ( !_flushed )
    {
        throw verror << "Была использована _impl::error_proxy, но не была сброшена.\n"
                        "Следует делать flush() после использования (скорее всего, "
                        "автор просто забыл это сделать).";
    }
}
#pragma GCC diagnostic pop
//=======================================================================================
void _impl::error_proxy::flush()
{
    _flushed = true;

    if ( _target )
    {
        _target->_set( _gerror );
    }
    else if ( _gerror )
    {
        string msg = Error::_deb_msg( _gerror );
        g_error_free( _gerror );
        throw Exception( msg );
    }
}
//=======================================================================================
_impl::error_proxy::operator GError **()
{
    return &_gerror;
}
//=======================================================================================
//      _error_proxy
//=======================================================================================



