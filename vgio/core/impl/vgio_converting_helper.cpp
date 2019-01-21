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


#include "vgio_converting_helper.h"

#include <glib.h>


using namespace std;


//=======================================================================================
std::vector<std::string> vgio::_impl::convert_and_free_list( char **list )
{
    vector<string> res;
    if ( !list ) return res;

    for ( auto it = list; *it; ++it )
        res.push_back( *it );

    g_strfreev( list );
    return res;
}
//=======================================================================================
string vgio::_impl::convert_and_free( char *raw )
{
    string res( raw ? raw : "" );
    if (raw) g_free(raw);
    return res;
}
//=======================================================================================
