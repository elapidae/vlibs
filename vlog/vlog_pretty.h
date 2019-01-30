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


#ifndef VLOG_PRETTY_H
#define VLOG_PRETTY_H

#include "vlog.h"


//=======================================================================================
//  UPD 2019-01-24 -- vlog_pretty deprecated. Let all will be here.
//=======================================================================================
static bool vlog_prety_deprecated = []()
{
    vdeb << "'vlog_pretty.h' is deprecated, use 'vlog.h' instead...";
    return true;
}();
//=======================================================================================


#endif // VLOG_PRETTY_H
