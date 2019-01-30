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
