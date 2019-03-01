#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include "sourceanalizer.h"
#include "pathscanner.h"
#include "vlog_qt.h"

//=======================================================================================
MainWindow::MainWindow(QString ini_path, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings( ini_path, QSettings::IniFormat )
{
    ui->setupUi(this);    
    ui->tabWidget->setCurrentWidget( ui->tab_brief );

    auto emitted = []( QString fname )
    {
        if ( !QFile::exists(fname) ) return;
        system( QString("qtcreator \"%1\"&").arg(fname).toLatin1() );
    };
    connect( ui->sources, &ReportForm::was_emitted, emitted );
    connect( ui->cmakes,  &ReportForm::was_emitted, emitted );
    connect( ui->omitted, &ReportForm::was_emitted, emitted );

    restoreGeometry( settings.value("geometry").toByteArray() );

    ui->sources->set_font( settings.value("sources-font").toString() );
    ui->cmakes-> set_font( settings.value("makes-font").toString()   );
    ui->omitted->set_font( settings.value("omitted-font").toString() );
}
//=======================================================================================
MainWindow::~MainWindow()
{
    settings.setValue( "geometry", saveGeometry() );

    settings.setValue( "sources-font", ui->sources->font() );
    settings.setValue( "makes-font",   ui->cmakes->font()  );
    settings.setValue( "omitted-font", ui->omitted->font() );

    delete ui;
}
//=======================================================================================
bool MainWindow::omit_it( const QFileInfo &fi )
{
    Q_ASSERT( fi.isFile() );
    const auto abs_name = fi.absoluteFilePath().toLower();
    const auto rel_name = fi.fileName().toLower();
    const auto suffix   = fi.suffix().toLower();

    if ( fi.absoluteFilePath().contains("boost") )  return true;
    if ( rel_name == "makefile" )                   return true;
    if ( suffix   == "o"        )                   return true;

    if ( suffix   == "txt" &&
         !rel_name.startsWith("cmakelists") )       return true;

    if ( suffix   == "opensdf"  )                   return true;
    if ( suffix   == "sdf"      )                   return true;
    if ( suffix   == "sln"      )                   return true;
    if ( suffix   == "suo"      )                   return true;
    if ( suffix   == "vcxproj"  )                   return true;
    if ( rel_name.contains(".user") )               return true;

    if ( suffix   == "conf"     )                   return true;
    if ( suffix   == "ini"     )                    return true;
    if ( suffix   == "cfg"     )                    return true;

    if ( suffix   == "sh"       )                   return true;
    if ( rel_name.contains(".tar") )                return true;
    if ( suffix   == "xml"       )                  return true;
    if ( abs_name.contains("doxygen") )             return true;

    if ( suffix   == "a"       )                    return true;
    if ( suffix   == "so"       )                   return true;

    if ( abs_name.contains("gmock") )               return true;
    if ( abs_name.contains("gtest") )               return true;
    if ( abs_name.contains("ncftp") )               return true;
    if ( abs_name.contains("ppp-2.4.4") )           return true;
    if ( abs_name.contains("zlib") )                return true;
    if ( abs_name.contains("obu/mk") )              return true;
    if ( abs_name.contains("obu/msvs") )            return true;
    if ( rel_name == "auth.tcl" )                   return true;

    if ( abs_name.contains("simulators") )          return true;
    if ( abs_name.contains("config/hex.dat") )      return true;
    if ( abs_name.contains("parser/config") )       return true;
    if ( abs_name.contains("ftp_downloader") )      return true;

    if ( rel_name.contains("lgpl") )                return true;
    if ( rel_name.contains("readme" ) )             return true;

    if ( suffix == "qrc" )                          return true;
    if ( suffix == "ui" )                           return true;

    if ( suffix == "py" )                           return true;

    if ( suffix == "jpg" )                          return true;
    if ( suffix == "png" )                          return true;

    if (abs_name.contains("build-test"))            return true;
    if (abs_name.contains("builds-desktop"))        return true;

    if (abs_name.contains("qcustomplot/"))          return true;
    if (abs_name.contains("sqlite3pp/"))            return true;
    if (abs_name.contains("json11/"))               return true;
    if (abs_name.contains("license"))               return true;

    if (rel_name.endsWith(".cmake.in"))             return true;
    if (abs_name.contains("/doc/"))                 return true;
    if (suffix == "in" )                            return true;

    if (suffix == "bash" )                          return true;
    if (suffix == "zsh" )                           return true;
    if (abs_name.contains("beginner_tutorials"))    return true;
    if (abs_name.contains("/launch/"))              return true;
    if (suffix == "msg")                            return true;

    return false;

}
//=======================================================================================
bool MainWindow::is_source( const QFileInfo &fi )
{
    if ( fi.suffix() == "h"   ) return true;
    if ( fi.suffix() == "c"   ) return true;

    if ( fi.suffix() == "hpp" ) return true;
    if ( fi.suffix() == "cpp" ) return true;

    return false;
}
//=======================================================================================
bool MainWindow::is_build( const QFileInfo &fi )
{
    if ( fi.fileName().toLower() == "cmakelists.txt" )  return true;
    if ( fi.suffix().toLower()   == "cmake" )           return true;
    if ( fi.suffix().toLower()   == "pri" )             return true;
    if ( fi.suffix().toLower()   == "pro" )             return true;

    return false;
}
//=======================================================================================
void MainWindow::scan_dir( const QString& dname )
{
    ui->root_folder_lbl->setText( dname );

    //ui->all->     set_columns( SourceAnalizer::heap() );
    ui->sources-> set_columns( SourceAnalizer::heap() );
    ui->cmakes->  set_columns( SourceAnalizer::heap() );
    ui->omitted-> set_columns( QStringList() << "Omitted filename" );

    auto all_files = PathScanner::scan( dname );
    //SourceAnalizer::List all;
    SourceAnalizer::List sources, cmakes;
    //===================================================================================
    for ( auto fi: all_files )
    {
        if ( !fi.isFile() ) continue;

        if ( omit_it(fi) )
        {
            ui->omitted->add_row( QStringList() << fi.absoluteFilePath() );
            continue;
        }
        SourceAnalizer sa( fi.absoluteFilePath() );
        if ( is_build(fi) )
        {
            cmakes << sa;
            ui->cmakes->add_row( sa.as_list() );
            continue;
        }
        if ( is_source(fi) )
        {
            sources << sa;
            ui->sources->add_row( sa.as_list() );
            continue;
        }

        vdeb << fi.absoluteFilePath();
        exit(1);
    }
    //===================================================================================
    {
        SourceAnalizer src_brief;
        for ( const auto &sa: sources ) src_brief.summ( sa );
        ui->sources->brief( src_brief.as_brief() );
    }
    {
        SourceAnalizer cmk_brief;
        for ( const auto &sa: cmakes ) cmk_brief.summ( sa );
        ui->cmakes->brief( cmk_brief.as_brief() );
    }
    //===================================================================================
    ui->cmakes->resize_to_context();
    ui->sources->resize_to_context();
    ui->omitted->resize_to_context();
    //===================================================================================
    ui->tabWidget->setCurrentWidget( ui->tab_sources );
    //===================================================================================
}
//=======================================================================================
void MainWindow::on_open_folder_btn_clicked()
{
    auto last_path = settings.value("last-path").toString();
    auto dname = QFileDialog::getExistingDirectory( this,
                                                    "Open project folder",
                                                    last_path );
    if ( dname.isEmpty() ) return;
    settings.setValue( "last-path", dname );
    settings.sync();

    scan_dir( dname  );
}
//=======================================================================================
