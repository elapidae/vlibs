#include "vgit.h"

#include <iostream>
#include <sstream>

//=======================================================================================
#define VGIT_QUOTES_FOR_EXTRACT_DEFINES(name) #name
#define VGIT_STRING_FOR_EXTRACT_DEFINES(macro) VGIT_QUOTES_FOR_EXTRACT_DEFINES(macro)
//=======================================================================================

//=======================================================================================
#define VGIT_CURRECT_HASH_BYEL    VGIT_STRING_FOR_EXTRACT_DEFINES(VGIT_HASH_ELPD)
#define VGIT_CURRECT_RVCOUNT_BYEL VGIT_STRING_FOR_EXTRACT_DEFINES(VGIT_REVCOUNT_ELPD)
#define VGIT_CURRECT_BRANCH_BYEL  VGIT_STRING_FOR_EXTRACT_DEFINES(VGIT_BRANCH_ELPD)
//=======================================================================================

//=======================================================================================
std::string VGit::hash()
{
    return VGIT_CURRECT_HASH_BYEL;
}
//=======================================================================================
std::string VGit::branch()
{
    return VGIT_CURRECT_BRANCH_BYEL;
}
//=======================================================================================
std::string VGit::revcount()
{
    return VGIT_CURRECT_RVCOUNT_BYEL;
}
//=======================================================================================
std::string VGit::as_message(const std::string &query)
{
    if ( query == "--vgit-hash" )       return hash();
    if ( query == "--vgit-branch" )     return branch();
    if ( query == "--vgit-revcount" )   return revcount();

    std::stringstream ss;
    ss << "hash=" << hash() << ", branch=" << branch() << ", revcount=" << revcount();
    return ss.str();
}
//=======================================================================================
void VGit::print_and_exit_if_need(int argc, char **argv, int retcode)
{
    std::string vgit("--vgit");
    for ( int i = 1; i < argc; ++i )
    {
        std::string str = argv[i];
        auto sub = str.substr(0, vgit.size());
        if ( sub != vgit ) continue;
        std::cout << as_message(str) << std::endl;
        exit( retcode );
    }
}
//=======================================================================================

