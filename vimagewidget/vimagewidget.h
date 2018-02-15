#pragma once
#ifndef VIMAGEWIDGET_H
#define VIMAGEWIDGET_H

#include <QGLWidget>
#include <QImage>

class VImageWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit VImageWidget( QWidget *parent = nullptr );

signals:

public slots:
    void set_image( const QImage &img );

private:
    void paintEvent(QPaintEvent*) override;
    QImage _img;
};

#endif // VIMAGEWIDGET_H
