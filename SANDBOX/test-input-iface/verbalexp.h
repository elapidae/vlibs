#ifndef VERBALEXP_H
#define VERBALEXP_H

#include <QString>

class VerbalExp
{
public:
    VerbalExp();

    //virtual bool match() const = 0;
    virtual QString regexp() const = 0;
};


class VExp_Diap : public VerbalExp
{
    QString from;
    QString to;

public:
    VExp_Diap( QChar from_, QChar to_ ) : from(from_), to(to_)
    {
        if (from == "\\") from = "\\\\";
        if (to   == "\\") to   = "\\\\";
    }

    QString regexp() const { return QString("[%1-%2]").arg(from).arg(to); }

    //bool match() const {  }
};


#endif // VERBALEXP_H
