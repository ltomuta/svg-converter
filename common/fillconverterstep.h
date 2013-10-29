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

#ifndef FILLCONVERTERSTEP_H
#define FILLCONVERTERSTEP_H

#include <QtCore/QObject>
#include "processorstep.h"

class FillConverterStep : public QObject, public ProcessorStep
{
    Q_OBJECT
public:
    explicit FillConverterStep(Logger& logger, QObject *parent = 0);
    virtual ~FillConverterStep();
public: // From ProcessorStep
    virtual QDomDocument process(QDomDocument svgDoc);
    virtual QString description();
private:
    void convertFillAttributes(QDomDocument svgDoc);
};

#endif
