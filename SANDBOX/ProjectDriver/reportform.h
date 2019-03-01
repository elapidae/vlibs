#ifndef REPORTFORM_H
#define REPORTFORM_H

#include <QWidget>

namespace Ui {
class ReportForm;
}

class ReportForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReportForm(QWidget *parent = nullptr);
    ~ReportForm();

    QFont font() const;
    void set_font(QFont f);

signals:
    void was_emitted( QString );

public slots:
    void set_columns( const QStringList &names );
    void add_row( const QStringList& vals,
                  const QColor& font_col = QColor(),
                  const QColor& bk_col   = QColor() );

    void brief( QString text );
    void resize_to_context();

private slots:
    void on_font_currentFontChanged(QFont f);
    void on_font_size_valueChanged(double arg1);
    void on_resize_btn_clicked();
    void on_emit_btn_clicked();

private:
    Ui::ReportForm *ui;
    void apply_font( const QFont& f );
};

#endif // REPORTFORM_H
