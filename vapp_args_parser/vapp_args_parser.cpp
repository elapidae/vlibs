#include "vapp_args_parser.h"

#include <algorithm>
#include <sstream>

using namespace std;

//=======================================================================================
VApp_Args_Parser::VApp_Args_Parser(int argc, char **argv)
{
    _appname = argv[0];
    for (int i = 1; i < argc; ++i )
    {
        _args.push_back( argv[i] );
    }
}
//=======================================================================================
std::string VApp_Args_Parser::full_app_name() const
{
    return _appname;
}
//=======================================================================================
std::string VApp_Args_Parser::app_name() const
{
    auto rbegin = _appname.rbegin();
    auto rend = _appname.rend();
    auto it = find( rbegin, rend, '/' );
    --it;

    string res;
    for ( ;; --it )
    {
        res.push_back( *it );
        if (it == rbegin) break;
    }
    return res;
}
//=======================================================================================
std::string VApp_Args_Parser::std_value( const std::string &name,
                                         const std::string &defval ) const
{
    int i = 0;
    for ( i = 0; i < int(_args.size()); ++i )
        if (name == _args[i])
            break;

    return i < int(_args.size()) - 1
                    ? _args[i + 1]
                    : defval;
}
//=======================================================================================
double VApp_Args_Parser::std_double(const string &name) const
{
    stringstream ss( std_value(name) );
    double res;
    ss >> res;
    return res;
}
//=======================================================================================
bool VApp_Args_Parser::has( const std::string &name ) const
{
    for ( const auto &s: _args )
        if ( s == name ) return true;

    return false;
}
//=======================================================================================
int VApp_Args_Parser::size() const
{
    return _args.size();
}
//=======================================================================================
string VApp_Args_Parser::at(int pos) const
{
    return _args.at(pos);
}
//=======================================================================================
