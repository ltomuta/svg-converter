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

#include "conversiontask.h"
#include "ruleengine.h"
#include "processorengine.h"
#include "tracer.h"

#include <QtCore/QObject> // tr
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QDebug>

ConversionTask::ConversionTask(const QString& filename, const QString& outputFilename) :
    Task(filename), m_outputFilename(outputFilename)
{
    Tracer trace(Q_FUNC_INFO);
    m_logger = new Logger;
    setupEngine();
}

ConversionTask::~ConversionTask()
{
    Tracer trace(Q_FUNC_INFO);
    delete m_engine;
    delete m_rules;
    delete m_logger;
}

void ConversionTask::run()
{
    Tracer trace(Q_FUNC_INFO);
    Q_ASSERT(m_engine);
    QString header = QObject::tr("*** Converting %1 -> %2").arg(m_filename).arg(m_outputFilename);

    m_logger->message(header);
    if (m_engine->process(m_filename, m_outputFilename) != EXIT_SUCCESS) {
	m_logger->error(QObject::tr("Error processing %1").arg(m_filename));
        qDebug() << m_logger->errors();
    }
    
    m_logger->message("\n");

    // If there are errors or warnings, insert header for clarity.
    if(m_logger->warnings().count() > 0) {
	m_logger->warning(header, 0);
	m_logger->warning("\n");
    }
    if(m_logger->errors().count() > 0) {
	m_logger->error(header, 0);
	m_logger->error("\n");
    }
}

QString ConversionTask::taskName() const
{
    static const QString CONVERSION_TASK("Conversion");
    return CONVERSION_TASK;
}

void ConversionTask::setupEngine()
{
    Tracer trace(Q_FUNC_INFO);

    static const QString RULES_FILE(":/rules.xml");

    // Create rules
    m_rules = new RuleEngine(*m_logger);
    if (m_rules->setRulesFile(RULES_FILE) != EXIT_SUCCESS) { // EXIT_SUCCESS
	m_logger->error(QObject::tr("Could not read conversion rules from file %1").arg(RULES_FILE));
        return;
    }

    // Create engine
    m_engine = new ProcessorEngine(*m_rules, *m_logger);
}

