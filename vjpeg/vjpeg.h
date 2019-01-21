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


#ifndef VJPEG_H
#define VJPEG_H

#include "vimage.h"
#include "vstring.h"


//=======================================================================================
/*  02-04-2018 -- Wrapper for jpeglib.
 *
 *  jpeglib -- Сишная библиотека с вполне обычным для Си интерфейсом, похожим на
 *  массовую расчлененку. В итоге код обертки был скопипащен из Qt, и частично переделан.
 *  Оборачивать часть с чтением/декодированием в планы не входит.
 *
 *  Синтаксис вызовов сомнений в использовании вызывать не должен, в подавляющем
 *  большинстве случаев вызывайте с параметрами по умолчанию:
 *  auto jpg_res = VJpeg::save_to_buffer( img );
 *  bool ok = VJpeg::save_to_file( img, filename );
 *
 *
 *  Пара слов по параметрам вызова:
 *
 *  quality -- от 0 до 100, значение по умолчанию (75) вполне норм.
 *
 *  optimize -- пишут, что влияет на качество. По идее, может отображаться по мере
 *  закачки. Автор не заметил разницы ни по скорости работы, ни по качеству.
 *
 *  progressive -- метод кодирования, при котором при загрузке, сначала видна
 *  общая суть, потом проявляются подробности. Работает раза в четыре медленней.
*/
//=======================================================================================



//=======================================================================================
class VJpeg
{
public:
    //-----------------------------------------------------------------------------------
    enum _optimize    { Optimize, NotOptimize };
    enum _progressive { Progressive, Fast };
    //-----------------------------------------------------------------------------------
    static bool save_to_buffer( const VImage &img,
                                std::string *out,
                                int quality = 75,
                                _optimize optimize = Optimize,
                                _progressive = Fast );

    //-----------------------------------------------------------------------------------
    // throw error if can't do.
    static std::string save_to_buffer( const VImage &img,
                                       int quality = 75,
                                       _optimize optimize = Optimize,
                                       _progressive = Fast );
    //-----------------------------------------------------------------------------------
    static bool save_to_file( const VImage &img,
                              const std::string &fname,
                              int quality = 75,
                              _optimize optimize = Optimize,
                              _progressive = Fast );
    //-----------------------------------------------------------------------------------
};
//=======================================================================================


#endif // VJPEG_H
