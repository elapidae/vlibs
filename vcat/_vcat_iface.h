#ifndef VCAT_IFACE_H
#define VCAT_IFACE_H

#include <sstream>
#include <iomanip>
#include <limits>
#include <chrono>


//=======================================================================================
//      VCAT IFACE
//=======================================================================================
template<typename D>
class _vcat_iface
{
    using _std_modifier_t = decltype(std::hex);

public:
    //-----------------------------------------------------------------------------------

    template< typename T >
    D& operator()( const T& val );

    template< typename T, typename ... Ts >
    D& operator()( const T& val, const Ts& ... args );

    //-----------------------------------------------------------------------------------

    template< typename T >
    D& operator << ( const T& val );

    template< typename T >
    D& cat ( const T& val );

    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //  Пробная часть -- сбор модификаторов, пробы по их установке.

    D& oct();                    // equal to std::oct
    D& dec();                    // equal to std::dec
    D& hex();                    // equal to std::hex

    D& precision( int p );       // equal to std::setprecision(p);
    D& max_precision();

    D& fill_char( char ch );     // equal to std::setfill(ch)
    D& field_width( int w );     // equal to std::setw(fieldWidth)

    D& space();                  // Пробелы между аргументами, то же cat(vcat::Space).
    D& nospace();                // Отключает вывод пробелов, cat(vcat::NoSpace)

    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //      chrono
    D& cat        ( const std::chrono::seconds      &sec );
    D& cat        ( const std::chrono::milliseconds &sec );
    D& cat        ( const std::chrono::microseconds &sec );
    D& cat        ( const std::chrono::nanoseconds  &sec );

    D& operator() ( const std::chrono::seconds      &sec );
    D& operator<< ( const std::chrono::seconds      &sec );
    D& operator() ( const std::chrono::milliseconds &sec );
    D& operator<< ( const std::chrono::milliseconds &sec );
    D& operator() ( const std::chrono::microseconds &sec );
    D& operator<< ( const std::chrono::microseconds &sec );
    D& operator() ( const std::chrono::nanoseconds  &sec );
    D& operator<< ( const std::chrono::nanoseconds  &sec );
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //      private / not interest section.
    //-----------------------------------------------------------------------------------
    // Перегрузки нужны, чтобы при этих модификаторах был вызван специфичный код.
    enum   _space   { Space    };
    enum   _nospace { NoSpace  };
    D& cat          ( _std_modifier_t );
    D& operator()   ( _std_modifier_t );
    D& operator<<   ( _std_modifier_t );
    D& cat          ( _space   );
    D& operator()   ( _space   );
    D& operator<<   ( _space   );
    D& cat          ( _nospace );
    D& operator()   ( _nospace );
    D& operator<<   ( _nospace );
    //-----------------------------------------------------------------------------------

protected:
    _vcat_iface();

    template< typename ... Ts >
    explicit _vcat_iface( const Ts& ... args );

    ~_vcat_iface() = default;


private:
    bool _with_spaces  = false;
    bool _is_first_arg = true;
};
//=======================================================================================
//      VCAT IFACE
//=======================================================================================





//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================
//=======================================================================================
template< typename D >
_vcat_iface<D>::_vcat_iface()
{}
//=======================================================================================
template< typename D >
template< typename ... Ts >
_vcat_iface<D>::_vcat_iface( const Ts& ... args )
    : _vcat_iface()
{
    operator()( args... );
}
//=======================================================================================
template< typename D >
template< typename T >
D& _vcat_iface<D>::cat( const T& val )
{
    D& d = static_cast<D&>( *this );
    if ( !_is_first_arg && _with_spaces )
        d.do_cat(' ');

    d.do_cat( val );
    _is_first_arg = false;

    return d;
}
//=======================================================================================
template< typename D >
template< typename T >
D& _vcat_iface<D>::operator()( const T& val )
{
    return cat( val );
}
//=======================================================================================
template< typename D >
template< typename T, typename ... Ts >
D& _vcat_iface<D>::operator()( const T& val, const Ts& ... args )
{
    cat( val );
    return operator()( args... );
}
//=======================================================================================
template< typename D >
template< typename T >
D& _vcat_iface<D>::operator << ( const T& val )
{
    return cat( val );
}
//=======================================================================================
template< typename D >
D& _vcat_iface<D>::cat ( _std_modifier_t modifier )
{
    D& d = static_cast<D&>( *this );
    d.do_cat( modifier );
    return d;
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator << ( _std_modifier_t modifier )
{
    return cat( modifier );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator()( _std_modifier_t modifier )
{
    return cat( modifier );
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::cat( _nospace )
{
    _with_spaces = false;
    return static_cast<D&>( *this );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator << ( _nospace )
{
    return cat( NoSpace );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator()( _nospace )
{
    return cat( NoSpace );
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::cat ( _space )
{
    _with_spaces = true;
    return static_cast<D&>( *this );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator << ( _space )
{
    return cat( Space );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator()( _space )
{
    return cat( Space );
}
//=======================================================================================
template< typename D >
D& _vcat_iface<D>::oct()
{
    return cat( std::oct );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::dec()
{
    return cat( std::dec );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::hex()
{
    return cat( std::hex );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::precision( int p )
{
    return cat( std::setprecision(p) );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::max_precision()
{
    return precision( std::numeric_limits<long double>::digits10 + 1 );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::fill_char( char ch )
{
    return cat( std::setfill(ch) );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::field_width(int w)
{
    return cat( std::setw(w) );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::space()
{
    return cat( Space );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::nospace()
{
    return cat( NoSpace );
}
//=======================================================================================
//      chrono
//=======================================================================================
template< typename D >
D& _vcat_iface<D>::cat( const std::chrono::seconds & sec )
{
    D& d = static_cast<D&>( *this );
    cat("seconds[");
    d.do_cat(sec.count());
    d.do_cat(']');
    return d;
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::cat( const std::chrono::milliseconds &ms )
{
    D& d = static_cast<D&>( *this );
    cat("milliseconds[");
    d.do_cat(ms.count());
    d.do_cat(']');
    return d;
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::cat( const std::chrono::microseconds &us )
{
    D& d = static_cast<D&>( *this );
    cat("microseconds[");
    d.do_cat(us.count());
    d.do_cat(']');
    return d;
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::cat( const std::chrono::nanoseconds &ns )
{
    D& d = static_cast<D&>( *this );
    cat("nanoseconds[");
    d.do_cat(ns.count());
    d.do_cat(']');
    return d;
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator() ( const std::chrono::seconds& sec )
{
    return cat( sec );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator<< ( const std::chrono::seconds& sec )
{
    return cat( sec );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator() ( const std::chrono::milliseconds &ms )
{
    return cat( ms );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator<< ( const std::chrono::milliseconds &ms )
{
    return cat( ms );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator() ( const std::chrono::microseconds &us )
{
    return cat( us );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator<< ( const std::chrono::microseconds &us )
{
    return cat( us );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator() ( const std::chrono::nanoseconds  &ns )
{
    return cat( ns );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator<< ( const std::chrono::nanoseconds  &ns )
{
    return cat( ns );
}
//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================





#endif // VCAT_IFACE_H
