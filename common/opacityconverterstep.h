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

#ifndef OPACITYCONVERTERSTEP_H
#define OPACITYCONVERTERSTEP_H

#include <QtCore/QObject>
#include "processorstep.h"
#include "nodewalker.h"

class OpacityConverterStep : public QObject, 
        public ProcessorStep,
        public NodeWalker::Visitor
{
    Q_OBJECT
public:
    explicit OpacityConverterStep(Logger& logger, QObject *parent = 0);
    virtual ~OpacityConverterStep();
public: // From ProcessorStep
    virtual QDomDocument process(QDomDocument svgDoc);
    virtual QString description();
    // From NodeWalker::Visitor
    bool visitNode(QDomNode node);
};

#endif // OPACITYCONVERTERSTEP_H
