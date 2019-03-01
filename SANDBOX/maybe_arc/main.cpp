#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableView>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //QObject::connect( &w, SIGNAL(sig()), &w, SLOT(simple_func()) );
    QObject::connect( &w, &MainWindow::sig, &w, &MainWindow::simple_func, Qt::QueuedConnection );
    w.sig();
    return a.exec();

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( "../maybe_arc/output_n.db" );
    bool ok = db.open();
    Q_ASSERT(ok);

    QSqlTableModel model;
    model.setTable( "GEO_POINT" );
    model.select();
    w.t1->setModel( &model );

    QSqlTableModel model2;
    model2.setTable( "GEO_LINE" );
    model2.select();
    w.t2->setModel( &model2 );
//    auto nodes = QSqlQuery("SELECT ID "
////                                "B.ID_GEO_POINT_START AS B_START_ID, "
////                                "A.ID_GEO_POINT_END   AS A_END_ID "
//                                "from GEO_LINE as A inner join GEO_LINE as B "
//                           "WHERE B.ID_GEO_POINT_START = A.ID_GEO_POINT_END ");
    //create temp view gl2 AS select * from geo_line
    ok = QSqlQuery("CREATE TEMP VIEW geo_line2 AS SELECT * from GEO_LINE").exec();
    //Q_ASSERT(ok);
//     trackid,
//     tracks.name,
//     albums.Title AS album,
//     media_types.Name AS media,
//     genres.Name AS genres
//    FROM
//     tracks
//    INNER JOIN albums ON Albums.AlbumId = tracks.AlbumId
//    INNER JOIN media_types ON media_types.MediaTypeId = tracks.MediaTypeId
//    INNER JOIN genres ON genres.GenreId = tracks.GenreId;

    auto nodes = QSqlQuery("SELECT "
                           "    geo_line.id, GEO_LINE.ID_GEO_POINT_START FROM GEO_LINE inner join geo_line2 ON geo_line2.id = geo_line.id");
    ok = nodes.exec();
    if (!ok)
    {
        qDebug() << nodes.lastError().text();
        Q_ASSERT(ok);
    }

    QSqlTableModel model3;
    model3.setTable( "RAILWAY_OBJ_SINGLE_SWITCH" );
    model3.select();
    w.t3->setModel( &model3 );


    return a.exec();
}
