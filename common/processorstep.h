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

#ifndef PROCESSORSTEP_H
#define PROCESSORSTEP_H

#include <QtCore/QSharedPointer>
#include <QtCore/QStringList>
#include <QtXml/QDomDocument>
#include "logger.h"

// Typedefs
// typedef QSharedPointer<QDomDocument> DomPointer;

class ProcessorStep
{
    // Public interface that all ProcessorSteps must implement
public:
    ProcessorStep(Logger& logger) : m_logger(logger) {}

    virtual QDomDocument preProcess(QDomDocument svgDoc) { return svgDoc; } // optional
    virtual QDomDocument process(QDomDocument svgDoc) = 0;
    virtual QDomDocument postProcess(QDomDocument svgDoc) { return svgDoc; } // optional
    virtual QString description() = 0;
    virtual ~ProcessorStep() {}
protected:
    Q_DISABLE_COPY(ProcessorStep);
    Logger& m_logger;
};

#endif // PROCESSORSTEP_H
