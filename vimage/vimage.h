#ifndef VIMAGE_H
#define VIMAGE_H

#include <string>

//=======================================================================================
/*  2018-04-11
 *  VImage -- адаптер для конвертации между классами разных систем, а именно:
 *  QImage, BaslerFrame, ZCM_Image, cv::Mat, etc.
 *
 *  Код, обрабатывающий, использующий картинки может принимать этот класс не задумываясь
 *  какая система предоставляет ему данные. Так действует, например, VJpeg.
 *
 *  Форматы картинок:
 *  Форматов представления картинкой как грязи, в каждой системе свое перечисление.
 *  В этом классе предполагается использовать минимальное количество форматов.
 *  Собственно, это черно-белый формат байт/пиксель, RGB три байта/пиксель,
 *  может быть в будущем будет введен формат RBG16(565) и то при условии жесткой
 *  необходимости. Пока неясно нужно ли вводить формат BGR для cv::Mat
 *
 *  Существуют планарные форматы, где компоненты отделены друг от друга. Такие форматы
 *  поддерживать не планируется.
*/
//=======================================================================================



//=======================================================================================
class VImage
{
public:
    using data_t = unsigned char;

    enum class Format
    {
        Invalid,
        Gray_8,
        RGB_888,
        BGR_888
    };

    static std::string format_to_string( Format f );
    static Format      string_to_format( const std::string &s );


    virtual ~VImage() = default;

    virtual Format format()         const = 0;

    virtual int width()             const = 0;
    virtual int height()            const = 0;
    virtual int bytes_per_line()    const = 0;

    virtual const data_t* data()    const = 0;

    virtual const data_t* line(int row) const; // return data() + row * bytes_per_line()

    virtual int data_size() const;      // NB! here returns bytes_per_line() * heigth()
                                        // If your system cut last row, override it!
};
//=======================================================================================



#endif // VIMAGE_H
