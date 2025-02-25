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

#include <svg2svgt/tracer.h>
#include <svg2svgt/processorengine.h>

#include <QtWidgets/QApplication>
#include <QtCore/QDir>
#include <QtCore/QLibraryInfo>
#include <QtCore/QTranslator>

int main(int argc, char *argv[])
{
    svg2svgt::Tracer trace(Q_FUNC_INFO);
    QApplication a(argc, argv);
   
    // Locale selection
    QTranslator translator;
    QString locale = QLocale::system().name();
    translator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    translator.load("qtbase_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QString dataDir = QDir(QApplication::applicationDirPath()).absoluteFilePath("../share/svg2svgt");
    translator.load(QString("svg2svgt") + "_fi", dataDir);
    a.installTranslator(&translator);

    a.setApplicationName(QObject::tr("SVG Converter"));
    a.setApplicationVersion(svg2svgt::ProcessorEngine::getVersionString());
    a.setWindowIcon(QIcon(":/gfx/svg2svgt.png"));

    MainWindow w;
    QStringList files;
    for(int i = 1; i < argc; ++i) {
      QFile file(argv[i]);
      if(file.exists() && file.fileName().endsWith(".svg", Qt::CaseInsensitive)) {
        files.append(file.fileName());
      }
    }
    if(!files.isEmpty()) {
      w.addFiles(files);
    }
    w.show();

    return a.exec();
}
