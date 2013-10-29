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

#include "gradientprocessorstep.h"
#include "tracer.h"
#include "errorcodes.h"
#include "ruleengine.h"

#include "nodefinder.h"

GradientProcessorStep::GradientProcessorStep(Logger& logger, QObject *parent) 
    : QObject(parent), ProcessorStep(logger)
{
    Tracer trace(Q_FUNC_INFO);
}

GradientProcessorStep::~GradientProcessorStep()
{
    Tracer trace(Q_FUNC_INFO);

}

static struct LinearGradientFilter : public NodeFilter {
    bool operator()(QDomNode node) {
	if(node.toElement().tagName() == "linearGradient") {
	    return true;
	}
	return false;
    }
} linearGradientFilter;

static struct RadialGradientFilter : public NodeFilter {
    bool operator()(QDomNode node) {
	if(node.toElement().tagName() == "radialGradient") {
	    return true;
	}
	return false;
    }
} radialGradientFilter;

static struct StopInGradientFilter : public NodeFilter {
    bool operator()(QDomNode node) {
	QDomElement elem = node.toElement();
	if(elem.tagName() == "stop" &&
                (node.parentNode().nodeName() == "linearGradient" ||
                 node.parentNode().nodeName() == "radialGradient")) {
	    return true;
	}
	return false;
    }
} stopInGradientFilter;

struct IdFilter : public NodeFilter {
    IdFilter(QString value) : m_value(value) {}
    bool operator()(QDomNode node) {
	QDomElement elem = node.toElement();
	QDomAttr attr = elem.attributeNode("id");
	if(!attr.isNull() && attr.value() == m_value) {
	    return true;
	}
	return false;
    }
private:
    QString m_value;
};

QDomDocument GradientProcessorStep::process(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);

    // Find all "linearGradient" nodes
    QList<QDomNode> linearGradientNodes = NodeFinder::find(svgDoc, &linearGradientFilter);

    // Find all "radialGradient" nodes
    QList<QDomNode> radialGradientNodes = NodeFinder::find(svgDoc, &radialGradientFilter);

    // Find all "stop" nodes inside either of the gradient elements
    QList<QDomNode> stopInGradientNodes  = NodeFinder::find(svgDoc, &stopInGradientFilter);

    // Convert attribute percentages to decimal notation in each of the above nodes:

    QStringList linearAttrs;
    linearAttrs << "x1" << "y1" << "x2" << "y2"; 
    foreach(QDomNode node, linearGradientNodes) {
	convertPercentages(node.toElement(), linearAttrs);
    }

    QStringList radialAttrs;
    radialAttrs << "cx" << "cy" << "fx" << "fy" << "r"; 
    foreach(QDomNode node, radialGradientNodes) {
	convertPercentages(node.toElement(), radialAttrs);
    }

    QStringList stopAttrs; 
    stopAttrs << "offset";
    foreach(QDomNode node, stopInGradientNodes) {
	convertPercentages(node.toElement(), stopAttrs);
    }

    // Reference conversion case
    // Some gradient tags inside <def> refer to other gradient tags with an id.
    // This does not work on S60. Conversion steps to fix:
    // - Find all gradient elements
    // - Check if it has an attribute "xlink:href", and remove it
    // - Find the referred element with the id from the xlink:href
    // - Add the children of the referred element to the gradient
    convertReferences(svgDoc, linearGradientNodes);
    convertReferences(svgDoc, radialGradientNodes);

    return svgDoc;
}

QString GradientProcessorStep::description()
{
    Tracer trace(Q_FUNC_INFO);
    return tr("Gradient converter");
}

void GradientProcessorStep::convertReferences(QDomDocument svgDoc, QList<QDomNode> nodes) 
{
    Tracer trace(Q_FUNC_INFO);
    foreach(QDomNode node, nodes) {
	QDomElement elem = node.toElement();
	QDomAttr attr = elem.attributeNode("xlink:href");
	
	// The node must have a reference, otherwise skip it.
	if(attr.isNull()) {
	    continue;
	}

	// Find the referred node.
	QString referredId = attr.value().mid(1);
	IdFilter filter(referredId);
	QList<QDomNode> referredNodes = NodeFinder::find(svgDoc, &filter);

	// If more than one is found, it would be an error in the xml file.
	if(referredNodes.count() != 1)  {
	    m_logger.warning(tr("Can't find referred node: %1").arg(referredId));
	    continue;
	}

	QDomNode referredNode = referredNodes[0];

	// Allow references to the two gradients.
	if(referredNode.nodeName() != "linearGradient" &&
                referredNode.nodeName() != "radialGradient") {
	    m_logger.warning(tr("Bad reference in gradient: %1").arg(referredId));
	    // warning, skip
	    continue;
	}

	// Remove old xlink attr
	elem.removeAttribute(attr.name());

	// Copy nodes from the referred node.
	for(QDomNode n = referredNode.firstChild(); !n.isNull(); n = n.nextSibling()) {
	    QDomElement e = n.toElement();
	    if (!e.isNull()) {
		elem.insertAfter(e.cloneNode(), QDomNode() /*null node, no specific insertion order */);
	    }
	}
    }
}

void GradientProcessorStep::convertPercentages(QDomElement elem,
					       QStringList attrs)
{
    Tracer trace(Q_FUNC_INFO);
    foreach(QString attrName, attrs) {

	QDomAttr attr = elem.attributeNode(attrName);

	if(attr.isNull()) {
	    // Attribute not found.
	    continue;
	}

	QString value = attr.value();
	if(!value.endsWith("%")) {
	    // Attribute value not in percentage format.
	    continue;
	}

	// Convert from percentage to decimal with one digit after the decimal point.
	int integer = value.left(value.length() - 1).toInt();
	QString newValue = QString("%1").arg(double(integer)/100, 0, 'f', 1);

 	// Remove old:
 	elem.removeAttribute(attr.name());
 	// Create new:
 	elem.setAttribute(attrName, newValue);
    }
}


// bool GradientProcessorStep::visitNode(QDomNode node) 
// {
//     // Replace all opacity-attributes with stroke-opacity and fill-opacity.

//     if(!node.isElement()) {
// 	return true;
//     }
//     QDomElement elem = node.toElement();

//     // Process these two tags:
//     if(elem.tagName() == "linearGradient" ||
//        elem.tagName() == "radialGradient") {

// 	// .. and these attributes:
// 	QStringList attrs;

// 	// in linearGradient:
// 	attrs << "x1" << "y1" << "x2" << "y2"; 

// 	// in radialGradient: 
// 	attrs << "cx" << "cy" << "fx" << "fy" << "r"; 
// 	// Note: SVGT does not have fx and fy attributes in the spec of radialGradient.

// 	convertPercentages(elem, attrs);
//     }
//     else
//     {
// 	// Process the stop tags within gradient tags:
// 	if((node.parentNode().nodeName() == "linearGradient" ||
// 	    node.parentNode().nodeName() == "radialGradient") &&
// 	   elem.tagName() == "stop") {
// 	    QStringList attrs; 
// 	    attrs << "offset";
// 	    convertPercentages(elem, attrs);
// 	}
//     }

//     return true;
// }
