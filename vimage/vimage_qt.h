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


#ifndef VIMAGE_QT_H
#define VIMAGE_QT_H

#include <QImage>
#include "vimage.h"


class VImage_Qt final : public VImage
{
public:

    static QImage::Format format_to_QImageFormat( Format f );
    static Format qImageFormat_to_format( QImage::Format f );

    static QImage convert( const VImage &other );

    // UPD: Нельзя забирать по const-ссылке, т.к. смогут запихать временный объект,
    // а мы есть обертка...
    VImage_Qt( const QImage *img );

    virtual Format format()         const override;

    virtual int width()             const override;
    virtual int height()            const override;
    virtual int bytes_per_line()    const override;

    virtual const data_t* data()    const override;

    virtual const data_t* line(int row) const override;

    virtual int data_size() const override;

private:
    const QImage *_img;
};



#endif // VIMAGE_QT_H
