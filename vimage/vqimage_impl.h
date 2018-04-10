#ifndef VQIMAGEIMPL_H
#define VQIMAGEIMPL_H

#include "vimage.h"
#include <QImage>


//=======================================================================================
class VQImage_Impl final : public VImage
{
public:
    static QImage::Format format_to_QImageFormat( Format f );
    static Format qImageFormat_to_format( QImage::Format f );


    static VQImage_Impl copy_from( const VImage &src );

    VQImage_Impl( QImage && img );
    VQImage_Impl( const QImage & img );

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



    VQImage_Impl( VQImage_Impl && ) = default;
    VQImage_Impl( const VQImage_Impl & ) = default;
    VQImage_Impl& operator = ( VQImage_Impl && ) = default;
    VQImage_Impl& operator = ( const VQImage_Impl & ) = default;

private:
    QImage img;
};
//=======================================================================================



#endif // VQIMAGEIMPL_H
