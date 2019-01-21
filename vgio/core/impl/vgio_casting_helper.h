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


#ifndef VGIO_CASTING_HELPER_H
#define VGIO_CASTING_HELPER_H

#include <gio/gio.h>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"

//=======================================================================================
template<class T>
GObject * gcast_to_gobject( T* g )
{
    return G_OBJECT( g );
}
//=======================================================================================
template<class T>
GInputStream * gcast_to_input_stream( T* i )
{
    return G_INPUT_STREAM( i );
}
//=======================================================================================
template<class T>
GOutputStream * gcast_to_output_stream( T* o )
{
    return G_OUTPUT_STREAM( o );
}
//=======================================================================================
template<class T>
GInetSocketAddress *gcast_to_ginet_socket_address( T *s )
{
    return G_INET_SOCKET_ADDRESS( s );
}
//=======================================================================================

#pragma GCC diagnostic pop


#endif // VGIO_CASTING_HELPER_H
