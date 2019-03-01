#include "reportform.h"
#include "ui_reportform.h"

//=======================================================================================
ReportForm::ReportForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReportForm)
{
    ui->setupUi(this);
//    ui->table->horizontalHeader()->setStretchLastSection(true);
}
//=======================================================================================
ReportForm::~ReportForm()
{
    delete ui;
}
//=======================================================================================
void ReportForm::set_columns(const QStringList& names )
{
    ui->table->setRowCount(0);
    ui->table->setColumnCount(0);

    ui->table->setColumnCount( names.count() );
    for (int c = 0; c < names.count(); ++c)
        ui->table->setHorizontalHeaderItem( c, new QTableWidgetItem(names.at(c)) );
}
//=======================================================================================
void ReportForm::add_row( const QStringList& vals,
                          const QColor& font_col,
                          const QColor& bk_col )
{
    Q_ASSERT( vals.count() == ui->table->columnCount() );

    auto row = ui->table->rowCount();
    ui->table->setRowCount( row + 1 );

    for (int c = 0; c < ui->table->columnCount(); ++c)
    {
        auto item = new QTableWidgetItem( vals.at(c) );
        if (c) item->setTextAlignment( Qt::AlignRight ); // со второй колонки...
        item->setFont( font() );
        if ( font_col.isValid() ) item->setTextColor( font_col );
        if ( bk_col.isValid()   ) item->setBackgroundColor( bk_col );
        ui->table->setItem( row, c, item );
    }
}
//=======================================================================================
void ReportForm::brief(QString text)
{
    ui->brief->setText( text );
}
//=======================================================================================
void ReportForm::resize_to_context()
{
    ui->table->horizontalHeader()->setStretchLastSection(false);
    ui->table->horizontalHeader()->setStretchLastSection(true);
    ui->table->resizeColumnsToContents();
    ui->table->resizeRowsToContents();
    ui->table->horizontalHeader()->setStretchLastSection(false);
}
//=======================================================================================
QFont ReportForm::font() const
{
    auto res = ui->font->currentFont();
    res.setPointSizeF( ui->font_size->value() );
    return res;
}
//=======================================================================================
void ReportForm::set_font(QFont f)
{
    ui->font->setCurrentFont( f );
    apply_font( f );
}
//=======================================================================================
void ReportForm::on_font_currentFontChanged( QFont f )
{
    f.setPointSizeF( ui->font_size->value() );
    apply_font( f );
}
//=======================================================================================
void ReportForm::on_font_size_valueChanged( double arg1 )
{
    auto f = ui->font->currentFont();
    f.setPointSizeF( arg1 );
    apply_font( f );
}
//=======================================================================================
void ReportForm::apply_font( const QFont& f )
{
    for (int c = 0; c < ui->table->columnCount(); ++c)
    {
        for (int r = 0; r < ui->table->rowCount(); ++r)
        {
            ui->table->item(r, c)->setFont( f );
        } // for all r
    } // for all c
    resize_to_context();
    ui->brief->setFont( f );
}
//=======================================================================================
void ReportForm::on_resize_btn_clicked()
{
    resize_to_context();
}
//=======================================================================================
void ReportForm::on_emit_btn_clicked()
{
    auto items = ui->table->selectedItems();
    if (items.isEmpty()) return;
    emit was_emitted( items.first()->text() );
}
//=======================================================================================
