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

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QDebug>

#include <cstdlib>
#include <iostream>

#include "cmdlineparser.h"
#include "processorengine.h"
#include "ruleengine.h"
#include "tracer.h"
#include "logger.h"

using namespace std;

void printOutput(Logger& logger);

static const QString RULES_FILE(":/rules.xml");

int main(int argc, char *argv[])
{
    Tracer trace(Q_FUNC_INFO);
    QCoreApplication a(argc, argv);
    Logger logger;

    // Parse command line params to struct
    CmdLine params;
    QScopedPointer<CmdLineParser> parser(new CmdLineParser(argc, argv));
    int retVal = parser->parseParameters(params);
    if (retVal) {
        printOutput(logger);
        return retVal;
    }

    // Create the engines
    QScopedPointer<RuleEngine> rules(new RuleEngine(logger));
    retVal = rules->setRulesFile(RULES_FILE);
    if (retVal) {
        printOutput(logger);
        return retVal;
    }

    QScopedPointer<ProcessorEngine> processor(new ProcessorEngine(*rules.data(), logger));
    
    // Create the processing steps. Add all the steps you want/need
    // TODO parse command line parameters and do the appropriate setup
    // e.g. --print -> EchoProcessorStep


    // Start processing
    retVal = processor->process(params.inputFile, params.outputFile);
    if (retVal) {
        printOutput(logger);
        return retVal;
    }
    printOutput(logger);

    return retVal;
}

void printOutput(Logger& logger) {
    cout << endl;
    if(logger.messages().count() > 0) {
        cout << "*** Messages: " << logger.messages().count() << endl;
        foreach(QString warning, logger.messages())
        {
            cout << " - " << warning.toStdString() << endl;
        }
    }
    cout << endl;

    if(logger.errors().count() > 0) {
        cout << "*** Errors: " << logger.errors().count() << endl;
        foreach(QString warning, logger.errors())
        {
            cout << " - " << warning.toStdString() << endl;
        }
    }
    cout << endl;

    if(logger.warnings().count() > 0) {
        cout << "*** Warnings: " << logger.warnings().count() << endl;
        foreach(QString warning, logger.warnings())
        {
            cout << " - " << warning.toStdString() << endl;
        }
    }

}
