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


#include "verror.h"

#include "vlog.h"


//=======================================================================================
static
std::shared_ptr<VLogger> make_logger( const char *file, int line, const char *func )
{
    return std::make_shared<VLogger>( VLogEntry::Level::Fatal,
                                      file, line, func,
                                      VLogger::_is_proxy::is_proxy );
}
//=======================================================================================


//=======================================================================================
VError::VError( const char *file, int line, const char *func )
    : _logger  ( make_logger(file, line, func) )
    , _printed ( std::make_shared<bool>(false) )
{
    _preambul = _logger->entry().place_func();
    _logger->do_cat( " ERROR: " );
}
//=======================================================================================
VError::~VError() noexcept
{
    if ( *_printed ) return;

    VLogger::execute( *_logger );
    *_printed = true;
}
//=======================================================================================
const char *VError::what() const noexcept
{
    return _what.c_str();
}
//=======================================================================================
