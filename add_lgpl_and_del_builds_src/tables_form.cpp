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


#include "tables_form.h"
#include "ui_tables_form.h"

//=======================================================================================
Tables_Form::Tables_Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tables_Form)
{
    ui->setupUi(this);

    ui->diff_table->setColumnCount( 2 );
    ui->all_table->setColumnCount( 2 );

    ui->diff_table->horizontalHeader()->setStretchLastSection( true );
    ui->all_table->horizontalHeader()->setStretchLastSection( true );
}
//=======================================================================================
Tables_Form::~Tables_Form()
{
    delete ui;
}
//=======================================================================================
void Tables_Form::resize_cells()
{
    ui->diff_table->resizeColumnsToContents();
    ui->diff_table->resizeRowsToContents();

    ui->all_table->resizeColumnsToContents();
    ui->all_table->resizeRowsToContents();
}
//=======================================================================================
void Tables_Form::append_all_only( const QString &path,
                                   const QString &info,
                                   const QColor &color,
                                   const QColor &bkg_color )
{
    _append_to( ui->all_table, path, info, color, bkg_color );
}
//=======================================================================================
void Tables_Form::append_all_and_diff( const QString &path,
                                       const QString &info,
                                       const QColor &color,
                                       const QColor &bkg_color )
{
    _append_to( ui->all_table,  path, info, color, bkg_color );
    _append_to( ui->diff_table, path, info, color, bkg_color );
}
//=======================================================================================
void Tables_Form::_append_to( QTableWidget *table,
                              const QString &path,
                              const QString &info,
                              const QColor &color,
                              const QColor &bkg_color )
{
    Q_ASSERT( table );

    static const auto font = QFont("Courier new", 12);

    int row = table->rowCount();
    table->setRowCount( row + 1 );

    auto item0 = new QTableWidgetItem( path );
    item0->setFont( font );
    item0->setTextColor( color );
    if ( bkg_color.isValid() ) item0->setBackgroundColor( bkg_color );
    table->setItem( row, 0, item0 );

    auto item1 = new QTableWidgetItem( info );
    item1->setFont( font );
    item1->setTextColor( color );
    if ( bkg_color.isValid() ) item1->setBackgroundColor( bkg_color );
    table->setItem( row, 1, item1 );
}
//=======================================================================================
