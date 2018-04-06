#ifndef VOUTFILE_H
#define VOUTFILE_H

#include <fstream>



//=======================================================================================
class VOutFile
{
public:

    enum class OpenMode { Truncate, Append };

    explicit VOutFile();
    VOutFile( const std::string &fname, OpenMode mode = OpenMode::Truncate );

    bool is_open()   const;
    long size()      const;
    bool is_good()   const;

    // Отличается от реального размера тем, что "не замечает" ошибок, т.е. если
    // были проблемы с записью, он будет врать.
    long fast_size() const;

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
    long          _fast_size = -1;
};
//=======================================================================================



#endif // VOUTFILE_H
