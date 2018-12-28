#ifndef VIMAGE_H
#define VIMAGE_H

#include "vimage.h"
#include "baslerframe.h"


//=======================================================================================
class VImage_BaslerRef_Impl : public VImage
{
public:

    static VImage::Format baslerFormat_to_format( BaslerPicFormat f );

    VImage_BaslerRef_Impl( const BaslerFrame *frame_ );

    virtual bool is_valid()         const override;

    virtual Format format()         const override;

    virtual int width()             const override;
    virtual int height()            const override;
    virtual int bytes_per_line()    const override;

    virtual const data_t* data()    const override;

    virtual void detach() override;

private:
     const BaslerFrame * const _frame;
};
//=======================================================================================



#endif // VIMAGE_H
