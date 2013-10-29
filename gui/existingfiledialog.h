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

#ifndef EXISTINGFILEDIALOG_H
#define EXISTINGFILEDIALOG_H

#include <QDialog>

namespace Ui {
    class ExistingFileDialog;
}

enum FileAction {
    ActionCancel,
    ActionOverwrite,
    ActionSkip
};

class ExistingFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExistingFileDialog(QWidget *parent = 0);
    virtual ~ExistingFileDialog();

    void setDontAskAgain(bool value);
    bool dontAskAgain() const;
    FileAction action() const;

    void setFilename(const QString& filename);
    void setRemainingCount(int count);
private slots:
    void on_replaceButton_clicked();
    void on_skipButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::ExistingFileDialog *ui;
    FileAction m_ret;
};

#endif // EXISTINGFILEDIALOG_H
