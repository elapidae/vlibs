#ifndef VCUSTOMPLOT_H
#define VCUSTOMPLOT_H

#include "qcustomplot.h"


//=======================================================================================

class VCustomPlot : public QCustomPlot
{
    Q_OBJECT
public:

    static QColor rand_color(int from = 0, int to = 255, int a = 255);

    explicit VCustomPlot(QWidget *parent = nullptr);


    enum class ImagePos { TopLeft, TopRight, BottomLeft, BottomRight };

public slots:
    void v_plot_image( const QImage &img, ImagePos pos, qreal scale );


public:
    using Graph_Tuner = std::function<void(QCPGraph*)>;
    void v_add_graph_group( std::string group_name, Graph_Tuner tuner = nullptr );
    void v_clear_graph_group( std::string group_name );
    // Добавляет и настраивает новый, если надо.
    QCPGraph * v_next_graph( std::string group_name );


private:
    struct _graph_group
    {
        Graph_Tuner tuner;
        std::vector<QCPGraph*> graphs;
        std::vector<QCPGraph*>::iterator cur_graph;
    };
    QMap<std::string,_graph_group> _graph_groups;


private:
    void paintEvent(QPaintEvent*) override;

    struct _image_paint
    {
        explicit _image_paint( ImagePos p ) : pos(p) {}
        const ImagePos pos;

        qreal    scale = 0;
        QImage   img;
    }
    _img_top_left,
    _img_top_right,
    _img_bottom_left,
    _img_bottom_right;

    void _paint_img( QPainter *painter, const _image_paint &pimg );
};

//=======================================================================================


#endif // VCUSTOMPLOT_H
