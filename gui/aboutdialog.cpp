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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "tracer.h"
#include "processorengine.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    Tracer trace(Q_FUNC_INFO);
    ui->setupUi(this);
    ui->textBrowser->clear();
    ui->textBrowser->setText(ProcessorEngine::getVersionStringFormatted());
}

AboutDialog::~AboutDialog()
{
    Tracer trace(Q_FUNC_INFO);
    delete ui;
}

void AboutDialog::on_dismissButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    accept();
}
