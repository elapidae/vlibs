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


#ifndef VOUTFILE_H
#define VOUTFILE_H

#include <fstream>



//=======================================================================================
class VOutFile
{
public:

    enum class OpenMode { Truncate, Append };

    //explicit VOutFile();
    VOutFile( const std::string &fname, OpenMode mode = OpenMode::Truncate );

    bool is_open()   const;
    long size()      const;
    bool is_good()   const;

    // Отличается от реального размера тем, что "не замечает" ошибок, т.е. если
    // были проблемы с записью, он будет врать.
    ulong fast_size() const;

    const std::string filename() const;

    void write( const std::string &data );
    void flush();

    bool rename( const std::string &to );

    // Обертка к std::rename. Метод не совсем на месте, переименование файлов не
    // только задача записывающего файла, но пока пусть лежит здесь.
    static bool rename( const std::string &from, const std::string &to );
    // То же не на месте, таково пока в стандарте вообще нету, поэтому сделано костылем.
    static bool exists( const std::string &fname );

private:
    std::ofstream _s;
    std::string   _fname;
    ulong         _fast_size = 0;
};
//=======================================================================================



#endif // VOUTFILE_H
