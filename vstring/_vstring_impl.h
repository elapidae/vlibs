/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#if !defined(VSTRING_H) || defined(VSTRING_IMPL_H)
#error "Do not include this file '_vstring_impl.h' -- must be include only 'vstring.h'"
#endif


//=======================================================================================
//      VString
//      Constructors
//=======================================================================================
template <class InputIterator>
VString::VString( InputIterator first, InputIterator last )
    : std::string( first, last )
{}
//=======================================================================================
//      Constructors
//      Public wrappers
//=======================================================================================
template<typename T>
VString & VString::append_LE( T val )
{
    #if BYTE_ORDER == BIG_ENDIAN
    return _append_sys( reverse_T(val) );
    #else
    return append_as_sys( val );
    #endif
}
//=======================================================================================
template<typename T>
VString & VString::append_BE( T val )
{
    #if BYTE_ORDER == BIG_ENDIAN
    return _append_sys( val );
    #else
    return append_as_sys( reverse_T(val) );
    #endif
}
//=======================================================================================
template<typename T>
VString& VString::prepend_LE( T val )
{
    #if BYTE_ORDER == BIG_ENDIAN
    return _prepend_sys( reverse_T(val) );
    #else
    return prepend_as_sys( val );
    #endif
}
//=======================================================================================
template<typename T>
VString& VString::prepend_BE( T val )
{
    #if BYTE_ORDER == BIG_ENDIAN
    return _prepend_sys( val );
    #else
    return prepend_as_sys( reverse_T(val) );
    #endif
}
//=======================================================================================
//=======================================================================================
template<typename T>
T VString::back_BE() const
{
    #if BYTE_ORDER == BIG_ENDIAN
    return _back_sys<T>();
    #else
    return reverse_T( _back_sys<T>() );
    #endif
}
//=======================================================================================
template<typename T>
T VString::back_LE() const
{
    #if BYTE_ORDER == BIG_ENDIAN
    return reverse_T( _back_sys<T>() );
    #else
    return _back_sys<T>();
    #endif
}
//=======================================================================================
template<typename T>
T VString::front_BE() const
{
    #if BYTE_ORDER == BIG_ENDIAN
    return _front_sys<T>();
    #else
    return reverse_T( _front_sys<T>() );
    #endif
}
//=======================================================================================
template<typename T>
T VString::front_LE() const
{
    #if BYTE_ORDER == BIG_ENDIAN
    return reverse_T( _front_sys<T>() );
    #else
    return _front_sys<T>();
    #endif
}
//=======================================================================================
//      Public wrappers
//      append & prepend
//=======================================================================================
template<typename T>
VString & VString::append_as_sys( const T& val )
{
    auto * ch = static_cast<const char*>( static_cast<const void*>(&val) );
    insert( size(), ch, sizeof(T) );
    return *this;
}
//=======================================================================================
template<typename T>
VString& VString::prepend_as_sys( const T& val )
{
    auto * ch = static_cast<const char*>( static_cast<const void*>(&val) );
    insert( 0, ch, sizeof(T) );
    return *this;
}
//=======================================================================================
template<typename It>
VString& VString::prepend( It b, It e )
{
    static_assert( sizeof(*b) == 1, "sizeof(It::value_type) != 1" );
    insert( begin(), b, e );
    return *this;
}
//=======================================================================================
template<typename It>
VString& VString::append( It b, It e )
{
    static_assert( sizeof(*b) == 1, "sizeof(It::value_type) != 1" );
    insert( end(), b, e );
    return *this;
}
//=======================================================================================
//      append & prepend
//      front, back & pop_front, pop_back
//=======================================================================================
template<typename T>
T VString::take_front_LE()
{
    auto res = front_LE<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VString::take_front_BE()
{
    auto res = front_BE<T>();
    chop_front( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VString::take_back_LE()
{
    auto res = back_LE<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
T VString::take_back_BE()
{
    auto res = back_BE<T>();
    chop_back( sizeof(T) );
    return res;
}
//=======================================================================================
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
VString::_front_sys() const
{
    _check_enough_size( sizeof(T) );

    T res;
    auto *ch = static_cast<char*>( static_cast<void*>(&res) );

    std::copy( begin(), begin() + sizeof(T), ch );
    return res;
}
//=======================================================================================
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
VString::_back_sys() const
{
    _check_enough_size( sizeof(T) );

    T res;
    auto *ch = static_cast<char*>( static_cast<void*>(&res) );

    std::copy( end() - sizeof(T), end(), ch );
    return res;
}
//=======================================================================================
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
VString::reverse_T( T val )
{
    auto *ch = static_cast<char*>( static_cast<void*>(&val) );
    constexpr auto tsize = sizeof(T);

    //std::reverse( ch, ch + tsize );

    //  UPD 28-12-2018: так оказалось быстрее, проверка была сделана в тестах VTimeMeter.
    switch( tsize )
    {
    case 8: std::swap( ch[3], ch[tsize-4] );
            std::swap( ch[2], ch[tsize-3] );
    case 4: std::swap( ch[1], ch[tsize-2] );
    case 2: std::swap( ch[0], ch[tsize-1] );
    }

    return val;
}
//=======================================================================================
//      front, back & pop_front, pop_back
//      std::stream wrappers: text_to_any & any_to_text
//=======================================================================================
template<typename T>
T VString::text_to_any( const std::string& val )
{
    std::stringstream ss( val );
    T res = T();
    ss >> res;
    return res;
}
//=======================================================================================
template<typename T>
T VString::text_to_any() const
{
    return text_to_any<T>( *this );
}
//=======================================================================================
template<typename T>
std::string VString::any_to_text( const T& val )
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}
//=======================================================================================
//      std::stream wrappers: text_to_any & any_to_text
//      VString
//=======================================================================================


//=======================================================================================
//      FORWARD VIEW
//=======================================================================================
template<typename T>
T VString::ForwardView::show_LE() const
{
    if ( _remained < sizeof(T) )
        throw std::out_of_range( "VString::ForwardView::show_LE<T>(): not enouth data" );

    auto res = * static_cast<const T*>( static_cast<const void*>(_buffer) );

    #if BYTE_ORDER == BIG_ENDIAN
        res = VString::reverse_T( res );
    #endif

    return res;
}
//=======================================================================================
template<typename T>
T VString::ForwardView::show_BE() const
{
    if ( _remained < sizeof(T) )
        throw std::out_of_range( "VString::ForwardView::take_BE<T>(): not enouth data" );

    auto res = * static_cast<const T*>( static_cast<const void*>(_buffer) );

    #if BYTE_ORDER == LITTLE_ENDIAN
        res = VString::reverse_T( res );
    #endif

    return res;
}
//=======================================================================================
template<typename T>
T VString::ForwardView::take_LE()
{
    auto res = show_LE<T>();

    _remained -= sizeof(T);
    _buffer   += sizeof(T);

    return res;
}
//=======================================================================================
template<typename T>
T VString::ForwardView::take_BE()
{
    auto res = show_BE<T>();

    _remained -= sizeof(T);
    _buffer   += sizeof(T);

    return res;
}
//=======================================================================================
//      FORWARD VIEW
//=======================================================================================

#define VSTRING_IMPL_H
