#ifndef VVERBALEXPR_H
#define VVERBALEXPR_H

#include <memory>
#include <set>

class VVerbalExpr
{
public:
    using str_it = std::string::const_iterator;

    static VVerbalExpr latin_downs ();
    static VVerbalExpr latin_ups   ();
    static VVerbalExpr latins      ();

    static VVerbalExpr rus_downs   ();
    static VVerbalExpr rus_ups     ();
    static VVerbalExpr russ        ();


    static VVerbalExpr chars     ( const std::set<char>& chs );
    static VVerbalExpr strings   ( const std::set<std::string>& sts );
    static VVerbalExpr digits_10 ();
    static VVerbalExpr digits_16 ();

    bool match( const std::string& data ) const;
    bool starts_with( const std::string& data ) const;

    str_it step( const str_it& b, const str_it& e ) const;

    class _pimpl;
private:
    VVerbalExpr( const std::shared_ptr<_pimpl>& pp );
    std::shared_ptr<_pimpl> p;
};





#endif // VVERBALEXPR_H
