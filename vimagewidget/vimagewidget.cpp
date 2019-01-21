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


#include "vimagewidget.h"

#include <QPainter>

//=======================================================================================
VImageWidget::VImageWidget(QWidget *parent)
    : QGLWidget(parent)
{}
//=======================================================================================
void VImageWidget::set_image(const QImage &img_)
{
    _img = img_;
    _img.detach();
    repaint();
}
//=======================================================================================
void VImageWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setBrush(Qt::gray);
    p.setPen(Qt::NoPen);
    p.drawRect(rect());

    if ( _img.isNull() ) return;

    auto rescaled = _img.scaled( size(), Qt::KeepAspectRatio );

    auto w = width()  - rescaled.width();
    auto h = height() - rescaled.height();

    p.drawImage( w/2, h/2, rescaled );
}
//=======================================================================================
