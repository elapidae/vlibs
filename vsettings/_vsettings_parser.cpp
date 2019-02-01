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


#include "_vsettings_parser.h"

#include "vstring.h"
#include "verror.h"
#include "vcompiler.h"
#include <assert.h>
#include "vsettings.h"

using namespace _impl;

namespace _impl
{
    class ASCII_Raw_Viewer
    {
    public:
        ASCII_Raw_Viewer( VString::ForwardView view );

        void kill_any_spaces();

        char take();
        char show(uint pos) const;
        char next() const                       { return show(0); }

        static bool at_end          ( char ch ) { return ch == '\0';                }
        static bool is_escape       ( char ch ) { return ch == '\\';                }
        static bool is_endl         ( char ch ) { return ch == '\n';                }
        static bool is_endl_or_fin  ( char ch ) { return is_endl(ch) || at_end(ch); }

        bool at_end() const                     { return at_end(next()); }

        bool is_escaped_endl() const;

        VString read_in_line_until( char stop );

        V_NORETURN void error( std::string msg ) const;

        static bool is_lined_space  ( char ch );
        static bool is_any_space    ( char ch );

    private:
        VString::ForwardView _view;

        int _line = 1;
        int _pos  = 1;
    };
}

//=======================================================================================
_vsettings_parse::_vsettings_parse( VString::ForwardView view, VSettings *sett )
    : viewer   ( new ASCII_Raw_Viewer(view) )
    , _settings ( sett )
{
    while ( 1 )
    {
        viewer->kill_any_spaces();
        if ( viewer->at_end() ) break;
        parse_next();
    }

    _settings->leave_to_root_group();
}
//=======================================================================================
_vsettings_parse::~_vsettings_parse()
{}
//=======================================================================================
void _vsettings_parse::add_subgroup( VString name )
{
    name = name.trimmed();
    if ( name.empty() ) viewer->error("Empty group name");

    _settings->enter_group( name );

    // do not attach comments
}
//=======================================================================================
void _vsettings_parse::add_group_0( VString name )
{
    name = name.trimmed();
    if ( name.empty() ) viewer->error("Empty group name");

    _settings->enter_group( name );

    _settings->add_comments( comments );
    comments.clear();
}
//=======================================================================================
void _vsettings_parse::add_keyval( VString key, VString val )
{
    key = key.trimmed();
    val = val.trimmed();
    if ( key.empty() ) viewer->error( "Empty key name" );
    if ( val.empty() ) viewer->error( "Empty value" );

    _settings->set( key, val );

    _settings->add_comments( comments );
    comments.clear();
}
//=======================================================================================
void _vsettings_parse::parse_next()
{
    if      ( viewer->next() == '[' )   read_first_group();
    else if ( viewer->next() == '#' )   read_comment();
    else                                read_keyval();
}
//=======================================================================================
void _vsettings_parse::read_first_group()
{
    viewer->take(); // delete '['
    _settings->leave_to_root_group();
    auto group = viewer->read_in_line_until( ']' );
    add_group_0( group );
}
//=======================================================================================
void _vsettings_parse::read_comment()
{
    viewer->take(); // delete "#"
    comments.push_back( viewer->read_in_line_until('\n') );
}
//=======================================================================================
//  - Сначала вычитывается строка до символа '=', режется на подгруппы с разделителем '.'
//    Последняя строка считается ключом, остальные -- подгруппы;
//  - далее открываются подгруппы;
//  - далее -- читаем до конца строки, это будет значение;
//  - добавляем в настройки это счастие;
//  - закрываем ровно столько групп, сколько открыли;
void _vsettings_parse::read_keyval()
{
    auto tmp = viewer->read_in_line_until('=');
    auto group_key = tmp.split('.');
    if ( group_key.empty() ) viewer->error("Empty key name");
    auto groups_count = group_key.size() - 1;
    for ( uint i = 0; i < groups_count; ++i )
    {
        auto group = group_key.at(i);
        add_subgroup( group );
    }
    auto key   = group_key.back();
    auto value = viewer->read_in_line_until( '\n' );
    add_keyval( key, value );

    for ( uint i = 0; i < groups_count; ++i )
    {
        _settings->leave_group();
    }
}
//=======================================================================================


//=======================================================================================
//      ASCII_Raw_Viewer
//=======================================================================================
ASCII_Raw_Viewer::ASCII_Raw_Viewer( VString::ForwardView view )
    : _view( view )
{}
//=======================================================================================
void ASCII_Raw_Viewer::kill_any_spaces()
{
    while( 1 )
    {
        if ( is_any_space(next()) )
        { take(); continue; }

        if ( is_escaped_endl() )
        { take(); take(); continue; }

        break;
    }
}
//=======================================================================================
char ASCII_Raw_Viewer::take()
{
    auto res = show( 0 );
    if ( !_view.finished() ) _view.take_ch();

    ++_pos;
    if ( res == '\n' ) { _pos = 1; ++_line; }

    return res;
}
//=======================================================================================
char ASCII_Raw_Viewer::show( uint pos ) const
{
    if ( _view.finished() ) return '\0';
    char res = _view.show_str(pos + 1).at(pos);
    if (res == '\0') error( "\\0 unexpected" );
    return res;
}
//=======================================================================================
bool ASCII_Raw_Viewer::is_escaped_endl() const
{
    if ( !is_escape(next()) ) return false;
    auto next = show(1);
    if ( next == '\0' ) error("Escape symbol at end");
    return next == '\n';
}
//=======================================================================================
VString ASCII_Raw_Viewer::read_in_line_until( char stop )
{
    VString res;
    while ( 1 )
    {
        if (is_escaped_endl()) { take(); take(); continue; }

        char ch = take();
        if ( ch == stop || ch == '\0' ) break;
        if ( ch == '\n' ) error("Unexpected end of line.");
        res += ch;
    }
    return res;
}
//=======================================================================================
void ASCII_Raw_Viewer::error( std::string msg ) const
{
    throw verror("Ini parse error at [", _line, ':', _pos, "] -- ", msg);
}
//=======================================================================================
bool ASCII_Raw_Viewer::is_lined_space( char ch )
{
    return ch == ' ' || ch == '\t' || ch == '\r';
}
//=======================================================================================
bool ASCII_Raw_Viewer::is_any_space( char ch )
{
    return is_lined_space(ch) ||
           is_endl(ch);
}
//=======================================================================================
//      ASCII_Raw_Viewer
//=======================================================================================
