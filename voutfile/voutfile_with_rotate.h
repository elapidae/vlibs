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


#ifndef VOUTFILE_WITH_ROTATE_H
#define VOUTFILE_WITH_ROTATE_H

#include "voutfile.h"
#include <memory>


//=======================================================================================
//  19.03.2018      VOutFile_WithRotate
//
//  Работает "хрупко", т.е. если будут к-л неприятности, сразу же будет брошено
//  исключение.
//=======================================================================================


//=======================================================================================
// [1]
// Базовое имя файла -- в него идет запись, по достижении размера, большего чем
// one_file_size, файл закрывается и переименовывается цепочка файлов от
// 'base_fname.rotate_files_count' до 'base_fname.1'
// Если one_file_size = 0 или rotate_files_count = 0, то ротация не производится.
class VOutFile_With_Rotate
{
public:
    VOutFile_With_Rotate();  // Пустой, данные игнорируются.

    VOutFile_With_Rotate( const std::string &base_fname,     // [1]
                          ulong one_file_size,               //
                          uint  rotate_files_count );        //


    bool is_open()  const;
    ulong size()    const;                  // Возвращает только предполагаемый размер.
    void write( const std::string &data );


private:
    std::string _base_fname;
    ulong       _one_file_size = 0;
    uint        _rotate_files_count = 0;

    void _reopen_file();
    void _rotate_and_reinit_file();

    std::shared_ptr<VOutFile> _cur_file;

    VOutFile_With_Rotate( const VOutFile_With_Rotate& ) = delete;
    VOutFile_With_Rotate& operator = ( const VOutFile_With_Rotate& ) = delete;
};
//=======================================================================================



#endif // VOUTFILE_WITH_ROTATE_H
