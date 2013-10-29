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

#include "nodefinder.h"
#include "tracer.h"


QList<QDomNode> NodeFinder::find(QDomNode node,
				 NodeFilter* filter) {
    Q_ASSERT(filter);
    Tracer trace(Q_FUNC_INFO);
    NodeFinder finder(node, filter);
    return finder.privateFind();
}

NodeFinder::NodeFinder(QDomNode node,
		       NodeFilter* filter)
    : m_node(node),
      m_filter(filter)
{
    Tracer trace(Q_FUNC_INFO);
}

QList<QDomNode> NodeFinder::privateFind() {
    Tracer trace(Q_FUNC_INFO);
    NodeWalker::walk(m_node, this);
    return m_results;
}

bool NodeFinder::visitNode(QDomNode node) {
    Tracer trace(Q_FUNC_INFO);

    QDomElement elem = node.toElement();
    QDomAttr attr;
    
    if(!elem.isNull()) {
	if(m_filter) {
	    if((*m_filter)(node)) {
		m_results.append(node);
	    }
	}
    }    
    return true; // continue walking
}




