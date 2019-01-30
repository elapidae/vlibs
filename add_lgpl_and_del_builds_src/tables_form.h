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


#ifndef TABLES_FORM_H
#define TABLES_FORM_H

#include <QWidget>
class QTableWidget;

namespace Ui {
class Tables_Form;
}

class Tables_Form : public QWidget
{
    Q_OBJECT
public:
    explicit Tables_Form(QWidget *parent = nullptr);
    ~Tables_Form();

public slots:
    void resize_cells();

    void append_all_only( const QString& path,
                          const QString& info,
                          const QColor& color,
                          const QColor& bkg_color = QColor() );

    void append_all_and_diff( const QString& path,
                              const QString& info,
                              const QColor& color,
                              const QColor& bkg_color = QColor() );

private:
    Ui::Tables_Form *ui;

    static void _append_to( QTableWidget *table,
                            const QString& path,
                            const QString& info,
                            const QColor& color,
                            const QColor& bkg_color );
};

#endif // TABLES_FORM_H
