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

#include "fillconverterstep.h"
#include "tracer.h"
#include "nodefinder.h"

FillConverterStep::FillConverterStep(Logger& logger, QObject *parent) :
    QObject(parent), ProcessorStep(logger)
{ 
    Tracer trace(Q_FUNC_INFO);
}

FillConverterStep::~FillConverterStep()
{
    Tracer trace(Q_FUNC_INFO);
}

QDomDocument FillConverterStep::process(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);
    QDomElement svg = svgDoc.elementsByTagName("svg").at(0).toElement(); // The 1st SVG element
    convertFillAttributes(svgDoc);
    return svgDoc;
}

QString FillConverterStep::description()
{
    Tracer trace(Q_FUNC_INFO);
    return tr("Fill converter");
}



// Filter to find <path> elements.
static struct FillFilter : public NodeFilter {
    bool operator()(QDomNode node) {
	QDomElement elem = node.toElement();
	if(elem.isNull()) {
	    return false;
	}
	QDomAttr fillAttr = elem.attributeNode("fill");
	if(!fillAttr.isNull()) {
	    return true;
	}
	QDomAttr styleAttr = elem.attributeNode("style");
	if(!styleAttr.isNull()) {
	    return true;
	}
	return false;
    }
} fillFilter;


static void fixStyleAttribute(QDomAttr attr) {
    Tracer trace(Q_FUNC_INFO);
    // <path style="fill: url(#radialGradient4401) rgb(0, 0, 0);"

    // Find a suitable pattern with regexp, the
    // captured part is to be replaced.
    QRegExp re("fill: *url.+( *rgb.+)[;$]");
    re.setMinimal(true);
    QString value = attr.value();
    int index = re.indexIn(value);

    // 1st capture is the whole string,
    // following capture is the rgb-part.
    if(index != -1) {
	value.replace(re.cap(1), "");
    }
    attr.setValue(value);
}

static void fixFillAttribute(QDomAttr attr) {
    Tracer trace(Q_FUNC_INFO);
    //<path  fill="url(#radialGradient4401) rgb(0, 0, 0)" so

    // Find a suitable pattern with regexp, the
    // captured part is to be replaced.
    QRegExp re("url.+( *rgb.+)$");
    re.setMinimal(true);
    QString value = attr.value();
    int index = re.indexIn(value);

    // 1st capture is the whole string,
    // following capture is the rgb-part.
    if(index != -1) {
 	value.replace(re.cap(1), "");
    }
    attr.setValue(value);
}

void FillConverterStep::convertFillAttributes(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);

    // Remove fallback color from fills like this, as
    // S60 displays the fallback instead of the primary
    // <path style="fill: url(#radialGradient4401) rgb(0, 0, 0);"
    // or
    // <path fill="url(#radialGradient4401) rgb(0, 0, 0)"
    // In the latter case there should also be no whitespace after the url ending ')'.

    // Find all tags that have a 'fill'-attribute, or a style-attribute that contains 'fill'.
    QList<QDomNode> fillNodes = NodeFinder::find(svgDoc, &fillFilter);
    foreach(QDomNode node, fillNodes) {

	QDomElement elem = node.toElement();

	QDomAttr styleAttr = elem.attributeNode("style");
	if(!styleAttr.isNull()) {
	    fixStyleAttribute(styleAttr);
	}

	QDomAttr fillAttr = elem.attributeNode("fill");
	if(!fillAttr.isNull()) {
	    fixFillAttribute(fillAttr);
	}
    }
}
