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

#include "exporttask.h"
#include "tracer.h"
#include "logger.h"

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QDebug>

ExportTask::ExportTask(const QString& filename, const QString& outputDir, QSize size, QColor background) :
    Task(filename), m_outputDir(outputDir), m_size(size), m_background(background)
{
    m_logger = new Logger;
    Tracer trace(Q_FUNC_INFO);
    QDir dir(m_outputDir);
    if (!dir.exists()) {
        dir.mkpath(m_outputDir);
    }
}

ExportTask::~ExportTask()
{
    Tracer trace(Q_FUNC_INFO);
    delete m_logger;
}

void ExportTask::run()
{
    Tracer trace(Q_FUNC_INFO);
    bool maintainAr = false;
    int w = m_size.width();
    int h = m_size.height();
    if (w == 0 || h == 0) {
        maintainAr = true;
    }
    QString outputFile = getOutputFilename(m_filename);
    m_logger->message(QObject::tr("Exporting %1 -> %2").arg(m_filename).arg(outputFile));

    if (m_renderer.load(m_filename)) {

        if (maintainAr) {
            QRect r = m_renderer.viewBox();
            float ar = (float)r.width()/(float)r.height();
            if (w == 0) {
                w = int( (float)h*ar);
            } else if (h == 0) {
                h = int ( (float)w/ar);
            }
        }
        /*
        For optimal performance only use the format types QImage::Format_ARGB32_Premultiplied,
        QImage::Format_RGB32 or QImage::Format_RGB16. Any other format, including QImage::Format_ARGB32,
        has significantly worse performance.
         */
        QImage image(QSize(w,h), QImage::Format_ARGB32_Premultiplied);
        QPainter paint(&image);

        image.fill(m_background.rgba());

        paint.save();
        paint.setRenderHints( QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform);
        m_renderer.render(&paint);
        paint.restore();
        // Save file
        if (!image.save(outputFile)) {
            m_logger->error(QObject::tr("Error saving file %1").arg(outputFile));
        }
    } else {
        m_logger->error(QObject::tr("Could not load SVG-file %1").arg(m_filename));
    }
}

QString ExportTask::taskName() const
{
    static const QString EXPORT_TASK("Export");
    return EXPORT_TASK;
}

QString ExportTask::getOutputFilename(const QString& filename)
{
    QFileInfo info(filename);
    QString outputFilename(m_outputDir);
    outputFilename = outputFilename.append(QDir::separator());
    outputFilename = outputFilename.append(info.baseName());

    QString sizePostfix;
    if (m_size.width() == 0 || m_size.height() == 0) {
        sizePostfix = "_%1.png";
        int val = 0;
        if (m_size.width() == 0) {
            val = m_size.height();
        } else if (m_size.height() == 0) {
            val = m_size.width();
        }
        outputFilename = outputFilename.append(sizePostfix.arg(val));
    } else {
        sizePostfix = "_%1x%2.png";
        outputFilename = outputFilename.append(sizePostfix.arg(m_size.width()).arg(m_size.height()));
    }

    return outputFilename;
}
