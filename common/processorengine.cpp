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

#include "processorengine.h"
#include "errorcodes.h"
#include "tracer.h"
#include "logger.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QMutexLocker>

#include "ruleengine.h"
#include "nodefilterstep.h"
#include "gradientprocessorstep.h"
#include "opacityconverterstep.h"
#include "emptynoderemoverstep.h"
#include "statisticsprocessorstep.h"
#include "validationstep.h"
#include "pathconverterstep.h"
#include "fillconverterstep.h"
#include "stylesheetconverterstep.h"

const char* VERSION = "0.9.5";

QString ProcessorEngine::getVersionString()
{
    return tr("SVG Converter - Version %1 (Compiled %2)\nCopyright (C) 2011 Nokia").arg(VERSION).arg(__TIMESTAMP__);
}

QString ProcessorEngine::getVersionStringFormatted()
{
    return tr("<div align='center'><h1>SVG to SVG-Tiny converter</h1>\n\n<h2>Version %1</h2>\n<b>Compiled %2</b>\n\n\n<i>Copyright &copy; 2011 Nokia</i></div>").arg(VERSION).arg(__TIMESTAMP__);
}

ProcessorEngine::ProcessorEngine(const RuleEngine& rules, Logger& logger, QObject *parent) :
    QObject(parent), m_rules(rules), m_logger(logger)
{
    Tracer trace(Q_FUNC_INFO);

    // Validation steps. The order for some steps is important.
    
    // 1st: sme validation if input data
    addProcessorStep(new ValidationStep(m_logger));
    // 2nd: style sheet processor (depends on nodes
    //      that will be removed in the filter step.
    addProcessorStep(new StyleSheetConverterStep(m_logger));
    // 3rd: node filter 
    addProcessorStep(new NodeFilterStep(rules, m_logger));
    addProcessorStep(new GradientProcessorStep(m_logger));
    addProcessorStep(new OpacityConverterStep(m_logger));
    addProcessorStep(new PathConverterStep(m_logger));
    addProcessorStep(new FillConverterStep(m_logger));
    addProcessorStep(new EmptyNodeRemoverStep(m_logger));
    // Last step: gather statistics 
    addProcessorStep(new StatisticsProcessorStep(m_logger));
}

ProcessorEngine::~ProcessorEngine()
{
    Tracer trace(Q_FUNC_INFO);
    foreach(ProcessorStep* step, m_steps) {
        delete step;
        step = 0;
    }
    m_steps.clear();
}

void ProcessorEngine::addProcessorStep(ProcessorStep* step)
{
    QMutexLocker locker(&m_mutex);
    Tracer trace(Q_FUNC_INFO);
    m_steps.enqueue(step);
}

void ProcessorEngine::resetSteps()
{
    QMutexLocker locker(&m_mutex);
    Tracer trace(Q_FUNC_INFO);
    m_steps.clear();
}

int ProcessorEngine::process(const QString& inputFile, const QString& outputFile)
{
    QMutexLocker locker(&m_mutex);
    Tracer trace(Q_FUNC_INFO);

    int retVal = EXIT_SUCCESS;

    // First read the input file into QDomDocument
    QDomDocument inputDOM = readInputXML(inputFile);
    if (inputDOM.isNull()) {
	m_logger.error(tr("XML-parsing has failed for file %1").arg(inputFile));
        return EXIT_FAILURE;
    }

    // New dom for SVGT
    QDomDocument outputDOM;

    while (!m_steps.isEmpty()) {
        ProcessorStep* step = m_steps.dequeue();
	//m_logger.message(tr("Running step %1 ...").arg(step->description()));

        // pre processing stuff
        QDomDocument preProcessOutputDOM = step->preProcess(inputDOM);
        Q_ASSERT(!preProcessOutputDOM.isNull());

        // actual processing
        QDomDocument processOutputDOM = step->process(preProcessOutputDOM);
        Q_ASSERT(!processOutputDOM.isNull());

        // post processing stuff
        QDomDocument postProcessOutputDOM = step->postProcess(processOutputDOM);
        Q_ASSERT(!postProcessOutputDOM.isNull());

        if (m_steps.count() > 0) {
            // Set latest DOM as the next input DOM
            inputDOM = postProcessOutputDOM;
        } else {
            // No more steps so store the latest DOM
            outputDOM = postProcessOutputDOM;
        }
        // No ownership
        step = 0;
    }

    retVal = writeOutputXML(outputFile, outputDOM);

    return retVal;
}


void ProcessorEngine::validateFileName(QString fileName) {

    // Generate warnings that may help with the SVG->MIF converter on the S60 SDK.
    // These warning rules are based on hunches. MIFconverter is unlogical and picky.
    
    if(fileName.length() > 15) {
        m_logger.warning(QObject::tr("Possible problem when doing SVG->MIF conversion using S60 SDK: filename '%1' is quite long.").arg(fileName));
    }

    foreach(QChar c, fileName) {
        if(!c.isLetterOrNumber()) {
            m_logger.warning(QObject::tr("Possible problem when doing SVG->MIF conversion using S60 SDK: filename '%1' contains characters that are not letters or numbers.").arg(fileName));
	    break;
	}
    }
}

QDomDocument ProcessorEngine::readInputXML(const QString& inputFile)
{
    Tracer trace(Q_FUNC_INFO);
    QDomDocument dom;

    QFileInfo info(inputFile);
    //m_logger.message(tr("Reading file SVG-image from file %1").arg(QDir::toNativeSeparators(info.absoluteFilePath())));

    validateFileName(info.baseName());

    // Open the input file for reading
    QFile file(inputFile);
    if (!file.open(QIODevice::ReadOnly)) {
	m_logger.error(tr("Could not open file %1 for reading").arg(inputFile));
	return dom;
    }

    // Parse DOM from the file
    QString errorString;
    int errorLine;
    int errorColumn;
    if (!dom.setContent(&file, false, &errorString, &errorLine, &errorColumn)) {
	m_logger.error(tr("Error parsing file %1 on line %2 column %3").arg(inputFile).arg(errorLine).arg(errorColumn));
        file.close();
	return dom;
    }

    // close the file
    file.close();

    return dom;
}

int ProcessorEngine::writeOutputXML(const QString& outputFile, QDomDocument dom)
{
    Tracer trace(Q_FUNC_INFO);

    QFileInfo info(outputFile);
    //m_logger.message(tr("Writing SVG-image to file %1").arg(QDir::toNativeSeparators(info.absoluteFilePath())));
    
    // Open the input file for reading
    QFile file(outputFile);
    if (!file.open(QIODevice::WriteOnly)) {
	m_logger.error(tr("Could not open file %1").arg(outputFile));
        return ERROR_WRITING_FILE;
    }

    qint64 len = file.write(dom.toByteArray());

    // Warn for big output files.
    if(len >= 300*1024) {
	m_logger.warning(tr("Output file is quite big (%1 kB). This may lead to performance problems.").arg(len>>10));
    }

    m_logger.message(tr("Wrote %1 bytes to file %2").arg(len).arg(outputFile));
    file.close();

    return EXIT_SUCCESS;
}
