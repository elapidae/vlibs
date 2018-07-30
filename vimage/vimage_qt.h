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
