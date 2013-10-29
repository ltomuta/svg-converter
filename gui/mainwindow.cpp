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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "exportdialog.h"
#include "existingfiledialog.h"
#include "svglistitemdelegate.h"
#include "conversiontask.h"
#include "exporttask.h"
#include "tracer.h"

#include <QtCore/QFileInfo>
#include <QtCore/QThread>
#include <QtCore/QThreadPool>
#include <QtGui/QFileDialog>
#include <QtGui/QDesktopServices>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QPixmapCache>
#include <QtGui/QPixmap>
#include <QtGui/QProgressBar>
#include <QtGui/QPainter>
#include <QtGui/QStandardItemModel>
#include <QtGui/QStandardItem>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtSvg/QSvgRenderer>


#include <QtCore/QDebug>

#include <iostream>

using std::cerr;
using std::endl;

static const int THUMBNAIL_SIZE = 128;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_delegate(0), m_aboutDialog(0), m_exportDialog(0), m_fileDialog(0), m_replaceDialog(0),
    m_progress(0), m_currentFilename(""), m_outputDir(""), m_lastDir(""),
    m_tempDir(QDir::toNativeSeparators(QDesktopServices::storageLocation(QDesktopServices::TempLocation))),
    m_currentProgress(0), m_overwrite(true), m_dontAskAgain(false)
{
    Tracer trace(Q_FUNC_INFO);
    m_model = new QStandardItemModel(this);
    ui->setupUi(this);
    setWindowIcon(QIcon(":/gfx/svg2svgt.png"));

    m_progress = new QProgressBar(this);
    m_progress->setVisible(false);
    statusBar()->addPermanentWidget(m_progress);

    m_delegate = new SvgListItemDelegate(this);
    m_delegate->setThumbnailSize(THUMBNAIL_SIZE,THUMBNAIL_SIZE);
    ui->inputFilesWidget->setModel(m_model);
    ui->inputFilesWidget->setItemDelegate(m_delegate);
    ui->previewBeforeWidget->load(tr(":/gfx/placeholder.svg"));
    ui->previewAfterWidget->load(tr(":/gfx/placeholder.svg"));
    ui->inputFilesWidget->setAcceptDrops(true);
    setAcceptDrops(true);
    update();
}

MainWindow::~MainWindow()
{
    Tracer trace(Q_FUNC_INFO);
    delete ui;
    delete m_delegate;
    delete m_aboutDialog;
    delete m_fileDialog;
    delete m_model;
    deleteTemporaries();
}
void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    Tracer trace(Q_FUNC_INFO);
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* event)
{
    Tracer trace(Q_FUNC_INFO);
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }
    QStringList filesToAdd;
    foreach (QUrl url, urls) {
        QFileInfo info(url.toLocalFile());
        if (info.fileName().endsWith(".svg")) {
            filesToAdd.append(QDir::toNativeSeparators(info.absoluteFilePath()));
        }
    }
    filesToAdd.removeDuplicates();
    addFiles(filesToAdd);
}

void MainWindow::on_browseForFolderButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    QString startupDir = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);
    m_outputDir = QFileDialog::getExistingDirectory(this, tr("Select output folder"), startupDir);
    ui->outputFolderLineEdit->setText(m_outputDir);
    update();
}


void MainWindow::on_aboutButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    if (!m_aboutDialog) {
        m_aboutDialog = new AboutDialog(this);
    }
    m_aboutDialog->show();
}

void MainWindow::on_addFilesButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    if (m_lastDir.isEmpty()) {
        m_lastDir = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);
    }
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open SVG-files"), m_lastDir, tr("SVG-images (*.svg)"));
    addFiles(files);
}

void MainWindow::on_removeFilesButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);

    foreach(QModelIndex index, ui->inputFilesWidget->selectionModel()->selectedIndexes())
    {
        m_model->removeRow(index.row());
    }
    if (m_model->rowCount() == 0) {
        ui->removeFilesButton->setEnabled(false);
        ui->convertFilesButton->setEnabled(false);
        ui->convertAllButton->setEnabled(false);
        ui->exportButton->setEnabled(false);
        ui->exportAllButton->setEnabled(false);
        ui->outputFolderLineEdit->clear();
    }
    update();
}

void MainWindow::on_convertFilesButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    doConversion(getSelectedFiles(), m_outputDir);
}

void MainWindow::on_convertAllButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    doConversion(getAllFiles(), m_outputDir);
}

void MainWindow::on_exportButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    if (QDialog::Accepted == showExportDialog()) {
        QList<QSize> exportSizes = m_exportDialog->getSizes();
        QColor color = m_exportDialog->getColor();
        doExport(getSelectedFiles(), m_outputDir, exportSizes, color);
    }
}

void MainWindow::on_exportAllButton_clicked()
{
    Tracer trace(Q_FUNC_INFO);
    if (QDialog::Accepted == showExportDialog()) {
        QList<QSize> exportSizes = m_exportDialog->getSizes();
        QColor color = m_exportDialog->getColor();
        doExport(getAllFiles(), m_outputDir, exportSizes, color);
    }
}

void MainWindow::on_inputFilesWidget_clicked(const QModelIndex &index)
{
    QVariant data = m_model->data(index, FULLPATH_DATA_ROLE);
    QFileInfo info(data.toString());
    m_currentFilename = QDir::toNativeSeparators(info.absoluteFilePath());
    QString tempFilename = QDir::toNativeSeparators(getConversionTempFilename(m_currentFilename));
    ui->previewBeforeWidget->load(m_currentFilename);
    ui->previewBeforeWidget->setToolTip(m_currentFilename);
    ConversionTask* task = new ConversionTask(m_currentFilename, tempFilename);
    QThreadPool::globalInstance()->start(task); // threadpool deletes the task when done
    QThreadPool::globalInstance()->waitForDone();
    ui->previewAfterWidget->load(tempFilename);
    ui->previewAfterWidget->setToolTip(tempFilename);
    m_generatedTemps.append(tempFilename);
    m_generatedTemps.removeDuplicates();
    update();
}

void MainWindow::on_outputFolderLineEdit_textChanged(const QString &newText)
{
    Tracer trace(Q_FUNC_INFO);
    updateOutputDir(newText);
}

QModelIndexList MainWindow::getSelectedFiles()
{
    return ui->inputFilesWidget->selectionModel()->selectedIndexes();
}

QModelIndexList MainWindow::getAllFiles()
{
    Tracer trace(Q_FUNC_INFO);
    QModelIndexList list;

    for (int i = 0; i < m_model->rowCount(); i++) {
        QModelIndex idx = m_model->index(i,0);
        list.append(idx);
    }
    return list;
}

void MainWindow::updateOutputDir(const QString& dirName)
{
    Tracer trace(Q_FUNC_INFO);
    QDir dir(dirName);
    m_outputDir = QDir::toNativeSeparators(dir.absolutePath() + QDir::separator());
}


void MainWindow::addFiles(const QStringList& filenames)
{
    Tracer trace(Q_FUNC_INFO);
    //If first file added, populate the output-dir
    if (filenames.count() > 0) {
        ui->removeFilesButton->setEnabled(true);
        ui->convertFilesButton->setEnabled(true);
        ui->convertAllButton->setEnabled(true);
        ui->exportButton->setEnabled(true);
        ui->exportAllButton->setEnabled(true);
        if (m_model->rowCount() == 0) {
            QFileInfo info(filenames.at(0));
            m_lastDir = QDir::toNativeSeparators(info.absolutePath() + QDir::separator());
            m_outputDir = m_lastDir;
            ui->outputFolderLineEdit->setText(m_outputDir);
        }
    }

    foreach(QString filename, filenames) {
        QFileInfo info(filename);
        QStandardItem* item = new QStandardItem(info.fileName());
        item->setData(QVariant(info.fileName()), FILENAME_DATA_ROLE);
        item->setData(QVariant(info.absoluteFilePath()), FULLPATH_DATA_ROLE);
        item->setData(ITEM_DEFAULT, ITEM_STATE);
        m_model->appendRow(item);
        update();
    }
}

void MainWindow::doConversion(const QModelIndexList& files, const QString& outputDir)
{
    Tracer trace(Q_FUNC_INFO);

    resetBeforeStart();
    // First check for all output files that they don't exist
    ActionList actions;
    if (checkOutputFiles(files, actions)) {
        QThreadPool* pool = QThreadPool::globalInstance();
        m_progress->setMaximum(files.count());
        m_progress->setVisible(true);

        QList<QPair<ConversionTask*, QModelIndex> > tasks;
        foreach(ActionPair pair, actions) {
            QModelIndex index = pair.first;
            FileAction action = pair.second;
            if (action == ActionSkip) {
                qDebug() << "SKIP";
                m_model->setData(index, ITEM_DEFAULT, ITEM_STATE);
                continue;
            } else if (action == ActionOverwrite) {
                qDebug() << "OVERWRITE";
                QString filename = m_model->data(index, FULLPATH_DATA_ROLE).toString();
                m_model->setData(index, ITEM_CONVERTING, ITEM_STATE);
                ConversionTask* task = new ConversionTask(filename, getConversionOutputFilename(filename));
                tasks.append(qMakePair(task, index));
                task->setAutoDelete(false); // prevent automatic deletion by QThreadPool
                pool->start(task);
            }
            ++m_currentProgress;
            m_progress->setValue(m_currentProgress);
        }

        pool->waitForDone();
        m_progress->setVisible(false);

        // All done, gather logger messages and update status.
        QPair<ConversionTask*, QModelIndex> pair;
        foreach (pair, tasks) {
            ConversionTask* task = pair.first;
            QModelIndex index = pair.second;

            updateMessages(task->logger());
            if (task->logger().errors().count() > 0) {
                m_model->setData(index, ITEM_ERRORS, ITEM_STATE);
            } else if (task->logger().warnings().count() > 0) {
                m_model->setData(index, ITEM_WARNINGS, ITEM_STATE);
            } else {
                m_model->setData(index, ITEM_CONVERTED, ITEM_STATE);
            }
            delete task;
            task = 0;
        }
    } else {
        // User cancelled whole operation
    }
}

void MainWindow::doExport(const QModelIndexList& files, const QString& outputDir, QList<QSize> sizes, QColor background)
{
    Tracer trace(Q_FUNC_INFO);
    resetBeforeStart();
    m_progress->setMaximum(files.count()*sizes.count());
    m_progress->setVisible(true);

    QThreadPool* pool = QThreadPool::globalInstance();
    QList<ExportTask*> tasks;
    foreach(QModelIndex index, files) {
        QString filename = m_model->data(index, FULLPATH_DATA_ROLE).toString();
        foreach (QSize size, sizes) {
            ExportTask* task = new ExportTask(filename, outputDir, size, background);
	    tasks.append(task);
	    task->setAutoDelete(false); // prevent automatic deletion by QThreadPool
            pool->start(task);
            ++m_currentProgress;
            m_progress->setValue(m_currentProgress);
        }
    }
    pool->waitForDone();
    m_progress->setVisible(false);

    // All done, gather logger messages.
    foreach (ExportTask* task, tasks) {
	updateMessages(task->logger());
	delete task;
    }
}

bool MainWindow::checkOutputFiles(const QModelIndexList& files, ActionList& actions)
{
    Tracer trace(Q_FUNC_INFO);
    int leftCount = files.count();
    foreach (QModelIndex index, files) {
        QString filename = getConversionOutputFilename(m_model->data(index, FULLPATH_DATA_ROLE).toString());
        QFileInfo info(filename);
        if (info.exists()) {
            if (!m_replaceDialog) {
                m_replaceDialog = new ExistingFileDialog(this);
            }
            // Show dialog if
            FileAction lastAction = ActionOverwrite;
            if (!m_dontAskAgain) {
                m_replaceDialog->setDontAskAgain(m_dontAskAgain);
                m_replaceDialog->setFilename(info.fileName());
                m_replaceDialog->setRemainingCount(leftCount);
                if (m_replaceDialog->exec() == QDialog::Accepted) {
                    m_dontAskAgain = m_replaceDialog->dontAskAgain();
                    FileAction action = m_replaceDialog->action();
                    lastAction = action;
                    actions.append(qMakePair(index, action));
                    if (action != ActionOverwrite && action != ActionSkip) {
                        // Cancel whole process
                        return false;
                    }
                } else {
                    // Cancel whole process
                    return false;
                }
            } else {
                // Don't show dialog anymore, use the last valid action
                actions.append(qMakePair(index, lastAction));
            }
        } else {
            // Default is overwrite
            actions.append(qMakePair(index, ActionOverwrite));
        }
        --leftCount;
    }
    // Continue
    return true;
}

void MainWindow::resetBeforeStart()
{
    Tracer trace(Q_FUNC_INFO);
    m_currentProgress = 0;
    m_overwrite = false;
    m_dontAskAgain = false;
    m_messages.clear();
    m_errors.clear();
    m_warnings.clear();
    ui->messagesBrowser->clear();
    ui->warningsBrowser->clear();
    ui->errorsBrowser->clear();
    ui->outputTabWidget->setTabText(0, tr("Messages (%1)").arg(m_messages.count()));
    ui->outputTabWidget->setTabText(1, tr("Errors (%1)").arg(m_errors.count()));
    ui->outputTabWidget->setTabText(2, tr("Warnings (%1)").arg(m_warnings.count()));
}

// This is used to calculate the relevant number of message, warnings or errors
// that is to be displayed in the tab header. Headers and empty lines
// are ignored.
static int displayableCount(const QStringList& stringList, bool skipHeaders) 
{
    int count = 0;
    foreach(QString s, stringList) {
	if(s.trimmed().isEmpty() || (skipHeaders && s.left(3) == "***")) {
	    continue;
	}
	count++;
    }
    return count;
}

void MainWindow::updateMessages(const Logger& logger)
{
    Tracer trace(Q_FUNC_INFO);

    m_messages.append(logger.messages());
    foreach(QString message, logger.messages()) {
        ui->messagesBrowser->append(message);
    }
    ui->outputTabWidget->setTabText(0, tr("Messages (%1)").arg(displayableCount(m_messages, false)));

    m_errors.append(logger.errors());
    foreach(QString error, logger.errors()) {
        ui->errorsBrowser->append(error);
    }
    ui->outputTabWidget->setTabText(1, tr("Errors (%1)").arg(displayableCount(m_errors, true)));

    m_warnings.append(logger.warnings());
    foreach(QString warning, logger.warnings()) {
        ui->warningsBrowser->append(warning);
    }
    ui->outputTabWidget->setTabText(2, tr("Warnings (%1)").arg(displayableCount(m_warnings, true)));
    update();
}

int MainWindow::showExportDialog()
{
    Tracer trace(Q_FUNC_INFO);
    if (!m_exportDialog) {
        m_exportDialog = new ExportDialog(this);
    }
    return m_exportDialog->exec();
}

void MainWindow::deleteTemporaries()
{
    cerr << tr("Deleting %1 generated temp-files").arg(m_generatedTemps.count()).toStdString() << endl;
    foreach (QString filename, m_generatedTemps) {
        QFile temp(filename);
        if (!temp.remove()) {
            cerr << tr("Error deleting temp-file %1").arg(filename).toStdString() << endl;
        }
    }
}

QString MainWindow::getConversionOutputFilename(const QString& filename)
{
    QFileInfo info(filename);
    QString outputFilename(m_outputDir);
    outputFilename = outputFilename.append(QDir::separator());
    outputFilename = outputFilename.append(info.baseName());
    outputFilename = outputFilename.append("_converted.svg");

    return outputFilename;
}

QString MainWindow::getConversionTempFilename(const QString& filename)
{
    QFileInfo info(filename);
    QString outputFilename(m_tempDir);
    outputFilename = outputFilename.append(QDir::separator());
    outputFilename = outputFilename.append(info.baseName());
    outputFilename = outputFilename.append("_converted.svg");

    return outputFilename;
}
