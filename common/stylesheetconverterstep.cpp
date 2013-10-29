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

#include "stylesheetconverterstep.h"
#include "errorcodes.h"
#include "ruleengine.h"
#include "nodefinder.h"
#include "tracer.h"

StyleSheetConverterStep::StyleSheetConverterStep(Logger& logger, QObject *parent) :
    QObject(parent),
    ProcessorStep(logger)
{
    Tracer trace(Q_FUNC_INFO);
}

StyleSheetConverterStep::~StyleSheetConverterStep()
{
    Tracer trace(Q_FUNC_INFO);
}

// Filter to find style sheets.
static struct StyleFilter : public NodeFilter {
    bool operator()(QDomNode node) {
	QDomElement elem = node.toElement();
	if(elem.tagName() == "style") {
	    QDomAttr attr = elem.attributeNode("type");
	    if(!attr.isNull() && attr.value() == "text/css" &&
                    !elem.text().isNull()) {
		return true;
	    }
	}
	return false;
    }
} styleFilter;

void StyleSheetConverterStep::buildStyleMap(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);

    // Grab all <style> -nodes.
    QList<QDomNode> nodes = NodeFinder::find(svgDoc, &styleFilter);

    // This function creates a map between style sheet keys and values,
    // from lines like these:
    // .fil4 {fill:none;fill-rule:nonzero}
    // .full-specularity	{opacity:1;}
    
    // RegExp to parse the lines above:
    QRegExp re("\\.(\\S+)[\\t\\s]+\\{(\\S+)\\}"); 
    re.setMinimal(true);

    int pos = 0;
    foreach(QDomNode node, nodes) {
	QDomElement elem = node.toElement();
	QString data = elem.text();

	while ((pos = re.indexIn(data, pos)) != -1) {
	    pos += re.matchedLength();
	    if(re.captureCount() == 2) {
		m_styleMap[re.cap(1)] = re.cap(2);
	    } else {
		m_logger.error(tr("Error parsing style sheet"));
	    }
	}

	// Finally remove the <style> node, it's not needed anymore.
 	node.parentNode().removeChild(node);
    }
}

// Filter to find nodes with class-attributes
static struct ClassFilter : public NodeFilter {
    bool operator()(QDomNode node) {
	QDomElement elem = node.toElement();
	QDomAttr attr = elem.attributeNode("class");
	if(!attr.isNull()) {
	    return true;
	}	    
	return false;
    }
} classFilter;

void StyleSheetConverterStep::convertClassAttributes(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);

    // This function finds all nodes with the 'class'-attribute.
    // It replaces this with a 'style'-attribute that contains
    // the style data from the stylesheet that was referenced by 
    // the 'class'-attribute.

    // Grab all nodes with the 'class'-attribute.
    QList<QDomNode> nodes = NodeFinder::find(svgDoc, &classFilter);
    foreach(QDomNode node, nodes) {
	QDomElement elem = node.toElement();

	// Grab the style identifier keys from the 'class'-attribute.
	// There may be several separated why whitespace.
	QDomAttr classAttr = elem.attributeNode("class");
	QStringList keys = classAttr.value().split(QRegExp("\\s+"));

	// Remove the 'class'-attribute, no need for it anymore.
	elem.removeAttribute(classAttr.name());

	// Build a 'style'-attribute. Start with the old style if available.
	QString styleValue; 
	QDomAttr styleAttr = elem.attributeNode("style");
	if(!styleAttr.isNull()) {
	    styleValue = styleAttr.value();
	}

	// Loop through the keys and find the corresponding style data.
	foreach(QString key, keys) {
	    styleValue += m_styleMap[key];
	    // To be safe, make sure to end with ';' so that the following
	    // data is separated properly.
	    if(!styleValue.endsWith(';')) {
		styleValue += ';';
	    }
	}

	// Finally, set the new 'style'-attribute, overwriting
	// a possible old one.
	elem.setAttribute("style", styleValue);

    }
}

QDomDocument StyleSheetConverterStep::process(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);
    buildStyleMap(svgDoc);
    convertClassAttributes(svgDoc);
    return svgDoc;
}

QString StyleSheetConverterStep::description()
{
    Tracer trace(Q_FUNC_INFO);
    return tr("Style sheet converter");
}
