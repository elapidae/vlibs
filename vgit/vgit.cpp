#include "vgit.h"

#include <iostream>
#include <sstream>

//=======================================================================================
#define VGIT_QUOTES_FOR_EXTRACT_DEFINES(name) #name
#define VGIT_STRING_FOR_EXTRACT_DEFINES(macro) VGIT_QUOTES_FOR_EXTRACT_DEFINES(macro)
//=======================================================================================

//=======================================================================================
#define VGIT_CURRECT_HASH_BYEL      VGIT_STRING_FOR_EXTRACT_DEFINES(VGIT_HASH_ELPD)
#define VGIT_CURRECT_REVCOUNT_BYEL  VGIT_STRING_FOR_EXTRACT_DEFINES(VGIT_REVCOUNT_ELPD)
#define VGIT_CURRECT_BRANCH_BYEL    VGIT_STRING_FOR_EXTRACT_DEFINES(VGIT_BRANCH_ELPD)
#define VGIT_CURRECT_DATE_BYEL      VGIT_STRING_FOR_EXTRACT_DEFINES(VGIT_DATE_ELPD)
#define VGIT_CURRECT_AUTHOR_BYEL    VGIT_STRING_FOR_EXTRACT_DEFINES(VGIT_AUTHOR_ELPD)
//#define VGIT_CURRECT_COMMENT_BYEL   VGIT_STRING_FOR_EXTRACT_DEFINES(VGIT_COMMENT_ELPD)
//#define VGIT_CURRECT_OLOLOLOLO    VGIT_STRING_FOR_EXTRACT_DEFINES(OLOLOLOLO)
//=======================================================================================


//=======================================================================================
std::string VGit::hash()
{
    return VGIT_CURRECT_HASH_BYEL;
}
//=======================================================================================
std::string VGit::date()
{
    return VGIT_CURRECT_DATE_BYEL;
}
//=======================================================================================
std::string VGit::author()
{
    return VGIT_CURRECT_AUTHOR_BYEL;
}
//=======================================================================================
//  Если ветка HEAD, значит, что у репа оторвана голова. Подробнее см. vgit.pri.
std::string VGit::branch()
{
    std::string res = VGIT_CURRECT_BRANCH_BYEL;

    if ( res == "HEAD" )
        return  "DETACHED HEAD";

    return res;
}
//=======================================================================================
std::string VGit::revcount()
{
    return VGIT_CURRECT_REVCOUNT_BYEL;
}
//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdate-time"
std::string VGit::compile_datetime()
{
    std::stringstream ss;
    ss << __DATE__ << "T" << __TIME__;
    return ss.str();
}
#pragma GCC diagnostic pop
//=======================================================================================
std::string VGit::as_message(const std::string &query)
{
    if ( query == "--vgit-hash"     )   return hash();
    if ( query == "--vgit-branch"   )   return branch();
    if ( query == "--vgit-revcount" )   return revcount();
    if ( query == "--vgit-date"     )   return date();
    if ( query == "--vgit-author"   )   return author();

    std::stringstream ss;
    ss << "hash="       << hash()
       << ", branch="   << branch()
       << ", revcount=" << revcount()
       << ", date="     << date()
       << ", author="   << author()
       << ", comptime=" << compile_datetime();

    return ss.str();
}
//=======================================================================================
void VGit::print_and_exit_if_need(int argc, const char * const *argv, int retcode)
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

