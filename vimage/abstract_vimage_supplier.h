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

    virtual ~Abstract_VImage_Supplier() = default;
    virtual void stop() = 0;
};


#endif // ABSTRACT_VIMAGE_SUPPLIER_H
