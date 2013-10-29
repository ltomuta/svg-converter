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

#include "ruleengine.h"
#include "tracer.h"
#include "logger.h"
#include "errorcodes.h"

#include <cstdlib>
#include <iostream>
#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNodeList>
#include <QtXml/QDomNode>
#include <QtXml/QDomAttr>
#include <QtXml/QDomElement>

RuleEngine::RuleEngine(Logger& logger, QObject *parent) :
    QObject(parent), m_logger(logger)
{
    Tracer trace(Q_FUNC_INFO);

}

RuleEngine::~RuleEngine()
{
    Tracer trace(Q_FUNC_INFO);
}

int RuleEngine::setRulesFile(const QString& ruleFilename)
{
    Tracer trace(Q_FUNC_INFO);

    int retVal = EXIT_SUCCESS;

    // Read the rules file
    QDomDocument dom;
    retVal = readFile(ruleFilename, dom);
    if (retVal) {
        return retVal;
    }

    // Parse the rules into usable form
    retVal = handleRuleDOM(dom);
    if (retVal) {
        return retVal;
    }

    // Print out the current ruleset
    //dumpRules();

    return retVal;
}

bool RuleEngine::isAcceptableNode(QDomNode& node) const
{
    Tracer trace(Q_FUNC_INFO);

    QString nodeName = node.nodeName();

    if (!m_allowed.contains(nodeName)) {
        return false;
    }

    return true;
}

bool RuleEngine::isAcceptableAttribute(QDomNode& node, QDomAttr& attr) const
{
    Tracer trace(Q_FUNC_INFO);
    QString nodeName = node.nodeName();

    if (!m_allowed.contains(nodeName)) {
        return false;
    } else {
        if (!m_allowed[nodeName].contains(attr.nodeName())) {
            return false;
        }
    }

    return true;
}

int RuleEngine::readFile(const QString& ruleFilename, QDomDocument& dom)
{
    Tracer trace(Q_FUNC_INFO);

    QFile file(ruleFilename);
    if (!file.open(QIODevice::ReadOnly)) {
        m_logger.error(tr("Error reading conversion rules from file %1").arg(ruleFilename));
        return ERROR_READING_RULES;
    }

    QString errorString;
    int errorLine;
    int errorColumn;

    if (!dom.setContent(&file, false, &errorString, &errorLine, &errorColumn)) {
        m_logger.error(tr("Error parsing rules on row %1 column %2: %3").arg(errorLine).arg(errorColumn).arg(errorString));
        return ERROR_PARSING_RULES;
    }

    return EXIT_SUCCESS;
}

int RuleEngine::handleRuleDOM(const QDomDocument& dom)
{
    Tracer trace(Q_FUNC_INFO);

    QDomNodeList allowedNodes = dom.elementsByTagName("allowed").at(0).childNodes();
    for (int i = 0; i < allowedNodes.count(); i++) {
        QDomNode node = allowedNodes.at(i);
        if (node.isElement()) {
            QDomElement elem = node.toElement();
            if (elem.nodeName() == "element" && elem.hasAttribute("name")) {
                QString name = elem.attributeNode("name").value();
                QStringList attributes;
                int retVal = handleAllowedElement(elem, attributes);
                if (retVal) {
                    m_logger.error(tr("Error in rules. No name attribute found."));
                    return retVal;
                }

                attributes.removeDuplicates();
                m_allowed.insert(name, attributes);
            } else {
                m_logger.error(tr("Error rules. Wrong element or no name-attribute found"));
                return ERROR_PARSING_RULES;
            }
        }
    }

    return EXIT_SUCCESS;
}

int RuleEngine::handleAllowedElement(const QDomElement& element, QStringList& allowedAttributes)
{
    Tracer trace(Q_FUNC_INFO);
    QDomNodeList children = element.childNodes();
    for (int i = 0; i < children.count(); i++) {
        QDomNode child = children.at(i);
        if (child.isElement()) {
            QDomElement childElement = child.toElement();
            if (childElement.nodeName()== "attribute") {
                if (childElement.hasAttribute("name")) {
                    QString name = childElement.attributeNode("name").value();
                    allowedAttributes.append(name);
                } else {
                    m_logger.error(tr("Error in rules. Attribute-element has no name-attribute"));
                    return ERROR_PARSING_RULES;
                }
            } else {
                m_logger.error(tr("Error in rules. Not an attribute-element"));
                return ERROR_PARSING_RULES;
            }
        }
    }
    return EXIT_SUCCESS;
}


void RuleEngine::dumpRules()
{
    Tracer trace(Q_FUNC_INFO);
    std::cout << "CURRENT RULESET:\n\n";
    std::cout << "ALLOWED ELEMENTS AND THEIR ATTRIBUTES:\n";
    foreach (QString key, m_allowed.keys()) {
        std::cout << "ELEMENT:" << key.toStdString();
        foreach (QString value, m_allowed.value(key)) {
            std::cout << " - ATTRIBUTE:" << value.toStdString();
        }
    }
}
