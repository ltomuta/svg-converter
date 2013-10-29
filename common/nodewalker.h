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

#ifndef NODEWALKER_H
#define NODEWALKER_H

#include <QDebug>
#include <QDomNode>

class NodeWalker
{
public:
    class Visitor {
    public:
	virtual bool visitNode(QDomNode node) = 0;
    };
    
    static void walk(QDomNode node, Visitor* visitor) 
    {
	Q_ASSERT(!node.isNull());
	Q_ASSERT(visitor);

	if(visitor->visitNode(node)) {
	    // Walk child nodes if visitor says yes.
	    QDomNodeList childNodes = node.childNodes();
	    int count = childNodes.count();
	    for(int i=0; i < count; i++) {
		NodeWalker::walk(childNodes.item(i), visitor);
	    }
	}
    }
};

#endif
