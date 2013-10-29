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

#ifndef NODEFINDER_H
#define NODEFINDER_H

#include <QDebug>
#include <QDomNode>
#include <QList>
#include <QString>

#include "nodewalker.h"

class NodeFilter {
public:
    virtual bool operator()(QDomNode node) = 0;
};

class NodeFinder : public NodeWalker::Visitor
{
public:
    static QList<QDomNode> find(QDomNode node,
				NodeFilter* filter);
private:
    NodeFinder(QDomNode node, NodeFilter* filter);
    bool visitNode(QDomNode node);
    QList<QDomNode> privateFind();
    QDomNode m_node;
    NodeFilter* m_filter;
    QList<QDomNode> m_results;
};

#endif
