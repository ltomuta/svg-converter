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

#include <cstdio>
#include <iostream>
#include "tracer.h"

using namespace std;

Tracer::Tracer(const char* method) 
{
#ifdef TRACING_ON
    m_method = method;
    cout << "[" PREFIX << "][TRACE][IN ] " << m_method << endl;
#endif
}
Tracer::~Tracer(){
#ifdef TRACING_ON
     cout << "[" << PREFIX << "][TRACE][OUT] " << m_method << endl;
#endif
}









