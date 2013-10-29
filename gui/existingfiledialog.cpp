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

#include "existingfiledialog.h"
#include "ui_existingfiledialog.h"

ExistingFileDialog::ExistingFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingFileDialog), m_ret(ActionCancel)
{
    ui->setupUi(this);
}

ExistingFileDialog::~ExistingFileDialog()
{
    delete ui;
}

void ExistingFileDialog::setDontAskAgain(bool value)
{
    ui->dontAskAgain->setChecked(value);
}

bool ExistingFileDialog::dontAskAgain() const
{
    return ui->dontAskAgain->checkState() == Qt::Checked;
}

FileAction ExistingFileDialog::action() const
{
    return m_ret;
}

void ExistingFileDialog::setFilename(const QString& filename)
{
    ui->textLabel->setText(tr("Output file %1 already exists.\n\nDo you want to overwrite it?").arg(filename));
    update();
}

void ExistingFileDialog::setRemainingCount(int count)
{
    if (count < 2) {
        ui->dontAskAgain->setEnabled(false);
        ui->dontAskAgain->setText(tr("Do this for all remaining occurrences"));
    } else {
        ui->dontAskAgain->setEnabled(true);
        ui->dontAskAgain->setText(tr("Do this for all %1 remaining occurrences").arg(count));
    }
}

void ExistingFileDialog::on_replaceButton_clicked()
{
    m_ret = ActionOverwrite;
    accept();
}

void ExistingFileDialog::on_skipButton_clicked()
{
    m_ret = ActionSkip;
    accept();
}

void ExistingFileDialog::on_cancelButton_clicked()
{
    m_ret = ActionCancel;
    reject();
}
