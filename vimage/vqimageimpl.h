#ifndef VQIMAGEIMPL_H
#define VQIMAGEIMPL_H

#include "vimage.h"
#include <QImage>


//=======================================================================================
class VQImageImpl final : public VImage
{
public:
    explicit VQImageImpl( QImage && img );
    explicit VQImageImpl( const QImage & img );

    virtual bool is_valid()                     const override;

    virtual VImage::Format format()             const override;

    virtual int width()                         const override;
    virtual int height()                        const override;
    virtual int bytes_per_line()                const override;

    virtual const VImage::data_t* data()        const override;
    virtual const VImage::data_t* line(int row) const override;

    virtual void detach()                             override;

    QImage &image();
    const QImage &image() const;



    VQImageImpl( VQImageImpl && ) = default;
    VQImageImpl( const VQImageImpl & ) = default;
    VQImageImpl& operator = ( VQImageImpl && ) = default;
    VQImageImpl& operator = ( const VQImageImpl & ) = default;

private:
    QImage img;
};
//=======================================================================================



#endif // VQIMAGEIMPL_H
