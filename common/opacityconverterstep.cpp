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

#include "opacityconverterstep.h"
#include "tracer.h"

OpacityConverterStep::OpacityConverterStep(Logger& logger, QObject *parent) :
    QObject(parent),
    ProcessorStep(logger)
{
    Tracer trace(Q_FUNC_INFO);
}

OpacityConverterStep::~OpacityConverterStep()
{
    Tracer trace(Q_FUNC_INFO);
}

QDomDocument OpacityConverterStep::process(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);

    // get first (hopefully only) svg-element
    QDomNodeList allNodes = svgDoc.elementsByTagName("svg").at(0).childNodes();
    for (int i = 0; i < allNodes.count(); i++) {
	NodeWalker::walk(allNodes.at(i), this);
    }
    return svgDoc;
}

QString OpacityConverterStep::description()
{
    Tracer trace(Q_FUNC_INFO);
    return tr("Opacity converter");
}

bool OpacityConverterStep::visitNode(QDomNode node) 
{
    Tracer trace(Q_FUNC_INFO);
    // Replace all opacity-attributes with stroke-opacity and fill-opacity.
    
    if(!node.isElement()) {
	return true;
    }
    QDomElement elem = node.toElement();

    QDomAttr attr = elem.attributeNode("opacity");
    if(attr.isNull()) {
	return true;
    }

    QString value = attr.value();

    // Remove old:
    elem.removeAttribute(attr.name());

    // Create new:
    elem.setAttribute("stroke-opacity", value);
    elem.setAttribute("fill-opacity", value);

    return true;
}
