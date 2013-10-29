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

#ifndef EXPORTTASK_H
#define EXPORTTASK_H

#include "task.h"
#include "exportdialog.h"
#include <QtCore/QSize>
#include <QtGui/QColor>
#include <QtSvg/QSvgRenderer>

class QSvgRenderer;

class ExportTask : public Task
{
public:
    explicit ExportTask(const QString& filename, const QString& outputDir, QSize size, QColor background);
    virtual ~ExportTask();
public:
    virtual void run();
    virtual QString taskName() const;
    virtual QString outputDir() const { return m_outputDir; }
private:
    QString getOutputFilename(const QString& filename);
private:
    QString m_outputDir;
    QSize m_size;
    QColor m_background;
    QSvgRenderer m_renderer;
};

#endif // EXPORTTASK_H
