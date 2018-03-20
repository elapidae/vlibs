#include "vcat.h"

template<class T>
class TD;

//=======================================================================================
vcat::vcat()
{
    // Эти флаги включаются по умолчанию.
    stream << std::showbase << std::boolalpha;
}
//=======================================================================================
vcat &vcat::operator << ( _std_modifier_t modifier )
{
    stream << modifier;
    return *this;
}
//---------------------------------------------------------------------------------------
vcat &vcat::operator()( _std_modifier_t modifier )
{
    stream << modifier;
    return *this;
}
//=======================================================================================
vcat& vcat::operator << ( vcat::_nospace )
{
    return operator()( NoSpace );
}
//---------------------------------------------------------------------------------------
vcat &vcat::operator << ( vcat::_space )
{
    return operator()( Space );
}
//---------------------------------------------------------------------------------------
vcat &vcat::operator()( vcat::_nospace )
{
    _with_spaces = false;
    return *this;
}
//---------------------------------------------------------------------------------------
vcat &vcat::operator()( vcat::_space )
{
    _with_spaces = true;
    return *this;
}
//=======================================================================================
std::string vcat::str() const
{
    return stream.str();
}
//---------------------------------------------------------------------------------------
vcat::operator std::string() const
{
    return str();
}
//=======================================================================================
vcat &vcat::oct()
{
    return cat( std::oct );
}
//---------------------------------------------------------------------------------------
vcat &vcat::dec()
{
    return cat( std::dec );
}
//---------------------------------------------------------------------------------------
vcat &vcat::hex()
{
    return cat( std::hex );
}
//---------------------------------------------------------------------------------------
vcat &vcat::precision( int p )
{
    stream << std::setprecision(p);
    return *this;
}
//---------------------------------------------------------------------------------------
vcat &vcat::max_precision()
{
    return precision( std::numeric_limits<long double>::digits10 + 1 );
}
//---------------------------------------------------------------------------------------
vcat &vcat::fill_char( char ch )
{
    return cat( std::setfill(ch) );
}
//---------------------------------------------------------------------------------------
vcat &vcat::field_width(int w)
{
    return cat( std::setw(w) );
}
//---------------------------------------------------------------------------------------
vcat &vcat::space()
{
    return cat( Space );
}
//---------------------------------------------------------------------------------------
vcat &vcat::nospace()
{
    return cat( NoSpace );
}
//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wcomma"                // Выключаю, чтобы не мешали
#pragma GCC diagnostic ignored "-Wunreachable-code"     // предупреждения в тернарном
                                                        // операторе /там все нормально/.
vcat &vcat::cat( long a, int fieldWidth, int base, char fillChar )
{
    auto sys_md = base ==  8 ? std::oct
                : base == 10 ? std::dec
                : base == 16 ? std::hex
                : (throw std::logic_error("VCat /пока/ не умеет делать в системах, "
                                          "не равных 8/10/16..."), std::hex);

    auto cur_mds = stream.flags();
    //TD<decltype(cur_mds)> cur_mds_type;

    if ( _with_spaces && !_is_first_arg )
        stream << ' ';
    _is_first_arg = false;

    stream << std::setw(fieldWidth) << std::setfill(fillChar) << sys_md << a;
    stream.flags(cur_mds);

    return *this;
}
#pragma GCC diagnostic pop
//=======================================================================================
