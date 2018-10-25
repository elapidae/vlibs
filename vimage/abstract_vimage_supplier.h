#ifndef ABSTRACT_VIMAGE_SUPPLIER_H
#define ABSTRACT_VIMAGE_SUPPLIER_H

//=======================================================================================
/*  24-09-2018       by Elapidae
 *
 *  class Abstract_VImage_Supplier введен для того, чтобы постараться свести разных
 *  поставщиков видео потоков в единое "русло".
 *
 *  Т.е. есть расчет, чтобы, например, для RTP потока не было особой разницы с какого
 *  источника кадры получаются.
*/
//=======================================================================================

#include "vimage.h"
#include "vsignal.h"
#include "vtimepoint.h"
#include <memory>

class Abstract_VImage_Supplier
{
public:
    using SPtr = std::shared_ptr<Abstract_VImage_Supplier>;

    VSignal<VImage,VTimePoint> received;

    virtual ~Abstract_VImage_Supplier() {}
    virtual void stop() = 0;
};


#endif // ABSTRACT_VIMAGE_SUPPLIER_H
