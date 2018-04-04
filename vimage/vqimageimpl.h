#ifndef VQIMAGEIMPL_H
#define VQIMAGEIMPL_H

#include "vimage.h"
#include <QImage>


//=======================================================================================
class VQImageImpl final : public VImage::Impl
{
public:
    static VImage::Impl_Ptr make( QImage && img );
    static VImage::Impl_Ptr make( const QImage & img );

    explicit VQImageImpl( QImage && img );
    explicit VQImageImpl( const QImage & img );

    virtual VImage::Format format()             const override;

    virtual int width()                         const override;
    virtual int height()                        const override;
    virtual int bytes_per_line()                const override;

    virtual const VImage::data_t* data()        const override;
    virtual const VImage::data_t* line(int row) const override;

    virtual VImage::Impl_Ptr copy()                   override;

    QImage &image();
    const QImage &image() const;

private:
    QImage img;
};
//=======================================================================================



#endif // VQIMAGEIMPL_H
