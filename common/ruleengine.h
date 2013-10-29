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

#ifndef RULEENGINE_H
#define RULEENGINE_H

#include <QtCore/QObject>
#include <QtCore/QHash>

// Forward declarations
class QDomDocument;
class QDomNode;
class QDomElement;
class QDomAttr;
class Logger;

class RuleEngine : public QObject
{
    Q_OBJECT
public:
    explicit RuleEngine(Logger& logger, QObject *parent = 0);
    virtual ~RuleEngine();

    int setRulesFile(const QString& ruleFilename);
    bool isAcceptableNode(QDomNode& node) const;
    bool isAcceptableAttribute(QDomNode& node, QDomAttr& attr) const;
private:
    int readFile(const QString& ruleFilename, QDomDocument& dom);
    int handleRuleDOM(const QDomDocument& dom);
    int handleAllowedElement(const QDomElement& element, QStringList& allowedAttributes);

    // debug
    void dumpRules();
private:
    QHash<QString, QStringList> m_allowed;
    Logger& m_logger;
};

#endif // RULEENGINE_H
