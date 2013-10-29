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

#ifndef NODEFILTERSTEP_H
#define NODEFILTERSTEP_H

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QPair>
#include <QDomNode>
#include "processorstep.h"

class RuleEngine;
class Logger;

class NodeFilterStep : public QObject, public ProcessorStep
{
    Q_OBJECT
public:
    explicit NodeFilterStep(const RuleEngine& rules, Logger& logger, QObject *parent = 0);
    virtual ~NodeFilterStep();
public: // From ProcessorStep
    virtual QDomDocument preProcess(QDomDocument svgDoc);
    virtual QDomDocument process(QDomDocument svgDoc);
    virtual QString description();
private:
    void getAllNamespacesUsed(QDomDocument svgDoc, QStringList& namespaces);
    QStringList getNamespacesFromNode(QDomNode& node);

    void walkNodes(QDomNode node, QDomNode parentNode);
    void walkAttributes(QDomNode node);
    void addRemovedNodeWarning(QDomNode node);
    void createRemovedNodeWarnings();
private:
    const RuleEngine& m_rules;
    QList<QPair<QDomNode,int> > m_removedNodes;
    int m_inkscapeWarningCount;
};

#endif // FILTERSTEP_H
