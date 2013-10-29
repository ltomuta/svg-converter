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

#include "emptynoderemoverstep.h"
#include "errorcodes.h"
#include "ruleengine.h"
#include "nodefinder.h"
#include "tracer.h"

EmptyNodeRemoverStep::EmptyNodeRemoverStep(Logger& logger, QObject *parent) :
    QObject(parent),
    ProcessorStep(logger)
{
    Tracer trace(Q_FUNC_INFO);
}

EmptyNodeRemoverStep::~EmptyNodeRemoverStep()
{
    Tracer trace(Q_FUNC_INFO);
}

static struct EmptyFilter : public NodeFilter {
    bool operator()(QDomNode node) {
	if(!node.hasChildNodes() && !node.hasAttributes() && !node.isText()) {
	    return true;
	}
	return false;
    }
} emptyFilter;

QDomDocument EmptyNodeRemoverStep::process(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);
    QList<QDomNode> nodes = NodeFinder::find(svgDoc, &emptyFilter);
    foreach(QDomNode node, nodes) {
	node.parentNode().removeChild(node);
    }
    return svgDoc;
}

QString EmptyNodeRemoverStep::description()
{
    Tracer trace(Q_FUNC_INFO);
    return tr("Empty node remover");
}
