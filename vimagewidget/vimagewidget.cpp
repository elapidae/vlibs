#include "vimagewidget.h"

#include <QPainter>


VImageWidget::VImageWidget(QWidget *parent)
    : QGLWidget(parent)
{}

void VImageWidget::set_image(const QImage &img_)
{
    _img = img_;
    _img.detach();
    repaint();
}

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
