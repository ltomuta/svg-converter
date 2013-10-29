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

#include "cmdlineparser.h"
#include "processorengine.h"
#include "errorcodes.h"
#include "tracer.h"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::cerr;
using std::endl;

CmdLineParser::CmdLineParser(int argc, char *argv[], QObject *parent) :
    QObject(parent), m_argCount(argc), m_argArray(argv)
{
    Tracer trace(Q_FUNC_INFO);
}

CmdLineParser::~CmdLineParser()
{
    Tracer trace(Q_FUNC_INFO);
}

int CmdLineParser::parseParameters(CmdLine& param)
{
    Tracer trace(Q_FUNC_INFO);

    if (m_argCount < 3) {
        cerr << tr("ERROR: Too few parameters").toStdString() << endl << endl;
        printUsage();
        return ERROR_PARAMETERS;
    }

    // Input file must end with .svg
    param.inputFile = QString(m_argArray[1]);
    if (!param.inputFile.endsWith(".svg")) {
        cerr << tr("ERROR: input file not SVG").toStdString() << endl;
        return ERROR_FILENAME;
    }
    // Add .svg if output file doesn't have it
    param.outputFile = QString(m_argArray[2]);
    if (!param.outputFile.endsWith(".svg")) {
        param.outputFile.append(".svg");
    }

    return EXIT_SUCCESS;
}

void CmdLineParser::printUsage()
{
    Tracer trace(Q_FUNC_INFO);
    cout << ProcessorEngine::getVersionString().toStdString() << endl << endl;
    cout << tr("Usage: svg2svgt inputfile outputfile").toStdString() << endl;
}

