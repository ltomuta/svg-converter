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

#include "statisticsprocessorstep.h"

#include "tracer.h"
#include "nodefinder.h"

StatisticsProcessorStep::StatisticsProcessorStep(Logger& logger, QObject *parent) :
    QObject(parent),
    ProcessorStep(logger)
{
    Tracer trace(Q_FUNC_INFO);
}

StatisticsProcessorStep::~StatisticsProcessorStep()
{
    Tracer trace(Q_FUNC_INFO);

}

struct NodeCounterFilter : public NodeFilter {
    NodeCounterFilter() : m_count(0) {}
    bool operator()(QDomNode node) {
	Q_UNUSED(node);
	// Count every node encountered.
	m_count++;
	return false;
    }
    int m_count;
};

QDomDocument StatisticsProcessorStep::process(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);

    NodeCounterFilter counter;
    NodeFinder::find(svgDoc, &counter);

    // Not very useful information, commented out:
//     m_logger.message(tr("Converted document contains %1 elements").arg(QString::number(counter.m_count)));
	
    // Thesholds are guesses.
    const int warningThreshold = 500;

    if(counter.m_count >= warningThreshold) {
	m_logger.warning(tr("Document contains a lot of elements (%1). This may lead to performance problems.")
			 .arg(QString::number(counter.m_count)));
    }
    return svgDoc;
}

QString StatisticsProcessorStep::description()
{
    Tracer trace(Q_FUNC_INFO);
    return tr("Statistics");
}
