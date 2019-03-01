#include <QApplication>

#include <QTimer>
#include "qcustomplot.h"
#include "vpoints.h"

#include "vlog_qt.h"
#include "p_sup.h"

class VCP_Lines
{
public:

};

QTimer *timer_ptr = nullptr;
bool started = true;

class SpaceFilter: public QObject
{
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        auto ke = dynamic_cast<QKeyEvent*>(event);
        if ( !ke || ke->text() != " " ) return false;

        if (started)    timer_ptr->stop();
        else            timer_ptr->start();

        started = !started;

        return true;
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCustomPlot plot;
    plot.show();
    plot.setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                          QCP::iSelectLegend | QCP::iSelectPlottables );
    plot.resize(1000,1000);

    auto graph = plot.addGraph();
//    graph->setLineStyle( QCPGraph::lsNone );
    graph->setScatterStyle( QCPScatterStyle::ssDisc );
    graph->setPen( QPen(Qt::blue) );

    auto g2 = plot.addGraph();
//    graph->setLineStyle( QCPGraph::lsNone );
    g2->setScatterStyle( {QCPScatterStyle::ssDisc, 15} );
    g2->setPen( QPen(Qt::red) );


    auto points = p_sup::pnts();
    auto it = points.begin();

    QTimer timer;
    timer.start(100);
    QObject::connect( &timer, &QTimer::timeout, [&]()
    {
        if ( it == points.end() )
        {
            timer.stop();
            return;
        }

        g2->data()->clear();
        g2->add_point( *it );

        graph->add_point( *it++ );


        if (graph->data()->size() > 150)
            graph->data()->remove( graph->data().get()->at(0)->key );
        plot.rescaleAxes();

        auto r = plot.xAxis->range();
        auto delta = (r.upper - r.lower) / 50;
        plot.xAxis->setRange( {r.lower - delta, r.upper + delta} );
        r = plot.yAxis->range();
        delta = (r.upper - r.lower) / 50;
        plot.yAxis->setRange( {r.lower - delta, r.upper + delta} );
        plot.replot();
    });
    SpaceFilter sfil;
    plot.installEventFilter( &sfil );
    timer_ptr = &timer;

    plot.replot();

    return app.exec();
}


/*

    VPointD p1, p2, p3;

    p1 = { 1, 1 };
    //p2 = { 4, 3 };
    p2 = { 7, 3 };
    p3 = { 6, 4 };

    auto v1 = p2 - p1;
    auto v2 = p3 - p2;

    auto a = v2 - v1;

    auto v3 = v2 + a;
    auto p4 = p3 + v3;

    auto dd = v2.distance() / v1.distance();

    auto da = (v2.angle() - v1.angle());
    da = v2.angle() + da;
    dd *= v2.distance();
    p4 = p3 + VPolarPointD( dd, da ).to_cartesian();

    //-----------------------------------------------------------------------------------
    auto Sgraph = plot.addGraph();
    //Sgraph->setLineStyle( QCPGraph::lsNone );
    Sgraph->setScatterStyle( QCPScatterStyle::ssDisc );
    Sgraph->setPen( QPen(Qt::gray) );

    Sgraph->add_point( p1 );
    Sgraph->add_point( p2 );
    Sgraph->add_point( p3 );
    Sgraph->add_point( p4 );
    //-----------------------------------------------------------------------------------
    auto Vgraph = plot.addGraph();
    //Vgraph->setLineStyle( QCPGraph::lsNone );
    Vgraph->setScatterStyle( QCPScatterStyle::ssDisc );
    Vgraph->setPen( QPen(Qt::blue) );

//    Vgraph->add_point( p1 + v1 );
//    Vgraph->add_point( p2 + v2 );
    //Vgraph->add_point( v1 );
    //Vgraph->add_point( v2 );
    //-----------------------------------------------------------------------------------
    auto Agraph = plot.addGraph();
    //Agraph->setLineStyle( QCPGraph::lsNone );
    Agraph->setScatterStyle( QCPScatterStyle::ssDisc );
    Agraph->setPen( QPen(Qt::red) );
    Agraph->add_point( VPointD{0,0} );
    //Agraph->add_point( p3 + a );
    //-----------------------------------------------------------------------------------
    vdeb << p1 << p2 << p3;
    vdeb << v1 << v2;
    vdeb << a;



    plot.xAxis->setRange(0, 10);
    plot.yAxis->setRange(0, 10);


*/
