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

#include "validationstep.h"
#include "nodefinder.h"
#include "tracer.h"

ValidationStep::ValidationStep(Logger& logger, QObject *parent) :
    QObject(parent),
    ProcessorStep(logger)
{ 
    Tracer trace(Q_FUNC_INFO);
}

ValidationStep::~ValidationStep()
{
    Tracer trace(Q_FUNC_INFO);
}

static struct ImageFilter : public NodeFilter {
    bool operator()(QDomNode node) {
	return node.toElement().tagName() == "image";
    }
} imageFilter;


QDomDocument ValidationStep::process(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);
    QDomElement svg = svgDoc.elementsByTagName("svg").at(0).toElement(); // The 1st SVG element

    // Some basic checks for the root attributes
    // We prefer that both width and height are defined.
    if(svg.attributeNode("width").isNull()) {
	m_logger.error(tr("Attribute 'width' missing in '%1'").arg(svg.nodeName()));
    }
    if(svg.attributeNode("height").isNull()) {
	m_logger.error(tr("Attribute 'height' missing in '%1'").arg(svg.nodeName()));
    }
    if(svg.attributeNode("viewBox").isNull()) {
	m_logger.warning(tr("Attribute 'viewBox' missing in '%1'. This is required for S60 3rd Edition FP1 or older.").arg(svg.nodeName()));
    }

    QList<QDomNode> imageNodes = NodeFinder::find(svgDoc, &imageFilter);
    if(imageNodes.count() > 0) {
	m_logger.warning(tr("Found %n raster 'image' element(s). Quality may not be optimal.", "", imageNodes.count()));
    }

    return svgDoc;
}

QString ValidationStep::description()
{
    Tracer trace(Q_FUNC_INFO);
    return tr("Validation");
}


