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


#include "map2d_widget.h"

#include "vlogger.h"
#include <QDebug>
#include <QWheelEvent>

#define qtdeb qDebug() << __FILE__ << ":" << __LINE__ << " -- "



//=======================================================================================
QColor color_alpha(Qt::GlobalColor gc, int alpha)
{
    QColor c(gc);
    c.setAlpha(alpha);
    return c;
}
//=======================================================================================


//=======================================================================================
//      PAINTER SAVER
//=======================================================================================
PainterSaver::PainterSaver(QPainter *p_)
    : p(p_)
{
    p->save();
}
//=======================================================================================
PainterSaver::~PainterSaver()
{
    p->restore();
}
//=======================================================================================
//      PAINTER SAVER
//=======================================================================================



//=======================================================================================
//      Map2D_Widget
//=======================================================================================
Map2D_Widget::Map2D_Widget( QWidget *parent )
    : QGLWidget( parent )
{}
//=======================================================================================
void Map2D_Widget::set_black_std_preset()
{
    scene_topleft = QPointF(0,-20);
    scene_bottomright = QPointF(70, 20);
    clear_brush = Qt::black;

//    pen_grid_1m  = QPen( color_alpha(Qt::darkGray, 120), 1, Qt::DotLine);
//    pen_grid_5m  = QPen( color_alpha(Qt::darkGray, 130), 1.1);
//    pen_grid_10m = QPen( color_alpha(Qt::darkGray, 180), 1.2);
    pen_grid_1m  = QPen( color_alpha(Qt::green, 120), 1, Qt::DotLine);
    pen_grid_5m  = QPen( color_alpha(Qt::green, 130), 1.1);
    pen_grid_10m = QPen( color_alpha(Qt::green, 180), 1.2);

    pen_X_axis = QPen( color_alpha(Qt::white, 180), 2);
    pen_Y_axis = QPen( color_alpha(Qt::white, 180), 2);
}
//=======================================================================================
QPen Map2D_Widget::scaled_pen(QPen p) const
{
    p.setWidthF( p.widthF() / native_scale() );
    return p;
}
//=======================================================================================
void Map2D_Widget::set_zoom(float zoom)
{
    _zoom = zoom;
    repaint();
}
//=======================================================================================
void Map2D_Widget::set_shift(const QPointF &p)
{
    _shifting = p;
    repaint();
}
//=======================================================================================
void Map2D_Widget::paintEvent(QPaintEvent*)
{
    QPainter p( this );
    p.setRenderHint( QPainter::Antialiasing, render_hint );

    p.setBrush ( clear_brush );
    p.setPen   ( clear_pen   );
    p.drawRect ( rect() );

    p.setBrush ( entry_brush );
    p.setPen   ( entry_pen   );

    { PainterSaver saver( &p );
        pre_paint_on_me( &p, this );
    }

    { PainterSaver saver( &p );
        auto min_x = scene_topleft.x();
        auto min_y = scene_topleft.y();

        p.scale( native_scale(), -native_scale() );

        p.translate( -min_x, min_y );
        p.translate( _shifting_sum() );

        _paint_grid( &p );

        paint_on_me( &p, this );
    }

    post_paint_on_me( &p, this );
}
//=======================================================================================
void Map2D_Widget::_paint_one_grid( QPainter *p, float increment )
{
    auto min_x = scene_topleft.x();
    auto min_y = scene_topleft.y();
    auto max_x = scene_bottomright.x();
    auto max_y = scene_bottomright.y();

    for ( float x = 0; x <= max_x; x += increment )
        p->drawLine( QPointF(x, min_y), QPointF(x, max_y) );

    for ( float x = 0; x >= min_x; x -= increment )
        p->drawLine( QPointF(x, min_y), QPointF(x, max_y) );

    for ( float y = 0; y <= max_y; y += increment )
        p->drawLine( QPointF(min_x, y), QPointF(max_x, y) );

    for ( float y = 0; y >= min_y; y -= increment )
        p->drawLine( QPointF(min_x, y), QPointF(max_x, y) );
}
//=======================================================================================
void Map2D_Widget::_paint_grid(QPainter *p)
{
    if ( !need_paint_grid ) return;

    PainterSaver saver( p );

    p->setPen( scaled_pen(pen_grid_1m) );
    _paint_one_grid( p, 1 );

    p->setPen( scaled_pen(pen_grid_5m) );
    _paint_one_grid( p, 5 );

    p->setPen( scaled_pen(pen_grid_10m) );
    _paint_one_grid( p, 10 );

    auto min_x = scene_topleft.x();
    auto min_y = scene_topleft.y();
    auto max_x = scene_bottomright.x();
    auto max_y = scene_bottomright.y();

    p->setPen( scaled_pen(pen_X_axis) );
    p->drawLine( QPointF(min_x, 0), QPointF(max_x, 0) );

    p->setPen( scaled_pen(pen_Y_axis) );
    p->drawLine( QPointF(0, min_y), QPointF(0, max_y) );
}
//=======================================================================================

//=======================================================================================
void Map2D_Widget::mousePressEvent(QMouseEvent *event)
{
    _pressed_point = event->localPos();
    _moving_now = true;
}
//=======================================================================================
void Map2D_Widget::mouseReleaseEvent(QMouseEvent *)
{
    //qtdeb << event->localPos() << event->windowPos() << event->screenPos();
    auto sx = _shifting.x() + _move_shifting.x();
    auto sy = _shifting.y() + _move_shifting.y();

    _shifting = QPointF( sx, sy );
    _move_shifting = QPointF( 0, 0 );
    _moving_now = false;

    emit display_options_changed( _shifting_sum(), _zoom );
    repaint();
}
//=======================================================================================
void Map2D_Widget::mouseMoveEvent(QMouseEvent *event)
{
    if ( !_moving_now ) return;

    auto cur_pos = event->localPos();

    auto dx = cur_pos.x() - _pressed_point.x();
    auto dy = cur_pos.y() - _pressed_point.y();

    dy = -dy;   //NB! чтобы совместить по осям, Y ось вывернута наизнанку.

    dx /= native_scale();
    dy /= native_scale();

    _move_shifting = QPointF(dx, dy);
    emit display_options_changed( _shifting_sum(), _zoom );
    repaint();
}
//=======================================================================================
QPointF Map2D_Widget::_shifting_sum() const
{
    return QPointF( _shifting.x() + _move_shifting.x(),
                    _shifting.y() + _move_shifting.y() );
}
//=======================================================================================
void Map2D_Widget::wheelEvent(QWheelEvent *ev)
{
    //constexpr auto k = 0.025;
    constexpr auto k = 0.08;
    _zoom *= ev->delta() > 0 ? (1 + k) : (1 - k);
    _zoom = qMax(_zoom, 1.f);

    emit display_options_changed( _shifting_sum(), _zoom );
    repaint();
}
//=======================================================================================
float Map2D_Widget::native_scale() const
{
    auto x_scale = width()  / x_len();
    auto y_scale = height() / y_len();
    auto min_scale = qMin(x_scale, y_scale);

    return min_scale * _zoom;
}
//=======================================================================================
//      Map2D_Widget
//=======================================================================================


//float w = width();
//float h = height();

////===============================================================================
//// Найти минимальные значения для будущих координат
////float xmin = numeric_limits<float>::max();
//float ymin = numeric_limits<float>::max();
//float xmax = numeric_limits<float>::min();
//float ymax = numeric_limits<float>::min();
//for( auto p:points )
//{
//    xmax = qMax(xmax, p.x);
//    ymax = qMax(ymax, p.y);
//    //xmin = qMin(xmin, p.x);
//    ymin = qMin(ymin, p.y);
//}

////scale
//xmax = 71;
//// выбор значения захвата по вертикали.
//auto xscale = w / xmax;

//auto hmm = qMax( qAbs(ymin), qAbs(ymax) );
//hmm = 30;
//auto yscale = h / (hmm * 2);

//auto scale_factor = qMin(xscale, yscale);
////p.scale( xscale, yscale );
//p.scale( scale_factor, scale_factor );
//p.scale( _zoom, _zoom );

//p.translate( 0, hmm );
//p.translate( _dx, _dy );



//    // прибивка в верхнему левом
//    auto cur_shift_x = _shifting.x() + dx;
//    if (cur_shift_x > 0)
//        dx -= cur_shift_x;

//    auto cur_shift_y = _shifting.y() + dy;
//    if (cur_shift_y > 0)
//        dy -= cur_shift_y;

//    cur_shift_x = _shifting.x() + dx;
//    if (cur_shift_x > -win_x_resolution())
//        dx -= cur_shift_x;

    //auto poss_min_shift_x = cur_shift_x - win_x_resolution() / 2.f;

//    vdeb(vlog("dx", dx, ", cur shift x:", cur_shift_x)
//             (", win_x_res:", win_x_resolution() ) );

    //dx = qMax( dx, poss_min_shift_x );


//    qtdeb << "delta:" << ev->delta()
//          << ", adelta:" << ev->angleDelta()
    //          << ", posf" << ev->posF();
