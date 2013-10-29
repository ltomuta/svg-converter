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

#ifndef PROCESSORENGINE_H
#define PROCESSORENGINE_H

// Platform includes
#include <QtCore/QObject>
#include <QtCore/QQueue>
#include <QtCore/QMutex>
#include <QtCore/QSharedPointer>
#include <QtCore/QStringList>
#include <QtXml/QDomDocument>

// Own includes
#include "processorstep.h"
#include "logger.h"

// Forward declarations
class QDomDocument;
class RuleEngine;
class Logger;

/**
 * ProcessorEngine.
 *
 * Handles the processing pipeline
 */
class ProcessorEngine : public QObject
{
    Q_OBJECT
public:
    explicit ProcessorEngine(const RuleEngine& rules, Logger& logger, QObject *parent = 0);
    static QString getVersionString();
    static QString getVersionStringFormatted();
public:
    virtual ~ProcessorEngine();

    // Add a step to the processing pipeline, takes ownership
    void addProcessorStep(ProcessorStep* step);
    // Clear all steps
    void resetSteps();

    // Process the whole pipeline
    int process(const QString& inputFile, const QString& outputFile);

private:
    QDomDocument readInputXML(const QString& inputFile);
    int writeOutputXML(const QString& outputFile, QDomDocument dom);
    void validateFileName(QString fileName);

private:
    const RuleEngine& m_rules;
    QQueue<ProcessorStep*> m_steps;
    QMutex m_mutex;
    Logger& m_logger;
};

#endif // PROCESSORENGINE_H
