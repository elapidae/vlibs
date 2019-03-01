#include <QApplication>

#include "vlog_qt.h"
#include "qcustomplot.h"
#include "vpoints.h"
#include "vinterval.h"


class Filter : public QObject
{
    double *step = nullptr;

public:
    Filter(double *step) : step(step) {}

    bool eventFilter( QObject *obj, QEvent *event )
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            vdeb << keyEvent->key() << keyEvent->text();

            if ( keyEvent->text() == "+" )
            {
                *step += 0.2;
                return true;
            }
            if ( keyEvent->text() == "-" )
            {
                *step -= 0.2;
                return true;
            }
            return false;
        }
        return QObject::eventFilter( obj, event );
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCustomPlot plot;
    plot.resize(1000,1000);
    plot.show();
    plot.setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                          QCP::iSelectLegend | QCP::iSelectPlottables );

    double step = 40;

    VPointF::Vector points
    {
        {1,1},
        {15,0.1},
        {30, 3},
        {45, -2.1},
        {60, -4.8},
        {75, -3},
        {90, 0.5},
        {105, 2.5},
    };

    VPointF checkpoint(77.5,-15);
    auto ggg = plot.addGraph();
    ggg->addData( checkpoint.x(), checkpoint.y() );
    ggg->setScatterStyle( QCPScatterStyle::ssCross );

    auto graph = plot.addGraph();
    graph->setPen( QPen(Qt::blue, 3.1) );
    for ( auto p: points )
    {
        graph->addData(p.x(), p.y());
        auto ell = new QCPItemEllipse( &plot );
        ell->setBrush( QColor(255,0,0,60) );
        //ell->setPen( Qt::NoPen );
        ell->topLeft->setCoords( p.x() - step/2, p.y() - step/2 );
        ell->bottomRight->setCoords( p.x() + step/2, p.y() + step/2 );

        if ( p.distance_to(checkpoint) < step/2)
            vdeb << "GOTCHA:" << p;
    }


    auto draw_line = [&](VPointF p1, VPointF p2)
    {
        auto line = new QCPItemLine( &plot );
        //line->setPen( QColor(0,0,0) );
        line->start->setCoords( p1.x(), p1.y() );
        line->end->setCoords  ( p2.x(), p2.y() );
    };
    auto draw_rect = [&](VPointF p1, VPointF p2, VPointF p3, VPointF p4)
    {
        draw_line(p1, p2);
        draw_line(p1, p3);
        draw_line(p1, p4);
        draw_line(p2, p3);
        draw_line(p2, p4);
        draw_line(p3, p4);
    };

    for ( auto it1 = points.begin(); it1 != points.end(); ++it1 )
    {
        auto it2 = it1 + 1;
        if ( it2 == points.end() ) break;

        auto p1 = *it1;
        auto p2 = *it2;

        VIntervalF i1(p1, p2);

        auto proj = i1.projection( checkpoint );
        if ( i1.in_rectangle(proj) )
            if ( proj.distance_to(checkpoint) <= step/2 )
                vdeb << "GOTCHA IN PROJ:" << proj;


        auto n11 = i1.normal_1( step/2 );
        auto n12 = i1.normal_2( step/2 );
        VIntervalF i2(p2, p1);
        auto n21 = i2.normal_1( step/2 );
        auto n22 = i2.normal_2( step/2 );

        draw_rect( n11.end_point(), n12.end_point(),
                   n21.end_point(), n22.end_point() );
    }

    //auto l1 = new QCPItemLine( &plot );
    //l1->start
    //rect->bottom


    plot.xAxis->setRange( -40, 120 );
    plot.yAxis->setRange( -80, 80  );
    //plot.rescaleAxes();
    plot.replot();

    return a.exec();
}
