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

#ifndef CONVERSIONTASK_H
#define CONVERSIONTASK_H

#include "task.h"
#include "processorengine.h"

class RuleEngine;
class ProcessorEngine;

class ConversionTask : public Task
{
public:
    explicit ConversionTask(const QString& filename, const QString& outputFilename);
    virtual ~ConversionTask();
public:
    virtual void run();
    virtual QString taskName() const;
private:
    void setupEngine();
private:
    RuleEngine* m_rules;
    ProcessorEngine* m_engine;
    QString m_outputFilename;
};

#endif // CONVERSIONTASK_H
