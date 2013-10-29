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

#include "logger.h"

Logger::Logger(QObject* parent)
    : QObject(parent)
{
}

Logger::~Logger(){
}

void Logger::clear()
{
    m_messages.clear();
    m_errors.clear();
    m_warnings.clear();
}

void Logger::message(QString message, int index)
{
    if(index == -1) {
	m_messages.append(message);
    } else {
	m_messages.insert(index, message);
    }
}

void Logger::warning(QString warning, int index)
{
    if(index == -1) {
	m_warnings.append(warning);
    } else {
	m_warnings.insert(index, warning);
    }
}

void Logger::error(QString error, int index)
{
    if(index == -1) {
	m_errors.append(error);
    } else {
	m_errors.insert(index, error);
    }
}

const QStringList& Logger::warnings() const
{
    return m_warnings;
}

const QStringList& Logger::messages()  const
{
    return m_messages;
}

const QStringList& Logger::errors() const
{
    return m_errors;
}








