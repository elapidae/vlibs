#ifndef SOURCEANALIZER_H
#define SOURCEANALIZER_H

#include <QFileInfo>
#include <QList>

class SourceAnalizer
{
public:
    using List = QList<SourceAnalizer>;

    explicit SourceAnalizer( const QFileInfo& finfo );
    explicit SourceAnalizer(); // empty
    void summ( const SourceAnalizer& other );

    static QStringList heap();
    QStringList as_list()  const;
    QString     as_brief() const;

    struct Lines
    {
        int all = 0;
        int comments = 0;
        int deep = 0;
        int max_len = 0;
        int max_deep = 0;
        int empties = 0;
    } lines;

    double avg_deep = 0;

    struct Symbols
    {
        int all = 0;
        //int start_spaces = 0;
        int spaces = 0;
        int tabs = 0;
        int four_spaces = 0;
    } symbols;

    struct Words
    {
        int _casts = 0;
        bool has_1251 = false;
        bool has_utf8 = false;
        int results = 0;
        int nss = 0;    // ::
        int logger = 0;
    } words;

    char prev_line_finished = 0;

    QFileInfo finfo;
};



#endif // SOURCEANALIZER_H
