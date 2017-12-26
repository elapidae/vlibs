#include "nconvertinghelper.h"

#include <glib.h>


using namespace std;


//=======================================================================================
std::vector<std::string> n_convert_and_free( char **list )
{
    vector<string> res;
    if ( !list ) return res;

    for ( auto it = list; *it; ++it )
        res.push_back( *it );

    g_strfreev( list );
    return res;
}
//=======================================================================================
string n_convert_and_free( char *raw )
{
    string res( raw ? raw : "" );
    if (raw) g_free(raw);
    return res;
}
//=======================================================================================
