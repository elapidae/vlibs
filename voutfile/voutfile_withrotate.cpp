#include "voutfile_withrotate.h"

#include <assert.h>
#include "vcat.h"

// del it
#include <iostream>

//=======================================================================================
VOutFile_WithRotate::VOutFile_WithRotate()
{}
//=======================================================================================
VOutFile_WithRotate::VOutFile_WithRotate( const std::string &base_fname,
                                          long one_file_size,
                                          int rotate_files_count )
    : _base_fname         ( base_fname         )
    , _one_file_size      ( one_file_size      )
    , _rotate_files_count ( rotate_files_count )
{
    assert( _one_file_size      >= 0 );
    assert( _rotate_files_count >= 0 );

    _reopen_file();

    if ( _cur_file->fast_size() > _one_file_size )
        _rotate_and_reinit_file();
}
//=======================================================================================
void VOutFile_WithRotate::_reopen_file()
{
    //std::cout << "------- " << _base_fname << std::endl;
    _cur_file.reset( new VOutFile(_base_fname, VOutFile::OpenMode::Append) );

    if ( !_cur_file->is_open() || !_cur_file->is_good() )
    {
        throw std::ios_base::failure( vcat("File '", _base_fname,
                                           "' has not open or not good.") );
    }
}
//=======================================================================================
bool VOutFile_WithRotate::is_open() const
{
    return _cur_file ? _cur_file->is_open() : false;
}
//=======================================================================================
long VOutFile_WithRotate::size() const
{
    return _cur_file ? _cur_file->fast_size() : -1;
}
//=======================================================================================
void VOutFile_WithRotate::write( const std::string &data )
{
    if ( !_cur_file ) return;

    _cur_file->write( data );

    if ( !_cur_file->is_open() || !_cur_file->is_good() )
    {
        throw std::ios_base::failure( vcat("Error during write to file '",
                                           _base_fname, "'.") );
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
void VOutFile_WithRotate::_rotate_and_reinit_file()
{
    if ( _one_file_size <= 0 || _rotate_files_count <= 0 ) return;
    _cur_file.reset();

    int vacant_pos = 1;
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

    vcat first_dst( _base_fname, ".1" );
    VOutFile::rename( _base_fname, first_dst );

    _reopen_file();
}
//=======================================================================================
