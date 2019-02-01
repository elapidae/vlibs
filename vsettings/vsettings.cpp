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


#include "vsettings.h"

#include "vlog.h"
#include "verror.h"
#include <map>
#include <assert.h>

#include "vcompiler.h"
#include "_vsettings_parser.h"

using str  = VSettings::str;
using cstr = VSettings::cstr;

//=======================================================================================
static std::string spaces_for_level( int lvl )
{
    std::string res;
    while(lvl-- > 0) res += "    ";
    return res;
}
//=======================================================================================
static std::string view_lvl_comments( const std::vector<str>& comms, int lvl )
{
    std::string res;
    auto spaces = spaces_for_level( lvl );
    for (auto c: comms)
    {
        //  Костыль -- очистка пробелов с конца. С начала не надо, там м/б "рисунок".
        while ( !c.empty() && std::isspace(c.back()) )
            c.erase( c.end() - 1 );

        res += spaces + "#" + c + "\n";
    }
    return res;
}
//=======================================================================================


//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
struct Group
{
    Group( Group *parent, const std::string& name );
    std::string view_0() const;
    void form_sub_view(std::string prefix, std::string *res) const;
    std::string view_comments() const;

    struct KV
    {
        std::string view_keyval  (int lvl) const;
        std::string view_comments (int lvl) const;

        KV( cstr key, const VString& val );

        std::vector<std::string> comments;
        std::string key;
        VString val;
    };

    std::vector<std::string> comments;

    Group *parent = nullptr;
    std::string name;
    std::vector<Group> subgroups;
    std::vector<KV> key_vals;

    int level;
};
#pragma GCC diagnostic pop
//=======================================================================================
class VSettings::Pimpl
{
public:
    Pimpl()
        : root( nullptr, "" )
    {
        cur_group = &root;
    }

    Group root;
    Group *cur_group = nullptr;
};
//=======================================================================================
VSettings::VSettings()
    : p( new Pimpl )
{}
//=======================================================================================
VSettings::VSettings(const VString& ini_data )
    : p( new Pimpl )
{
    _impl::_vsettings_parse( ini_data.forward_view(), this );
}
//=======================================================================================
VSettings::~VSettings()
{}
//=======================================================================================
//  [1] - Если было перераспределение памяти, то старое значение указателя родителя
//        окажется невалидным. А нам надо будет правильно вернутся.
void VSettings::enter_group( cstr name )
{
    if ( name.empty() ) throw verror( "Cannot open empty group" );

    //  Если найдется такая группа, переходим в нее.
    for ( auto& g: p->cur_group->subgroups )
    {
        if ( g.name != name ) continue;
        g.parent = p->cur_group;            // [1]
        p->cur_group = &g;
        return;
    }

    //  Добавляем группу в конец.
    p->cur_group->subgroups.push_back( {p->cur_group, name} );
    p->cur_group = & p->cur_group->subgroups.back();
}
//=======================================================================================
void VSettings::leave_group()
{
    if ( !p->cur_group->parent ) throw verror("Leave root group");
    p->cur_group = p->cur_group->parent;
}
//=======================================================================================
void VSettings::leave_to_root_group()
{
    p->cur_group = &p->root;
}
//=======================================================================================
int VSettings::group_level() const
{
    return p->cur_group->level;
}
//=======================================================================================
VSettings::vec_str VSettings::cur_groups() const
{
    vec_str res;
    for( auto & g: p->cur_group->subgroups )
        res.push_back( g.name );
    return res;
}
//=======================================================================================
VSettings::cstr VSettings::cur_group() const
{
    return p->cur_group->name;
}
//=======================================================================================
VSettings::vec_str VSettings::cur_keys() const
{
    vec_str res;
    for( auto & kv: p->cur_group->key_vals )
        res.push_back( kv.key );
    return res;
}
//=======================================================================================
std::string VSettings::view() const
{
    std::string res;

    res += view_lvl_comments( p->root.comments, 0 );
    res += "\n";

    for ( auto &kv: p->root.key_vals )
    {
        res += kv.view_comments( 0 );
        res += kv.view_keyval  ( 0 );
    }

    for ( auto &g0: p->root.subgroups )
        res += g0.view_0();

    return res;
}
//=======================================================================================
//  Если в группе есть ключи-значения, то комментарий касается последнего из них,
//  иначе комментарий относится к группе.
void VSettings::add_comment( cstr comment )
{
    auto g = p->cur_group;
    if ( g->key_vals.empty() )
        g->comments.push_back( comment );
    else
        g->key_vals.back().comments.push_back( comment );
}
//=======================================================================================
void VSettings::add_comments(VSettings::cvec_str comments)
{
    for ( auto& c: comments )
        add_comment( c );
}
//=======================================================================================
const VString & VSettings::get( VSettings::cstr key ) const
{
    for (auto & kv: p->cur_group->key_vals )
        if ( kv.key == key ) return kv.val;

    throw verror("Key '", key, "' not found in group '", cur_group(), "'.");
}
//=======================================================================================
void VSettings::set(cstr key, const VString& val )
{
    if ( key.empty() ) throw verror( "Key is empty" );
    auto g = p->cur_group;
    g->key_vals.push_back( {key, val} );
}
//=======================================================================================
//      VSettings -- iface realization
//=======================================================================================


//=======================================================================================
//      Implement realizations
//=======================================================================================
Group::KV::KV( cstr key, const VString &val )
    : key(key), val(val)
{}
//=======================================================================================
std::string Group::KV::view_keyval( int lvl ) const
{
    return spaces_for_level(lvl) + key + "\t= " + val + "\n";
}
//=======================================================================================
std::string Group::KV::view_comments(int lvl) const
{
    return view_lvl_comments( comments, lvl );
}
//=======================================================================================

//=======================================================================================
Group::Group(Group *parent, const std::string &name)
    : parent ( parent )
    , name   ( name   )
{
    level = parent ? parent->level + 1 : 0;
}
//=======================================================================================
std::string Group::view_0() const
{
    std::string res;

    for ( auto& c: comments )
        res += "#" + c + "\n";

    res += "[" + name + "]\n";
    for ( auto & kv: key_vals )
    {
        res += kv.view_comments( 1 );   // 1 -- для сдвига в группу,
        res += kv.view_keyval  ( 1 );   //      они уже на первом уровне.
    }

    for ( auto & sg: subgroups )
        sg.form_sub_view( spaces_for_level(1), &res );

    return res;
}
//=======================================================================================
void Group::form_sub_view( std::string prefix, std::string *res ) const
{
    if ( !comments.empty() )
        vwarning.nospace()("Group '", name, "' has comment, but used as subgroup.");

    prefix += name + ".";

    for ( auto & kv: key_vals )
    {
        *res += kv.view_comments(1);
        *res += prefix + kv.view_keyval(0);
    }
    for ( auto & sg: subgroups )
    {
        sg.form_sub_view( prefix, res );
    }
}
//=======================================================================================
std::string Group::view_comments() const
{
    return view_lvl_comments( comments, level );
}
//=======================================================================================
//      Implement realizations
//=======================================================================================
