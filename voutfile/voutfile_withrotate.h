#ifndef VOUTFILE_WITHROTATE_H
#define VOUTFILE_WITHROTATE_H

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
// base_fname.rotate_files_count до base_fname.1.
// Если one_file_size = 0 или rotate_files_count = 0, то ротация не производится.
class VOutFile_WithRotate
{
public:
    VOutFile_WithRotate();  // Пустой, данные игнорируются.

    VOutFile_WithRotate( const std::string &base_fname,     // [1]
                         long one_file_size,                //
                         int  rotate_files_count );         //


    bool is_open()  const;
    long size()     const;                  // Возвращает только предполагаемый размер.
    void write( const std::string &data );


private:
    std::string _base_fname;
    long        _one_file_size = 0;
    int         _rotate_files_count = 0;

    void _reopen_file();
    void _rotate_and_reinit_file();

    std::shared_ptr<VOutFile> _cur_file;
};
//=======================================================================================



#endif // VOUTFILE_WITHROTATE_H
