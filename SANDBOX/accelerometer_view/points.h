#ifndef POINTS_H
#define POINTS_H

#include <QList>


class points
{
public:
    static QList<double> xs();
    static QList<double> ys();
    static QList<double> zs();

    static QList<double> g_ys();
    static QList<double> g_zs();
};

#endif // POINTS_H
