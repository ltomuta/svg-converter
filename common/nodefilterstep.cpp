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

#include "nodefilterstep.h"
#include "tracer.h"
#include "errorcodes.h"
#include "ruleengine.h"
#include "processorengine.h"

#include <QtCore/QBuffer>
#include <QtCore/QStringList>
#include <QtXml/QDomNodeList>
#include <QtXml/QDomNamedNodeMap>
#include <QtXmlPatterns/QXmlQuery>

NodeFilterStep::NodeFilterStep(const RuleEngine& rules, Logger& logger, QObject *parent) :
    QObject(parent), ProcessorStep(logger), m_rules(rules)
{
    Tracer trace(Q_FUNC_INFO);
}

NodeFilterStep::~NodeFilterStep()
{
    Tracer trace(Q_FUNC_INFO);
}

QDomDocument NodeFilterStep::preProcess(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);

    return svgDoc;
}

void NodeFilterStep::addRemovedNodeWarning(QDomNode node) 
{
    Tracer trace(Q_FUNC_INFO);

    // Skip warnings for elements and attributes for certain Inkscape
    // stuff. They're not important to be shown to the user.
    // Instead gather statistics for later display.
    if(node.nodeName().contains("sodipodi") ||
            node.nodeName().contains("inkscape")) {
	m_inkscapeWarningCount++;
	return;
    }

    // For similar warnings, keep count instead of displaying
    // the same warning many times.

    bool found = false;
    QPair<QDomNode,int> pair;
    for(int i=0; i < m_removedNodes.count(); i++) {
	QDomNode compareNode = m_removedNodes[i].first;

	// For attribute related warnings, check both tag name
	// and attribute name to determine equality.

	if(node.isAttr() && compareNode.isAttr()) {
	    if(node.nodeName() == compareNode.nodeName() &&
                    node.parentNode().nodeName() == compareNode.parentNode().nodeName()) {
		m_removedNodes[i].second++;
		found = true;
		break;
	    }
	} 
	else if(node.nodeName() == compareNode.nodeName()) {
	    m_removedNodes[i].second++;
	    found = true;
	    break;
	}
    }
    if(!found) {
	// No older node remove warning found, add a new one with count 1.
	m_removedNodes.append(qMakePair(node,1));
    }
}

void NodeFilterStep::createRemovedNodeWarnings() 
{
    QPair<QDomNode,int> pair;
    foreach(pair, m_removedNodes) {
	if(pair.first.isAttr()) {
	    m_logger.warning(tr("Removed %n unacceptable attribute(s) '%1' in '%2'", "", pair.second)
			     .arg(pair.first.nodeName())
			     .arg(pair.first.parentNode().nodeName()));
	} else {
	    m_logger.warning(tr("Removed %n unacceptable element(s) '%1'", "", pair.second)
			     .arg(pair.first.nodeName()));
	}
    }
}

QDomDocument NodeFilterStep::process(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);

    QDomDocument svgtDoc;
    m_inkscapeWarningCount = 0;

    // Create the XML-declaration
    QDomNode pi = svgtDoc.createProcessingInstruction("xml", "version=\"1.0\"");
    svgtDoc.insertBefore(pi, svgtDoc.firstChild());

    // Create the svg-element
    QString defaultNamespace = "http://www.w3.org/2000/svg";
    QDomElement svg = svgtDoc.createElementNS(defaultNamespace, "svg");
    svgtDoc.insertAfter(svg, pi);
    QString commentString = " Converted with ";
    commentString = commentString.append(ProcessorEngine::getVersionString());
    commentString = commentString.append(" ");
    commentString = commentString.replace("\n", " - ");
    QDomComment comment = svgtDoc.createComment(commentString);
    svgtDoc.insertBefore(comment, svg);

    // Copy allowed root element attributes to destination document:
    QDomNode sourceRoot = svgDoc.elementsByTagName("svg").at(0); // The 1st SVG element 
    QDomNamedNodeMap attrs = sourceRoot.attributes();

    for (int i = 0; i < attrs.count(); i++) {
	QDomAttr attr = attrs.item(i).toAttr();

	// NOTE: Java passes attrs "xmlns:xlink" directly without the passthrough check.
	// If it is something other, like "xmlns:foo", "foo" is checked with passthrough.
	// @TODO: clone this behaviour.

	if(attr.name() == "xmlns" && attr.value() == defaultNamespace) {
	    // skip this, it's already added above.
	    continue;
	}

	if (m_rules.isAcceptableAttribute(svg, attr)) {
	    svg.setAttributeNode(attr);
	} else {
	    addRemovedNodeWarning(attr);
	}
    }
    
    svg.setAttribute("baseProfile", "tiny");
    // @todo: check this, should probably not be automatically added:
    svg.setAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink"); 

    // Walk thru all childnodes
    QDomNodeList allNodes = sourceRoot.childNodes();
    for (int i = 0; i < allNodes.count(); i++) {
        walkNodes(allNodes.at(i), svg);
    }

    createRemovedNodeWarnings();

    if(m_inkscapeWarningCount > 0) {
	m_logger.warning(tr("Removed %1 Inkscape specific attributes.").arg(QString::number(m_inkscapeWarningCount)));
    }

    return svgtDoc;
}

QString NodeFilterStep::description()
{
    Tracer trace(Q_FUNC_INFO);
    return tr("Node filter");
}

void NodeFilterStep::walkNodes(QDomNode node, QDomNode parentNode)
{
    Tracer trace(Q_FUNC_INFO);
    Q_ASSERT(!parentNode.isNull());

    // Check if node is accepted from the rule engine.
    // Text data is always accepted (eg. <tag>textdata</tag>).
    if (m_rules.isAcceptableNode(node) || node.isText()) {
	QDomNode newNode = node.cloneNode(false); // shallow copy
	walkAttributes(newNode);
	parentNode.appendChild(newNode);
	QDomNodeList childNodes = node.childNodes();
        for(int i=0; i < childNodes.count(); i++) {
	    walkNodes(childNodes.item(i), newNode);
	}
    } else {
	addRemovedNodeWarning(node);
    }
}

void NodeFilterStep::walkAttributes(QDomNode node)
{
    Tracer trace(Q_FUNC_INFO);
    Q_ASSERT(!node.isNull());

    QStringList attrsToRemove; 
    QDomNamedNodeMap attributes = node.attributes();

    for (int i = 0; i < attributes.count(); i++) {
	QDomAttr attr = attributes.item(i).toAttr();
	if (!m_rules.isAcceptableAttribute(node, attr)) {
	    attrsToRemove.append(attr.nodeName());
	    addRemovedNodeWarning(attr);
	}
    }

    foreach(QString attrName, attrsToRemove) {
	attributes.removeNamedItem(attrName);
    }
}


// At the moment not used:

// void NodeFilterStep::getAllNamespacesUsed(QDomDocument svgDoc, QStringList& namespaces)
// {
//     Tracer trace(Q_FUNC_INFO);
//     Q_ASSERT(!svgDoc.isNull());

//     QDomNodeList allNodes = svgDoc.childNodes();

//     for (int i = 0; i < allNodes.count(); i++) {
//         QDomNode node = allNodes.at(i);
//         QStringList ns = getNamespacesFromNode(node);
//         namespaces.append(ns);
//     }
//     namespaces.removeDuplicates();
// }

// QStringList NodeFilterStep::getNamespacesFromNode(QDomNode& node)
// {
//     Tracer trace(Q_FUNC_INFO);
//     QStringList namespaces;
//     if (node.hasAttributes()) {
//         QDomNamedNodeMap attributes = node.attributes();
//         for (int i = 0; i < attributes.count(); i++) {
//             QDomNode attrNode = attributes.item(i);
//             if (attrNode.isAttr()) {
//                 QDomAttr attr = attrNode.toAttr();
//                 if (attr.name().startsWith("xmlns")) {
//                     namespaces.append(attr.value());
//                 }
//             }
//         }
//     }
//     return namespaces;
// }

