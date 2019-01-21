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


#include "vcat.h"

template<class T>
class TD;

//=======================================================================================
vcat::vcat()
{
    _init_default_modifiers();
}
//=======================================================================================
std::string vcat::str() const
{
    return _stream.str();
}
//=======================================================================================
void vcat::_init_default_modifiers()
{
    // Эти флаги включаются по умолчанию.
    _stream << std::showbase << std::boolalpha;
}
//=======================================================================================
vcat::operator std::string() const
{
    return str();
}
//=======================================================================================

//=======================================================================================
std::ostream &operator <<( std::ostream &s, const vcat &c )
{
    s << c.str();
    return s;
}
//=======================================================================================
