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


#include "voutfile.h"

#include <assert.h>

// для проверки существования файла.
#include <sys/stat.h>

using namespace std;


//=======================================================================================
static ios_base::openmode std_mode( VOutFile::OpenMode mode )
{
    auto base = ios_base::out|ios_base::binary;

    if ( mode == VOutFile::OpenMode::Append   )     return base|ios_base::app;
    if ( mode == VOutFile::OpenMode::Truncate )     return base|ios_base::trunc;

    assert( false && "Unknown VOutFile::OpenMode" );
}
//=======================================================================================



//=======================================================================================
//VOutFile::VOutFile()
//{}
//=======================================================================================
VOutFile::VOutFile( const std::string &fname, VOutFile::OpenMode mode )
    : _s     ( fname, std_mode(mode) )
    , _fname ( fname )
{
    _fast_size = size();
}
//=======================================================================================
void VOutFile::write( const string & data )
{
    _s.write( data.data(), static_cast<std::streamsize>(data.size()) );

    if ( !_s.good() )
        throw std::ios_base::failure( "File '" + _fname + "' is not good()." );

    _fast_size += data.size();
}
//=======================================================================================
void VOutFile::flush()
{
    _s.flush();
}
//=======================================================================================
bool VOutFile::rename(const string &to)
{
    return rename( _fname, to );
}
//=======================================================================================
bool VOutFile::rename( const string &from, const string &to )
{
    return 0 == std::rename( from.c_str(), to.c_str() );
}
//=======================================================================================
bool VOutFile::exists( const string &fname )
{
    struct stat buffer;
    return stat(fname.c_str(), &buffer) == 0;
}
//=======================================================================================
bool VOutFile::is_open() const
{
    return _s.is_open();
}
//=======================================================================================
bool VOutFile::is_good() const
{
    return _s.good();
}
//=======================================================================================
ulong VOutFile::fast_size() const
{
    return _fast_size;
}
//=======================================================================================
//  Простеньким тестом выяснил, что вызов tellp() не портит позицию в файле, однако
//  этот метод не константный (т.к. пользует какие-то неконстантные мероприятия с
//  буффером).
long VOutFile::size() const
{
    auto & ofs = const_cast<std::ofstream &>( _s );
    return ofs.tellp();
}
//=======================================================================================
const string VOutFile::filename() const
{
    return _fname;
}
//=======================================================================================
