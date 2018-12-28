#pragma once
#ifndef VIMAGEWIDGET_H
#define VIMAGEWIDGET_H

#include <QGLWidget>
#include <QImage>

//=======================================================================================
class VImageWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit VImageWidget( QWidget *parent = nullptr );

signals:


public slots:
    /// Будет вызван detach() и repaint(), т.е. виджет автоматизирует отрисовку.
    void set_image( const QImage &img );

private:
    void paintEvent(QPaintEvent*) override;
    QImage _img;
};
//=======================================================================================


#endif // VIMAGEWIDGET_H
