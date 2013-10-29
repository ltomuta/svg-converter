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

#include "exportdialog.h"
#include "ui_exportdialog.h"
#include "tracer.h"
#include <QtGui/QColorDialog>

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog), m_colorDialog(0), m_color(Qt::transparent), m_maintainAspectRatio(false)
{
    Tracer trace(Q_FUNC_INFO);
    ui->setupUi(this);
    static const int MINIMUM_EXPORT_SIZE = 16;
    static const int MAXIMUM_EXPORT_SIZE = 4096;

    ui->customWidth->setValidator(new QIntValidator(MINIMUM_EXPORT_SIZE, MAXIMUM_EXPORT_SIZE, ui->customWidth));
    ui->customHeight->setValidator(new QIntValidator(MINIMUM_EXPORT_SIZE, MAXIMUM_EXPORT_SIZE, ui->customHeight));
    connect(ui->size16, SIGNAL(clicked()), this, SLOT(updateUI()));
    connect(ui->size32, SIGNAL(clicked()), this, SLOT(updateUI()));
    connect(ui->size48, SIGNAL(clicked()), this, SLOT(updateUI()));
    connect(ui->size64, SIGNAL(clicked()), this, SLOT(updateUI()));
    connect(ui->size96, SIGNAL(clicked()), this, SLOT(updateUI()));
    connect(ui->size128, SIGNAL(clicked()), this, SLOT(updateUI()));
    connect(ui->sizeCustom, SIGNAL(clicked()), this, SLOT(updateUI()));
    connect(ui->customWidth, SIGNAL(textChanged(QString)), this, SLOT(updateUI()));
    connect(ui->customHeight, SIGNAL(textChanged(QString)), this, SLOT(updateUI()));
}

ExportDialog::~ExportDialog()
{
    Tracer trace(Q_FUNC_INFO);
    delete ui;
}

QList<QSize> ExportDialog::getSizes() const
{
    QList<QSize> sizes;
    if (ui->size16->isChecked()) {
        sizes.append(QSize(16,16));
    }
    if (ui->size32->isChecked()) {
        sizes.append(QSize(32,32));
    }
    if (ui->size48->isChecked()) {
        sizes.append(QSize(48,48));
    }
    if (ui->size64->isChecked()) {
        sizes.append(QSize(64,64));
    }
    if (ui->size96->isChecked()) {
        sizes.append(QSize(96,96));
    }
    if (ui->size128->isChecked()) {
        sizes.append(QSize(128,128));
    }
    if (ui->sizeCustom->isChecked()) {
        QString width = ui->customWidth->text();
        QString height = ui->customHeight->text();
        int pos = 0;
        if (ui->customWidth->validator()->validate(width,pos) == QValidator::Acceptable ||
                ui->customHeight->validator()->validate(height,pos) == QValidator::Acceptable) {
            int w = 0;
            int h = 0;
            if (!width.isEmpty()) {
                w = width.toInt();
            }
            if (!height.isEmpty()) {
                h = height.toInt();
            }
            sizes.append(QSize(w,h));
        }
    }
    return sizes;
}

QColor ExportDialog::getColor() const
{
    return m_color;
}

void ExportDialog::updateUI()
{
    bool canExport = false;

    if (ui->size16->isChecked()) {
        canExport = true;
        goto update;
    }
    if (ui->size32->isChecked()) {
        canExport = true;
        goto update;
    }
    if (ui->size48->isChecked()) {
        canExport = true;
        goto update;
    }
    if (ui->size64->isChecked()) {
        canExport = true;
        goto update;
    }
    if (ui->size96->isChecked()) {
        canExport = true;
        goto update;
    }
    if (ui->size128->isChecked()) {
        canExport = true;
        goto update;
    }
    if (ui->sizeCustom->isChecked()) {
        QString width = ui->customWidth->text();
        QString height = ui->customHeight->text();
        int pos = 0;
        if (m_maintainAspectRatio) {
            if (width.isEmpty() && !height.isEmpty()) {
                ui->customWidth->setEnabled(false);
            } else if (!width.isEmpty() && height.isEmpty()) {
                ui->customHeight->setEnabled(false);
            } else {
                ui->customWidth->setEnabled(true);
                ui->customHeight->setEnabled(true);
            }
        }
        if (m_maintainAspectRatio &&
                (ui->customWidth->validator()->validate(width,pos) == QValidator::Acceptable ||
                 ui->customHeight->validator()->validate(height,pos) == QValidator::Acceptable)) {
            canExport = true;
            goto update;
        } else if (ui->customWidth->validator()->validate(width,pos) == QValidator::Acceptable &&
                   ui->customHeight->validator()->validate(height,pos) == QValidator::Acceptable) {
            canExport = true;
            goto update;
        }
    }

update:
    ui->exportButton->setEnabled(canExport);
}

void ExportDialog::on_cancelButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    reject();
}

void ExportDialog::on_exportButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    accept();
}

void ExportDialog::on_sizeCustom_toggled(bool checked)
{
    ui->customWidth->setEnabled(checked);
    ui->customHeight->setEnabled(checked);
    ui->aspectRatioButton->setEnabled(checked);
    updateUI();
}

void ExportDialog::on_backgroundCustom_clicked(bool checked)
{
    ui->backgroundPreview->setEnabled(checked);
    if (checked) {
        if (!m_colorDialog) {
            m_colorDialog = new QColorDialog(this);
        }
        int ret = m_colorDialog->exec();
        if (ret == QDialog::Accepted) {
            m_color = m_colorDialog->currentColor();
            ui->backgroundPreview->setStyleSheet(QString("QLabel { background-color: rgb(%1,%2,%3); }").arg(m_color.red()).arg(m_color.green()).arg(m_color.blue()));
        }
    }
}

void ExportDialog::on_backgroundWhite_clicked(bool checked)
{
    if (checked) {
        m_color = Qt::white;
    }
}

void ExportDialog::on_backgroundBlack_clicked(bool checked)
{
    if (checked) {
        m_color = Qt::black;
    }
}

void ExportDialog::on_backgroundTransparent_clicked(bool checked)
{
    if (checked) {
        m_color = Qt::transparent;
    }
}

void ExportDialog::on_aspectRatioButton_clicked()
{
    m_maintainAspectRatio = !m_maintainAspectRatio;
    if (m_maintainAspectRatio) {
        ui->aspectRatioButton->setIcon(QIcon(":/gfx/linked.png"));
        ui->customHeight->clear();
    } else {
        ui->aspectRatioButton->setIcon(QIcon(":/gfx/unlinked.png"));
    }
    updateUI();
}

void ExportDialog::on_customWidth_textChanged(const QString &arg1)
{
    if (m_maintainAspectRatio) {
        if (!ui->customHeight->text().isEmpty()) {
            ui->customWidth->clear();
        } else {
            ui->customHeight->setEnabled(arg1.length() == 0);
        }
    }
}

void ExportDialog::on_customHeight_textChanged(const QString &arg1)
{
    if (m_maintainAspectRatio) {
        if (!ui->customWidth->text().isEmpty()) {
            ui->customHeight->clear();
        } else {
            ui->customWidth->setEnabled(arg1.length() == 0);
        }
    }
}
