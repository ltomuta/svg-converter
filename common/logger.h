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

#ifndef LOGGER_H
#define LOGGER_H

#include <QtCore/QStringList>
#include <QtCore/QObject>

class Logger : public QObject
{
    Q_OBJECT

public:
    Logger(QObject* parent = 0);
    ~Logger();

    void clear();
    void message(QString msg, int index = -1);
    void error(QString error, int index = -1);
    void warning(QString warning, int index = -1);
    
    const QStringList& messages() const;
    const QStringList& errors() const;
    const QStringList& warnings() const;

private:
    QStringList m_messages;
    QStringList m_errors;
    QStringList m_warnings;
};

#endif // LOGGER_H
