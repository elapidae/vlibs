#ifndef VAPP_ARGS_PARSER_H
#define VAPP_ARGS_PARSER_H

#include <vector>
#include <string>
#include <cmath>

class VApp_Args_Parser
{
public:
    VApp_Args_Parser( int argc, char **argv );

    std::string full_app_name() const;
    std::string app_name() const; // без пути.

    // Имеются ввиду опции вида ... --smth value ...
    std::string std_value( const std::string &name,
                           const std::string &defval = std::string() ) const;

    double std_double(const std::string &name) const;

    // Имеется ввиду просто наличие опции, например ... --help ...
    bool has( const std::string &name ) const;

    int size() const;
    std::string at(int pos) const;

private:
    std::vector<std::string> _args;
    std::string _appname;
};


#endif // VAPP_ARGS_PARSER_H
