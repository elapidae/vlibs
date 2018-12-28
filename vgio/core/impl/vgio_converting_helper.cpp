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
