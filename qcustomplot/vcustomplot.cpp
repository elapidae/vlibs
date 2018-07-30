#include "vcustomplot.h"

//=======================================================================================

QColor VCustomPlot::rand_color(int from, int to, int a)
{
    Q_ASSERT(from <= to);
    auto diff = to - from;

    auto r = from + qrand() % diff;
    auto g = from + qrand() % diff;
    auto b = from + qrand() % diff;

    return QColor( r, g, b, a );
}
//=======================================================================================

VCustomPlot::VCustomPlot(QWidget *parent)
    : QCustomPlot(parent)
    , _img_top_left     ( ImagePos::TopLeft     )
    , _img_top_right    ( ImagePos::TopRight    )
    , _img_bottom_left  ( ImagePos::BottomLeft  )
    , _img_bottom_right ( ImagePos::BottomRight )
{
    setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );
}

//=======================================================================================

void VCustomPlot::v_plot_image( const QImage &img, ImagePos pos, qreal scale )
{
    Q_ASSERT( scale >= 0 && scale <= 1 );

    _image_paint *pimg = nullptr;
    switch ( pos )
    {
    case ImagePos::TopLeft:     pimg = &_img_top_left;      break;
    case ImagePos::TopRight:    pimg = &_img_top_right;     break;
    case ImagePos::BottomLeft:  pimg = &_img_bottom_left;   break;
    case ImagePos::BottomRight: pimg = &_img_bottom_right;  break;
    }
    Q_ASSERT( pimg );

    pimg->img   = img;
    pimg->scale = scale;

    repaint();
}

//=======================================================================================

//void VCustomPlot::v_plot_image_simple(const QImage &img)
//{
//    v_plot_image( img, ImagePos::TopRight, 0.3 );
//}

//=======================================================================================

void VCustomPlot::paintEvent( QPaintEvent *pe )
{
    QCustomPlot::paintEvent( pe );

    QPainter painter( this );
    _paint_img( &painter, _img_top_left     );
    _paint_img( &painter, _img_top_right    );
    _paint_img( &painter, _img_bottom_left  );
    _paint_img( &painter, _img_bottom_right );
}

//=======================================================================================

void VCustomPlot::_paint_img( QPainter *painter, const VCustomPlot::_image_paint &pimg )
{
    if ( pimg.img.isNull() || pimg.scale <= 0 )
        return;

    int sw = static_cast<int>( width()  * pimg.scale );
    int sh = static_cast<int>( height() * pimg.scale );

    auto scaled_img = pimg.img.scaled( sw, sh, Qt::KeepAspectRatio );

    auto is_left = pimg.pos == ImagePos::TopLeft || pimg.pos == ImagePos::BottomLeft;
    auto is_top  = pimg.pos == ImagePos::TopLeft || pimg.pos == ImagePos::TopRight;

    auto left = is_left ? 3 : width()  - scaled_img.width()  - 3;
    auto top  = is_top  ? 3 : height() - scaled_img.height() - 3;

    painter->drawImage( QPoint(left,top), scaled_img );
}
//=======================================================================================

//void VCustomPlot::_paint_img()
//{
//    if (_img.isNull() || _img_scale <= 0)
//        return;

//    int sw = static_cast<int>( width()  * _img_scale );
//    int sh = static_cast<int>( height() * _img_scale );

//    auto img = _img.scaled(sw, sh, Qt::KeepAspectRatio);

//    auto is_left = _img_pos == ImagePos::TopLeft || _img_pos == ImagePos::BottomLeft;
//    auto is_top  = _img_pos == ImagePos::TopLeft || _img_pos == ImagePos::TopRight;

//    auto left = is_left ? 0 : width()  - img.width();
//    auto top  = is_top  ? 0 : height() - img.height();

//    QPainter p(this);
//    p.drawImage( QPoint(left,top), img );
//}

//=======================================================================================

//=======================================================================================
void VCustomPlot::v_add_graph_group( std::string group_name,
                                   Graph_Tuner tuner )
{
    Q_ASSERT( !_graph_groups.contains(group_name) );

    _graph_group gg;
    gg.tuner = tuner;
    gg.cur_graph = gg.graphs.end();

    _graph_groups.insert( group_name, gg );

}
//=======================================================================================
void VCustomPlot::v_clear_graph_group( std::string group_name )
{
    Q_ASSERT( _graph_groups.contains(group_name) );

    auto && gg = _graph_groups[group_name];
    for ( auto g: gg.graphs )
    {
        g->data()->clear();
    }

    gg.cur_graph = gg.graphs.begin();
}
//=======================================================================================
QCPGraph *VCustomPlot::v_next_graph( std::string group_name )
{
    Q_ASSERT( _graph_groups.contains(group_name) );

    auto && gg = _graph_groups[group_name];

    if ( gg.cur_graph != gg.graphs.end() )
    {
        return *gg.cur_graph++;
    }

    // need to add the graph...
    auto *g = addGraph();

    if ( gg.tuner )
        gg.tuner( g );

    gg.graphs.push_back( g );
    gg.cur_graph = gg.graphs.end();

    return g;
}
//=======================================================================================
