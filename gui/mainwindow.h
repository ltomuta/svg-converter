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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "exportdialog.h"
#include "svglistitemdelegate.h"
#include "existingfiledialog.h"

// Forward declarations
namespace Ui {
class MainWindow;
}
class AboutDialog;
class ExportDialog;
class QFileDialog;
class ExistingFileDialog;
class QListWidgetItem;
class QSvgRenderer;
class QPixmapCache;
class SvgListItemDelegate;
class QProgressBar;
class QStandardItemModel;
class QDragEnterEvent;
class QDropEvent;
class Logger;

typedef QPair<QModelIndex, FileAction> ActionPair;
typedef QList<ActionPair> ActionList;

// Main UI
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
private slots:
    void on_browseForFolderButton_clicked();
    void on_aboutButton_clicked();
    void on_addFilesButton_clicked();
    void on_removeFilesButton_clicked();
    void on_convertFilesButton_clicked();
    void on_convertAllButton_clicked();
    void on_exportButton_clicked();
    void on_outputFolderLineEdit_textChanged(const QString &newText);
    void on_exportAllButton_clicked();
    void on_inputFilesWidget_clicked(const QModelIndex &index);

private:
    void updateOutputDir(const QString& dir);
    QModelIndexList getSelectedFiles();
    QModelIndexList getAllFiles();
    void addFiles(const QStringList& filenames);
    void doConversion(const QModelIndexList& files, const QString& outputDir);
    void doExport(const QModelIndexList& files, const QString& outputDir, QList<QSize> sizes, QColor background);
    bool checkOutputFiles(const QModelIndexList& files, ActionList& actions);
    void resetBeforeStart();
    void updateMessages(const Logger& logger);
    int showExportDialog();
    void deleteTemporaries();
    QString getConversionOutputFilename(const QString& filename);
    QString getConversionTempFilename(const QString& filename);
private:
    // UI
    Ui::MainWindow *ui;
    SvgListItemDelegate* m_delegate;
    AboutDialog *m_aboutDialog;
    ExportDialog *m_exportDialog;
    QFileDialog *m_fileDialog;
    ExistingFileDialog* m_replaceDialog;
    QProgressBar* m_progress;
    QString m_currentFilename;
    QString m_outputDir;
    QString m_lastDir;
    QString m_tempDir;
    int m_currentProgress;
    bool m_overwrite;
    bool m_dontAskAgain;

    QStandardItemModel* m_model;
    QStringList m_messages;
    QStringList m_warnings;
    QStringList m_errors;
    QStringList m_generatedTemps;
};

#endif // MAINWINDOW_H
