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
