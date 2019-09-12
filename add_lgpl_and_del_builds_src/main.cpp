/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#include <QApplication>

#include <QDir>
#include <QHeaderView>
#include <QTextStream>
#include <QTableWidget>
#include "vlog_qt.h"
#include "verror.h"
#include "vgit.h"
#include "tables_form.h"
#include <iostream>

//=======================================================================================
static const QByteArray start_plus_line =
"/**************************************************************************************"
"**\n";
static const QByteArray end_plus_line =
"***************************************************************************************"
"*/\n";
//=======================================================================================
static const QByteArray start_build_line =
"#######################################################################################"
"##\n";
static const QByteArray end_build_line = start_build_line;
//=======================================================================================
static QByteArray plus_licence;    // Текст для вставки в плюсовые файлы
static QByteArray build_licence;   // Для вставки в pri & cmake файлы
static void prepare_licences();
//=======================================================================================
static Tables_Form *tables_form = nullptr;
//=======================================================================================
static void append_log_removed( const QString& path )
{
    Q_ASSERT( tables_form );
    tables_form->append_all_and_diff( path, "REMOVED", Qt::black, Qt::red );
}
//=======================================================================================
static void append_log_excluded( const QString& path )
{
    Q_ASSERT( tables_form );
    tables_form->append_all_only( path, "EXCLUDED", Qt::yellow, Qt::blue );
}
//=======================================================================================


//=======================================================================================
static void _process_licence_file( const QString& fname,
                                   const QByteArray& start_line,
                                   const QByteArray& licence );
//=======================================================================================
void process_plus_file( const QString& fname )
{
    _process_licence_file( fname, start_plus_line, plus_licence );
}
//=======================================================================================
void process_build_file( const QString& fname )
{
    _process_licence_file( fname, start_build_line, build_licence );
}
//=======================================================================================
void process_entry( const QFileInfo& info )
{
    vdeb << "entry:" << info.absoluteFilePath() << info.fileName();
    const auto abs_name = info.absoluteFilePath();
    const auto rel_name = info.fileName();
    const auto suffix = info.suffix();

    //-----------------------------------------------------------------------------------
    // text files -- exclude
    if ( rel_name.contains("LICENSE")               ||
         rel_name.toUpper().startsWith("README")    ||
         suffix == "txt"                            ||
         suffix == "sh"                             ||          //  Scripts
         suffix == "qrc"                            ||          //  Qt resources
         suffix == "pro"                            ||          //  Qt projects
         suffix == "ui"                             ||          //  Qt forms
         suffix == "qdoc"                           ||          //  Qt docs
         suffix == "png"                            ||          //
         suffix == "conf"                           ||          //
         suffix == "so"                             ||          //
         suffix == "py"                             ||          //
         suffix == "zcm"                            ||          //
         rel_name == "CMakeLists.txt"               ||          //  cmake projects
         rel_name == "add_lgpl_and_del_builds"      ||          //  self $)
         rel_name.startsWith("qcustomplot")         ||
         rel_name.startsWith("sqlite3pp")           ||
         abs_name.contains("/omit_it/")             ||
         rel_name.contains("changes")               ||
         abs_name.contains("/qtserialport/")                // about to copy-paste
       )
    {
        append_log_excluded( abs_name );
        return;
    }
    //-----------------------------------------------------------------------------------
    // dirty builds property
    if ( suffix == "o"                                              ||
         rel_name == "Makefile"                                     ||
         rel_name.contains(".user")                                 ||
         (info.isExecutable() && rel_name.startsWith("test_"))          // test builds
       )
    {
        //vtrace << "about to remove";
        QFile::remove( abs_name );
        append_log_removed( abs_name );
        return;
    }
    //-----------------------------------------------------------------------------------
    bool in_sandbox = abs_name.contains("SANDBOX");
    if ( suffix == "h" || suffix == "hpp" || suffix == "c" || suffix == "cpp" )
    {
        if ( in_sandbox ) return;
        process_plus_file( abs_name );
        return;
    }
    //-----------------------------------------------------------------------------------
    if ( suffix == "cmake" || suffix == "pri" )
    {
        if ( in_sandbox ) return;
        process_build_file( abs_name );
        return;
    }
    //-----------------------------------------------------------------------------------
    //append_log_info( abs_name, "NOT APPROVED", Qt::black, Qt::red );
    auto cmd = vcat("caja ", info.absolutePath().toStdString()).str();
    (void)system( cmd.c_str() );
    vdeb << "NOT APPROVED";
    exit(42);
    //-----------------------------------------------------------------------------------
}
//=======================================================================================
void process_path( const QString& path )
{
    vdeb << "path:" << path;
    QDir dir( path );
    const auto rel_name = QFileInfo(path).fileName();

    tables_form->append_all_only( path, "DIR", QColor(Qt::darkBlue) );

    //  Exclude
    if ( rel_name == "build_tool"           ||
         rel_name == "ii_network"           ||
         rel_name.startsWith("json11")      ||
         rel_name.startsWith("qcustomplot") ||
         rel_name.startsWith("sqlite3pp")
       )
    {
        append_log_excluded( path );
        return;
    }

    //  Remove
    if ( rel_name == "build-all-tests" ||
         rel_name == "test_builds" ||
         (rel_name.startsWith("build-") && rel_name.contains("Desktop")) || // shadow
         (rel_name.startsWith("build-") && rel_name.contains("Release"))    // build
       )
    {
        dir.removeRecursively();
        append_log_removed( path );
    }

    auto filter = QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks;
    auto enties = dir.entryInfoList( filter, QDir::Name|QDir::DirsLast );

    for ( auto entry: enties )
    {
        if ( entry.isDir() )
        {
            vdeb << "process dir:" << entry.absoluteFilePath();
            process_path( entry.absoluteFilePath() );
            continue;
        }
        process_entry( entry );
    }
}
//=======================================================================================


//=======================================================================================
//      MAIN
//=======================================================================================
int main( int argc, char *argv[] )
{
    VGit::print_and_exit_if_need( argc, argv );

    prepare_licences();

    QApplication a(argc, argv);
    Tables_Form w;
    w.showMaximized();

    tables_form = &w;

    if ( argc != 2 )
    {
        vfatal.nospace() << "Usage: '" << a.applicationName() << " path_to_vlibs_dir'";
        return 1;
    }

    if ( std::string(argv[1]) == "--print-xmake-heap" )
    {
        std::cout << build_licence.toStdString();
        return 0;
    }

    process_path( argv[1] );

    w.resize_cells();
    return a.exec();
}
//=======================================================================================
//      MAIN
//=======================================================================================
static void prepare_licences()
{
    QFile f(":including_lgpl_part_00.txt");
    if ( !f.open(QIODevice::ReadOnly) )
        throw verror("Cannot find licence text in resource.");

    plus_licence = start_plus_line;
    build_licence = start_build_line;
    while ( !f.atEnd() )
    {
        auto line = f.readLine();

        if ( line != "\n" )
            line = "  " + line;                 //  Отступ только для непустых строчек.

        plus_licence += "**" + line;
        build_licence += "##" + line;
    }
    plus_licence += end_plus_line + "\n\n";
    build_licence += end_build_line + "\n\n";
}
//=======================================================================================
static void _process_licence_file( const QString& fname,
                                   const QByteArray& start_line,
                                   const QByteArray& licence )
{
    Q_ASSERT( tables_form );
    QFile f( fname );
    if ( !f.open(QIODevice::ReadWrite) )
    {
        tables_form->append_all_and_diff( fname, "OPEN ERROR", Qt::red, Qt::darkGreen );
        return;
    }
    auto ftext = f.readAll();

    if ( ftext.startsWith(start_line) )
    {
        tables_form->append_all_only( fname, "ALREADY WITH", Qt::darkGreen );
        return;
    }

    if ( !f.reset() )
    {
        tables_form->append_all_and_diff( fname, "RESET ERROR", Qt::red, Qt::darkGreen );
        return;
    }
    //vtrace << "about to append licence";
    f.write( licence );
    f.write( ftext );
    tables_form->append_all_and_diff( fname, "APPENDED", Qt::green, Qt::black );
}
//=======================================================================================
