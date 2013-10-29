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

#ifndef TASK_H
#define TASK_H

#include <QtCore/QRunnable>
#include <QtCore/QString>
class Logger;

class Task : public QRunnable {
public:
    Task(const QString& filename) : m_filename(filename) {}
    virtual ~Task() {}
public:
    virtual void run() = 0;
    virtual QString taskName() const = 0;
    virtual QString filename() const { return m_filename; }
    const Logger& logger() const { return *m_logger; }
protected:
    QString m_filename;
    Logger* m_logger;
};

#endif // TASK_H
