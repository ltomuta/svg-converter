/**
 * SVG Converter
 * Copyright (C) 2011 Nokia
 *   
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1 of
 *  the License, or (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  Lesser General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ExportDialog;
}
class QColorDialog;

class ExportDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExportDialog(QWidget *parent = 0);
    virtual ~ExportDialog();
public:
    QList<QSize> getSizes() const;
    QColor getColor() const;
private slots:
    void updateUI();
    void on_cancelButton_clicked();
    void on_exportButton_clicked();
    void on_sizeCustom_toggled(bool checked);
    void on_backgroundCustom_clicked(bool checked);
    void on_backgroundWhite_clicked(bool checked);
    void on_backgroundBlack_clicked(bool checked);
    void on_backgroundTransparent_clicked(bool checked);
    void on_aspectRatioButton_clicked();

    void on_customWidth_textChanged(const QString &arg1);

    void on_customHeight_textChanged(const QString &arg1);

private:
    Ui::ExportDialog *ui;
    QColorDialog *m_colorDialog;
    QColor m_color;
    bool m_maintainAspectRatio;
};

#endif // EXPORTDIALOG_H
