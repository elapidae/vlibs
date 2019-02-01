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


#ifndef IMPL_VSETTINGS_PARSER_H
#define IMPL_VSETTINGS_PARSER_H

#include "vstring.h"
#include <memory>

class VSettings;
//=======================================================================================
namespace _impl
{
    class ASCII_Raw_Viewer;

    class _vsettings_parse final
    {
    public:
        _vsettings_parse( VString::ForwardView view, VSettings *sett );
        ~_vsettings_parse();

    private:
        std::unique_ptr<ASCII_Raw_Viewer> viewer;
        VSettings * _settings;

        void add_group_0  ( VString name );
        void add_subgroup ( VString name );
        void add_keyval   ( VString key, VString val );

        std::vector<std::string> comments;

        void parse_next();
        void read_first_group();
        void read_comment();
        void read_keyval();
    };
} // _impl
//=======================================================================================

#endif // IMPL_VSETTINGS_PARSER_H
