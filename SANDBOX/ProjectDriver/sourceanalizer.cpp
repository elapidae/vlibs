#include "sourceanalizer.h"

#include "verror.h"
#include "vlog_qt.h"
#include <QFile>
#include <QTextStream>


//=======================================================================================
QStringList SourceAnalizer::heap()
{
    return QStringList() << "fname"

                         << "Lines_All"
                         << "Lines_comm"
                         << "Lines_max_len"

                         << "All symbols"
                         << "Spaces/4"
                         << "Tabs"

                         << "Max deep"
                         //<< "Avg deep"

                         << "casts"
                         << "codepage"
                         << "result"
                         << "::"
                         << "logger"
                        ;
}
//=======================================================================================
QStringList SourceAnalizer::as_list() const
{
    auto codepage = words.has_1251 ? "CP-1251 WTF?"
                                   : words.has_utf8 ? "UTF-8"
                                                    : "ASCII";
    enum {fwidht = 6};
    return QStringList() << QString("%1").arg( finfo.absoluteFilePath() )

                         << QString("%1").arg( lines.all,       fwidht )
                         << QString("%1").arg( lines.comments,  fwidht )
                         << QString("%1").arg( lines.max_len,   fwidht )

                         << QString("%1").arg( symbols.all,         fwidht )
                         << QString("%1").arg( symbols.four_spaces, fwidht )
                         << QString("%1").arg( symbols.tabs,        fwidht )

                         << QString("%1").arg( lines.max_deep,  fwidht )
                        // << QString("%1").arg( avg_deep, fwidht,'f', 3 )

                         << QString("%1").arg( words._casts,    fwidht )
                         << QString("%1").arg( codepage )
                         << QString("%1").arg( words.results,   fwidht )
                         << QString("%1").arg( words.nss,       fwidht )
                         << QString("%1").arg( words.logger,   fwidht )
                            ;
}
//=======================================================================================
QString SourceAnalizer::as_brief() const
{
    return QString("Total lines:%1 "
                   "Comment lines:%2 "
                   "Max line len:%3 "

                   "Symbols total:%4 "
                   "Spaces/4:%5 "
                   "Tabs: %6 "
                   "*_cast:%7 "
                   "logger:%8"
                   )

                    .arg( lines.all        )
                    .arg( lines.comments   )
                    .arg( lines.max_len    )

                    .arg( symbols.all      )
                    .arg( symbols.four_spaces )
                    .arg( symbols.tabs )

                    .arg( words._casts    )
                    .arg( words.logger    )
            ;
}
//=======================================================================================

static bool is_cp1251( const QByteArray& data, bool *has_utf8 )
{
    *has_utf8 = false;
    int utfs = 0;
    for ( char ch: data )
    {
        if (utfs)
        {
            *has_utf8 = true;

            // must begins as 0x10xx
            if ( (ch & 0xC0) != 0x80 )
                return true;

            --utfs;
            continue;
        }

        if ( (ch & 0x80) == 0 ) continue;

        if ( (ch & 0xF8) == 0xF0 ) { utfs = 3; continue; }  //  11110xxx
        if ( (ch & 0xF0) == 0xE0 ) { utfs = 2; continue; }  //  1110xxxx
        if ( (ch & 0xE0) == 0xC0 ) { utfs = 1; continue; }  //  110xxxxx

        return true;
    }
    return false;
}
//=======================================================================================
static bool is_splitted( const QString& l2, char prev_fin )
{
    if (l2.startsWith("const ") && l2.endsWith(";")) return true;
    if (l2.startsWith("const ") && l2.endsWith(",")) return true;
    if (l2.startsWith("const ") && l2.endsWith(")")) return true;
    if (l2.startsWith("->"))                return true;
    if (l2.startsWith("//"))                return true;
    if (l2.startsWith("*"))                 return true;
    if (l2.startsWith("typename"))          return true;
    if (l2.startsWith("\""))                return true;
    if (l2.startsWith("$"))                 return true;
    if (l2.startsWith("-l"))                return true;
    if (l2.startsWith(")"))                 return true;
    if (l2.startsWith("self->"))            return true;
    if (l2.startsWith("#"))                 return true;
    if (l2.startsWith("."))                 return true;
    if (l2.startsWith("("))                 return true;
    if (l2.startsWith("<<"))                return true;
    if (prev_fin == ',')                    return true;
    if (prev_fin == '\\')                   return true;
    if (l2.endsWith("||"))                  return true;
    if (l2.startsWith("__nonnull"))         return true;
    if (l2.startsWith("__THROW"))           return true;

    return false;
}
//=======================================================================================
static int st_spaces_count( const QByteArray& line_ba )
{
    auto fit = std::find_if_not( line_ba.begin(), line_ba.end(), [](char ch)
    {
        return ch == ' ';
    });
    return fit - line_ba.begin(); // std::distance(line_ba.begin(), fit);
}
//=======================================================================================
static void parse_line( const QByteArray& line_ba, SourceAnalizer *res, bool trap )
{
    QString line( line_ba );

    while (!line.isEmpty() && line.back() == '\n') line.chop(1);
    while (!line.isEmpty() && line.back() == '\r') line.chop(1);

    if (trap && line.size() > 89)
        vdeb << "TRAPPED:" << line;

    bool utf8;
    bool cp1251 = is_cp1251( line_ba, &utf8 );
    res->words.has_1251 = res->words.has_1251 || cp1251;
    res->words.has_utf8 = res->words.has_utf8 || utf8;

    res->lines.max_len = std::max( res->lines.max_len, line.size() );
    ++res->lines.all;
    res->symbols.all += line.size();

    res->words.results += line.toLower().count("result");
    res->words.nss += line.count("::");

    auto l2 = line.trimmed();
    auto llow = l2.toLower();
    res->words.logger += llow.count("logger");

    //if (l2.count("::") >= 4) vtrace << l2;
    if (l2.count("<") >= 4) vtrace << l2;

    res->symbols.spaces += line.size() - l2.size();
    res->symbols.four_spaces += st_spaces_count(line_ba) / 4;
    res->lines.empties  += l2.isEmpty() ? 0 : 1;


    if ( l2.startsWith("//") )
        ++res->lines.comments;

    // попытка быстро понять, что в строке забой предыдущей команды.

    // start spaces...
    int start_spaces = 0;
    for ( auto ch: line )
    {
        if (ch == '\t')
        {
            ++res->symbols.tabs;
            while ( ++start_spaces % 4 );
            continue;
        }
        if ( ch.isSpace() && ch != ' '&& ch != '\r' ) throw verror.hex() << ch.unicode();
        if (ch != ' ') break;
        ++start_spaces;
    }
    auto splitted = is_splitted( l2, res->prev_line_finished );
    while ( !splitted && start_spaces % 4 )
    {
        ++start_spaces;
        static int cnt  = 0;
        //vdeb << start_spaces << "not aligned" << ++cnt << line;
    }
    int deep = splitted ? 1 : start_spaces / 4;

    res->lines.deep += ( deep );
    res->lines.max_deep = std::max( res->lines.max_deep, deep );

    if ( !l2.isEmpty() )
        res->prev_line_finished = l2.back().toLatin1();

    if ( line.contains("_cast") )
        ++res->words._casts;
}
//=======================================================================================

//=======================================================================================
SourceAnalizer::SourceAnalizer(const QFileInfo &finfo_ )
    : finfo( finfo_ )
{
    QFile f( finfo_.absoluteFilePath() );
    if ( !f.open(QIODevice::ReadOnly) )
        throw verror << "Cannot open " << finfo.absoluteFilePath();

    //vtrace << finfo_.absoluteFilePath();
    int line = 1;
    while ( !f.atEnd() )
    {
        parse_line( f.readLine(), this, finfo.fileName() == "vhdlc.h" );
        ++line;
    }

    auto filled_lines = lines.all - lines.empties;
    avg_deep = filled_lines == 0 ? 0 : double(lines.deep) / filled_lines;
}
//=======================================================================================
SourceAnalizer::SourceAnalizer()
{}
//=======================================================================================
void SourceAnalizer::summ( const SourceAnalizer& other )
{
    Q_ASSERT( finfo.absoluteFilePath().isEmpty() );

    lines.all       += other.lines.all;
    lines.comments  += other.lines.comments;
    lines.max_len = std::max( lines.max_len, other.lines.max_len );

    symbols.all         += other.symbols.all;
    symbols.spaces      += other.symbols.spaces;
    symbols.tabs        += other.symbols.tabs;
    symbols.four_spaces += other.symbols.four_spaces;

    words._casts    += other.words._casts;
    words.results   += other.words.results;
    words.logger    += other.words.logger;
}
//=======================================================================================


