#include "pathscanner.h"

#include <QDir>


//=======================================================================================
static void process_path( const QString& path, QList<QFileInfo> *res )
{
    QDir dir( path );

    constexpr auto filter = QDir::Dirs           |
                            QDir::Files          |
                            QDir::NoDotAndDotDot |
                            QDir::NoSymLinks;

    const auto enties = dir.entryInfoList( filter, QDir::Name|QDir::DirsLast );
    for ( auto entry: enties )
    {
        res->append( entry );
        if ( entry.isDir() )
            process_path( entry.absoluteFilePath(), res );
    }
}
//=======================================================================================
QFileInfoList PathScanner::scan( QString path )
{
    QList<QFileInfo> res;
    process_path( path, &res );
    return res;
}
//=======================================================================================
QStringList PathScanner::clear_first_path( QString path, const QFileInfoList& list )
{
    const auto fpath = QFileInfo(path).absoluteFilePath();

    QStringList res;
    for ( auto &s: list )
    {
        auto p = s.absoluteFilePath();
        Q_ASSERT( p.startsWith(fpath) );
        res << p.right( p.count() - fpath.count() );
    }
    return res;
}
//=======================================================================================
