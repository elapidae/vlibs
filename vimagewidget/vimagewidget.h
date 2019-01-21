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
