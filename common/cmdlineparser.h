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

#ifndef CMDLINEPARSER_H
#define CMDLINEPARSER_H

#include <QtCore/QObject>

struct CmdLine {
    QString inputFile;
    QString outputFile;
};

class CmdLineParser : public QObject
{
    Q_OBJECT
public:
    explicit CmdLineParser(int argc, char *argv[], QObject *parent = 0);
    virtual ~CmdLineParser();

    int parseParameters(CmdLine& param);
private:
    void printUsage();
private:
    int m_argCount;
    char** m_argArray;
};

#endif // CMDLINEPARSER_H
