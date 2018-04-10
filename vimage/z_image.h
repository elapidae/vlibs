#ifndef Z_IMAGE_H
#define Z_IMAGE_H

#include "ZCM_Image.hpp"
#include "vimage.h"



//=======================================================================================
class Z_Image : public VImage
{
public:

    static Z_Image copy_from( const VImage &src );

    Z_Image();
    Z_Image( ZCM_Image &&i );
    Z_Image( const ZCM_Image &i );

    virtual bool is_valid()         const override;

    virtual Format format()         const override;

    virtual int width()             const override;
    virtual int height()            const override;
    virtual int bytes_per_line()    const override;

    virtual const data_t* data()    const override;

    virtual void detach() override;

    const ZCM_Image & zcm_image() const;

private:
    ZCM_Image img;
};
//=======================================================================================



#endif // Z_IMAGE_H
