#ifndef PATHSCANNER_H
#define PATHSCANNER_H

#include <QList>
#include <QFileInfo>

class PathScanner
{
public:
    static QFileInfoList scan( QString path );
    static QStringList clear_first_path( QString path, const QFileInfoList& list );
};

#endif // PATHSCANNER_H
