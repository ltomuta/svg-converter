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

#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include "mainwindow.h"
#include "tracer.h"
#include "processorengine.h"

int main(int argc, char *argv[])
{
    Tracer trace(Q_FUNC_INFO);
    QApplication a(argc, argv);
   
    // Locale selection
    QTranslator translator;
    QString locale = QLocale::system().name();
    if(locale.compare("fi_fi", Qt::CaseInsensitive) == 0) {
      translator.load(QString(":/svg2svgt") + "_fi");
    } else {
      translator.load(QString(":/svg2svgt") + "_en");
    }
    a.installTranslator(&translator);

    a.setApplicationName(QObject::tr("SVG Converter"));
    a.setApplicationVersion(ProcessorEngine::getVersionString());
    a.setWindowIcon(QIcon(":/gfx/svg2svgt.png"));

    MainWindow w;
    w.show();

    return a.exec();
}
