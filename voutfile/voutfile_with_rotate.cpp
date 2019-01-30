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


#include "voutfile_with_rotate.h"

#include <assert.h>
#include "vcat.h"

// del it
//#include <iostream>

//=======================================================================================
VOutFile_With_Rotate::VOutFile_With_Rotate()
{}
//=======================================================================================
VOutFile_With_Rotate::VOutFile_With_Rotate(const std::string &base_fname,
                                            ulong one_file_size,
                                            uint rotate_files_count )
    : _base_fname         ( base_fname         )
    , _one_file_size      ( one_file_size      )
    , _rotate_files_count ( rotate_files_count )
{
    _reopen_file();

    // Если такой файл уже есть и он заполнен под завязку.
    if ( _cur_file->fast_size() > _one_file_size )
        _rotate_and_reinit_file();
}
//=======================================================================================
void VOutFile_With_Rotate::_reopen_file()
{
    _cur_file.reset( new VOutFile(_base_fname, VOutFile::OpenMode::Append) );

    if ( _cur_file->is_open() && _cur_file->is_good() )
        return;

    _cur_file.reset();
    throw std::ios_base::failure( "File '" + _base_fname +
                                  "' has not open or not good." );
}
//=======================================================================================
bool VOutFile_With_Rotate::is_open() const
{
    return _cur_file ? _cur_file->is_open() : false;
}
//=======================================================================================
ulong VOutFile_With_Rotate::size() const
{
    return _cur_file ? _cur_file->fast_size() : 0;
}
//=======================================================================================
void VOutFile_With_Rotate::write( const std::string &data )
{
    if ( !_cur_file ) return;

    _cur_file->write( data );

    if ( !_cur_file->is_open() || !_cur_file->is_good() )
    {
        throw std::ios_base::failure( "Error during write to file '"
                                      + _base_fname + "'." );
    }

    _cur_file->flush();

    if ( _cur_file->fast_size() >= _one_file_size )
        _rotate_and_reinit_file();
}
//=======================================================================================
// - закрыть базовый файл;
// - найти вакантную позицию;
// - переименовать файлы, заняв в.п.;
// - переименовать только что пользованный файл;
// - открыть базовый файл;
void VOutFile_With_Rotate::_rotate_and_reinit_file()
{
    //if ( _one_file_size <= 0 || _rotate_files_count <= 0 ) return;
    _cur_file.reset();

    uint vacant_pos = 1;
    while ( vacant_pos < _rotate_files_count )
    {
        vcat vacant_fname( _base_fname, '.', vacant_pos );
        if ( !VOutFile::exists(vacant_fname) )
            break;
        ++vacant_pos;
    }

    for ( auto i = vacant_pos - 1; i >= 1; --i )
    {
        vcat dst_name( _base_fname, '.', i + 1 );
        vcat src_name( _base_fname, '.', i );
        VOutFile::rename( src_name, dst_name );
    }

    auto first_dst = _base_fname + ".1";
    VOutFile::rename( _base_fname, first_dst );

    _reopen_file();
}
//=======================================================================================
