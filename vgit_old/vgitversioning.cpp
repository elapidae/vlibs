#include "vgitversioning.h"

#include "vcat.h"
#include "vgitcatch/vgit_catcher.h"
#include "vstring.h"
#include <iostream>

//=======================================================================================
std::string VGitVersioning::hash()
{
    return VGitCatcher().hash;
}
//=======================================================================================
std::string VGitVersioning::branch()
{
    return VGitCatcher().branch;
}
//=======================================================================================
int VGitVersioning::revcount()
{
    return VGitCatcher().revcount;
}
//=======================================================================================
std::string VGitVersioning::as_message( const std::string &query )
{
    if ( query == "--vgit-hash" )       return hash();
    if ( query == "--vgit-branch" )     return branch();
    if ( query == "--vgit-revcount" )   return vcat(revcount());

    return vcat( "hash=", hash(), ", branch=", branch(), ", revcount=", revcount() );
}
//=======================================================================================
void VGitVersioning::print_and_exit_if_need( int argc, char **argv )
{
    for ( int i = 1; i < argc; ++i )
    {
        VString str( argv[i] );
        if ( !str.begins_with("--vgit") ) continue;
        std::cout << as_message(str) << std::endl;
        exit(0);
    }
}
//=======================================================================================
