#include "vverbalexpr.h"

#include <algorithm>

using namespace std;

//=======================================================================================
template<typename Cont>
bool contains( const Cont& c, const typename Cont::value_type& val )
{
    return c.find( val ) != c.end();
}
//=======================================================================================


//=======================================================================================
class VVerbalExpr::_pimpl
{
public:
    virtual ~_pimpl() {}
    //virtual bool match( const std::string& data ) const = 0;

    virtual bool starts_with( const std::string& data ) const = 0;
    virtual VVerbalExpr::str_it step( const VVerbalExpr::str_it& b,
                                      const VVerbalExpr::str_it& e ) const = 0;
};
//=======================================================================================
class Chars : public VVerbalExpr::_pimpl
{
    set<char> chars;
public:
    Chars( const set<char>& chars) : chars(chars) {}

    bool starts_with( const string& data ) const
    {
        return !data.empty() &&
                chars.find(data[0]) != chars.end();
    }
    virtual VVerbalExpr::str_it step( const VVerbalExpr::str_it& b,
                                      const VVerbalExpr::str_it& e ) const
    {
        if ( b == e ) return b;
        return contains(chars, *b) ? b + 1 : b;
    }
};
//=======================================================================================



//=======================================================================================
VVerbalExpr VVerbalExpr::latin_downs()
{
    static auto res = []()
    {
        set<char> res;
        for ( char ch = 'a'; ch <= 'z'; ++ch )
            res.emplace( ch );
        return VVerbalExpr( std::make_shared<Chars>(res) );
    }();
    return res;
}
//=======================================================================================
VVerbalExpr VVerbalExpr::chars(const std::set<char> &chs)
{
    return { std::make_shared<Chars>(chs) };
}
//=======================================================================================
VVerbalExpr::VVerbalExpr(const std::shared_ptr<_pimpl>& pp )
    : p( pp )
{}
//=======================================================================================
bool VVerbalExpr::starts_with( const string &data ) const
{
    return p->starts_with( data );
}
//=======================================================================================
VVerbalExpr::str_it VVerbalExpr::step( const str_it& b, const str_it& e ) const
{
    return p->step( b, e );
}
//=======================================================================================
