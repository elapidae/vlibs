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


#ifndef VIMAGE_H
#define VIMAGE_H

#include <string>

//=======================================================================================
/*
 *  2018-04-11, UPD 2018-05-22
 *
 *  -------------------------------------------------------------------------------------
 *
 *  VImage -- адаптер для конвертации между классами разных библиотек, фреймворков,
 *  систем, а именно: QImage, BaslerFrame, ZCM_Image, cv::Mat, etc.
 *
 *  Код, обрабатывающий, использующий картинки может принимать этот класс не задумываясь
 *  какая система предоставляет ему данные. Так действует, например, VJpeg.
 *
 *  Также можно конвертировать картинки любых типов между собой.
 *
 *  Предполагается использовать так:
 *  [ пусть есть классы VImage_Qt, VImage_Basler, VImage_ZCM, VImage_Cv,
 *    все наследники от VImage ]
 *
 *      auto basler_frame = camera->get_frame();     // картинка в формате камеры Basler.
 *      VImage_Basler vbasler( basler_frame );       // захватили на адаптацию.
 *      auto qimage = VImage_Qt::convert( vbasler ); // адаптировали.
 *      some_widget->show( qimage );                 // QImage -- родной тип для Qt.
 *
 *      print_some_info( &qimage );                  // пусть изменили картинку.
 *      VImage_Qt vimg2( qimage  );                  // захватили измененную.
 *      auto zimage = VImage_ZCM::convert( vimg2 );  // адаптировали для передачи.
 *      zcm.send( zimage );                          // отправили по сети.
 *
 *      ... // на другой машине:
 *      auto zimage = zcm->get();                    // условный прием zcm сообщения.
 *      VImage_ZCM vimage( zimage );                 // также захватили для адаптации.
 *      jpeg::save( vimage );                        // сжатие не зависит от фреймворка.
 *
 *      auto qimage = VImage_Qt::convert( vimage );  // адаптируем
 *      some_widget->show( qimage );                 // и используем.
 *
 *      auto cvimg = VImage_Cv::convert( vimage );   // адаптируем
 *      auto track = track_detect( cvimg );          // и используем.
 *
 *  -------------------------------------------------------------------------------------
 *
 *  Форматы картинок:
 *  Форматов представления картинкой как грязи, в каждой системе свое перечисление.
 *  В этом классе предполагается использовать минимальное количество форматов.
 *  Собственно, это черно-белый формат байт/пиксель, RGB три байта/пиксель,
 *  может быть в будущем будет введен формат RBG16(565) и то при условии жесткой
 *  необходимости. Пока неясно нужно ли вводить формат BGR для cv::Mat
 *
 *  Существуют планарные форматы, где компоненты отделены друг от друга. 
 *  UPD 26.12.2018 планируется использовать, как минимум, YUV форматы (420/422). 
 *  В подавляющем большинстве в них транслируется видео.
 *
 *  -------------------------------------------------------------------------------------
 *
 *  Убедительная просьба -- при наследовании следующие правила считать
 *  непременными к исполнению!
 *  [ пусть DstImage   -- целевой класс, представляющий картинку;
 *          VImage_Dst -- наследованный от VImage класс-адаптер; ]
 *
 *  При реализации конвертора для картинки DstImage следует:
 *
 *  0. Наследники адаптеры называются VImage_<Dst>, где <Dst> -- описательное название
 *     фреймворка/библиотеки адаптируемой картинки.
 *     Примеры названий см. в псевдокоде демонстрации использования.
 *
 *  1. сделать статический метод convert, принимающий VImage и возвращающий
 *     целевой класс:
 *          static DstImage convert( const VImage &other );
 *
 *  2. сделать конструктор, принимающий и захватывающий константную ссылку на DstImage.
 *     Захват константной ссылки закроет возможности копирования, нам это и надо.
 *          public:  [explicit] VImage_Dst( const DstImage &img ) : _img( img ) {}
 *          private: const DstImage & _img;
 *
 *  3. перегрузить все чисто виртуальные методы.
 *     NB! Обязательно перепроверьте как ваш формат хранит последнюю строку, если надо,
 *     перегрузите метод data_size()! Перегрузите метод line() если это целесообразно.
 *
 *  -------------------------------------------------------------------------------------
 *
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

    /// то же что и data_size(), только беззнаковое.
    uint data_usize() const;
};
//=======================================================================================

#endif // VIMAGE_H
