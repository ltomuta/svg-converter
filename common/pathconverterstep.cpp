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

#include "pathconverterstep.h"
#include "tracer.h"
#include "nodefinder.h"

#include <qmath.h>
const qreal Q_PI = 3.1415926535;

PathConverterStep::PathConverterStep(Logger& logger, QObject *parent) :
    QObject(parent),
    ProcessorStep(logger)
{ 
    Tracer trace(Q_FUNC_INFO);
}

PathConverterStep::~PathConverterStep()
{
    Tracer trace(Q_FUNC_INFO);
}

QDomDocument PathConverterStep::process(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);
    QDomElement svg = svgDoc.elementsByTagName("svg").at(0).toElement(); // The 1st SVG element
    convertEllipticalArcs(svgDoc);
    return svgDoc;
}

QString PathConverterStep::description()
{
    Tracer trace(Q_FUNC_INFO);
    return tr("Path converter");
}

// Parser for path d-attribute for parts with elliptical arcs.
class PathParser
{
public:
    enum ArcType { ArcAbsolute = 0, ArcRelative };

    // Check parser status
    bool success() const { Tracer trace(Q_FUNC_INFO); return m_ok; }

    // Retrieve the generated path
    QString path() const { Tracer trace(Q_FUNC_INFO); return m_path; }

    // Elliptical arg: a/A
    // 	(rx ry x-axis-rotation large-arc-flag sweep-flag x y)+

    //         rx         ry    xar   lafl sfl      x      y      rx      ry      xar lafl sfl   x       y
    // 	82.429848,11.747722 0     1    1     -164.85969,0 82.429848,11.747722 0   1      1 164.85969,0

    // Parse moveTo command to get the initial position for absolute arcs.
    void parseMoveTo(QString data) {
        Tracer trace(Q_FUNC_INFO);
        m_string = data;
 	m_currentX = pullDouble();
 	m_currentY = pullDouble();
    }

    // Parse elliptical arc parameters from the given string.
    int parseEllipticalArc(QString data, ArcType type) {
        Tracer trace(Q_FUNC_INFO);
        m_arcType = type;
	m_string = data;
	int length = m_string.length();
	m_ok = true;
	m_path.clear();

	// There may be more than one elliptical arc incoming.
	forever {
	    // Check for parse error
 	    if(!m_ok) break;

	    // Skip to next relevant char
	    skip();

	    // End condition check
	    if(m_string.length() == 0 ||
                    (!m_string[0].isNumber() &&
                     m_string[0] != '-' &&
                     m_string[0] != 'a' &&
                     m_string[0] != 'A')) {
		break;
	    }
	    
	    // Pull parameters
	    qreal rx = pullDouble();
	    qreal ry = pullDouble();
	    int xar = pullInt();
	    int lafl = pullInt();
	    int sfl = pullInt();
	    qreal x = pullDouble(); // end position x
	    qreal y = pullDouble(); // end position y

	    if(m_arcType == ArcRelative) {
		// Relative arcs start from 0,0.
		m_currentX = 0;
		m_currentY = 0;
	    } 
	    pathArc(rx, ry, xar, lafl, sfl, x, y, m_currentX, m_currentY);
	}
	// Returns amount of chars consumed.
	return length - m_string.length();
    }


private:

    // Skip to next relevant character.
    void skip() {
        Tracer trace(Q_FUNC_INFO);
        while(m_string[0].isSpace() ||
	      m_string[0] == ',' ||
	      m_string[0] == 'A' ||
	      m_string[0] == 'a') {
	    m_string.remove(0,1);
	}
    }

    // Pull the next token.
    QString pull() {
        Tracer trace(Q_FUNC_INFO);
        skip();
	QString s;
	// Both space and comma seem to be acceptable delimiters.
	while(m_string.length() > 0 && 
	      m_string[0] != ' ' &&  m_string[0] != ',') {
	    QChar c = m_string[0];
	    m_string.remove(0,1);

	    // Acceptable characters
	    if(c.isNumber() || c == '.' || c == '-') {
		s.append(c);
	    } else {
		m_ok = false;
		break;
	    }
	}
	return s;
    }

    // Pull a double
    qreal pullDouble() {
        Tracer trace(Q_FUNC_INFO);
        QString s = pull();
	return s.toDouble(&m_ok);
    }

    // Pull an integer
    int pullInt() {
        Tracer trace(Q_FUNC_INFO);
        QString s = pull();
	return s.toInt(&m_ok);
    }


    void pathArcSegment(qreal xc, qreal yc,
			qreal th0, qreal th1,
			qreal rx, qreal ry, qreal xAxisRotation)
    {
        Tracer trace(Q_FUNC_INFO);
        qreal sinTh, cosTh;
	qreal a00, a01, a10, a11;
	qreal x1, y1, x2, y2, x3, y3;
	qreal t;
	qreal thHalf;

	sinTh = qSin(xAxisRotation * (Q_PI / 180.0));
	cosTh = qCos(xAxisRotation * (Q_PI / 180.0));

	a00 =  cosTh * rx;
	a01 = -sinTh * ry;
	a10 =  sinTh * rx;
	a11 =  cosTh * ry;

	thHalf = 0.5 * (th1 - th0);
	t = (8.0 / 3.0) * qSin(thHalf * 0.5) * qSin(thHalf * 0.5) / qSin(thHalf);
	x1 = xc + qCos(th0) - t * qSin(th0);
	y1 = yc + qSin(th0) + t * qCos(th0);
	x3 = xc + qCos(th1);
	y3 = yc + qSin(th1);
	x2 = x3 + t * qSin(th1);
	y2 = y3 - t * qCos(th1);

	qreal c1X = a00 * x1 + a01 * y1;
	qreal c1Y = a10 * x1 + a11 * y1;
	qreal c2X = a00 * x2 + a01 * y2;
	qreal c2Y = a10 * x2 + a11 * y2;
	qreal endX = a00 * x3 + a01 * y3;
	qreal endY = a10 * x3 + a11 * y3;

	// Generate bezier curve path command
	if(m_arcType == ArcRelative) {
	    // Relative arc segments need to be translated according
	    // to the previous segment.
	    m_path.append(" c ");
	    m_path.append(QString::number(c1X - m_currentX,  'f', 4) + " " + 
			  QString::number(c1Y - m_currentY,  'f', 4) + " " +
			  QString::number(c2X - m_currentX,  'f', 4) + " " + 
			  QString::number(c2Y - m_currentY,  'f', 4) + " " +
			  QString::number(endX - m_currentX, 'f', 4) + " " +
			  QString::number(endY - m_currentY, 'f', 4));
	} else {
	    m_path.append(" C ");
	    m_path.append(QString::number(c1X,  'f', 4) + " " + 
			  QString::number(c1Y,  'f', 4) + " " +
			  QString::number(c2X,  'f', 4) + " " + 
			  QString::number(c2Y,  'f', 4) + " " +
			  QString::number(endX, 'f', 4) + " " +
			  QString::number(endY, 'f', 4));
	}
	// Store last segment end position for later.
	m_currentX = endX;
	m_currentY = endY;
    }


    // the arc handling code underneath is from XSVG (BSD license)
    /*
     * Copyright  2002 USC/Information Sciences Institute
     *
     * Permission to use, copy, modify, distribute, and sell this software
     * and its documentation for any purpose is hereby granted without
     * fee, provided that the above copyright notice appear in all copies
     * and that both that copyright notice and this permission notice
     * appear in supporting documentation, and that the name of
     * Information Sciences Institute not be used in advertising or
     * publicity pertaining to distribution of the software without
     * specific, written prior permission.  Information Sciences Institute
     * makes no representations about the suitability of this software for
     * any purpose.  It is provided "as is" without express or implied
     * warranty.
     *
     * INFORMATION SCIENCES INSTITUTE DISCLAIMS ALL WARRANTIES WITH REGARD
     * TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF
     * MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL INFORMATION SCIENCES
     * INSTITUTE BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
     * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
     * OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
     * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
     * PERFORMANCE OF THIS SOFTWARE.
     *
     */
    void pathArc(qreal rx,
		 qreal ry,
		 qreal x_axis_rotation,
		 int large_arc_flag,
		 int sweep_flag,
		 qreal x,
		 qreal y,
		 qreal curx, qreal cury)
    {
        Tracer trace(Q_FUNC_INFO);
        qreal sin_th, cos_th;
	qreal a00, a01, a10, a11;
	qreal x0, y0, x1, y1, xc, yc;
	qreal d, sfactor, sfactor_sq;
	qreal th0, th1, th_arc;
	int i, n_segs;
	qreal dx, dy, dx1, dy1, Pr1, Pr2, Px, Py, check;

	rx = qAbs(rx);
	ry = qAbs(ry);

	sin_th = qSin(x_axis_rotation * (Q_PI / 180.0));
	cos_th = qCos(x_axis_rotation * (Q_PI / 180.0));

	dx = (curx - x) / 2.0;
	dy = (cury - y) / 2.0;
	dx1 =  cos_th * dx + sin_th * dy;
	dy1 = -sin_th * dx + cos_th * dy;
	Pr1 = rx * rx;
	Pr2 = ry * ry;
	Px = dx1 * dx1;
	Py = dy1 * dy1;
	/* Spec : check if radii are large enough */
	check = Px / Pr1 + Py / Pr2;
	if (check > 1) {
	    rx = rx * qSqrt(check);
	    ry = ry * qSqrt(check);
	}

	a00 =  cos_th / rx;
	a01 =  sin_th / rx;
	a10 = -sin_th / ry;
	a11 =  cos_th / ry;
	x0 = a00 * curx + a01 * cury;
	y0 = a10 * curx + a11 * cury;
	x1 = a00 * x + a01 * y;
	y1 = a10 * x + a11 * y;
	/* (x0, y0) is current point in transformed coordinate space.
    (x1, y1) is new point in transformed coordinate space.

    The arc fits a unit-radius circle in this space.
 */
	d = (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
	sfactor_sq = 1.0 / d - 0.25;
	if (sfactor_sq < 0) sfactor_sq = 0;
	sfactor = qSqrt(sfactor_sq);
	if (sweep_flag == large_arc_flag) sfactor = -sfactor;
	xc = 0.5 * (x0 + x1) - sfactor * (y1 - y0);
	yc = 0.5 * (y0 + y1) + sfactor * (x1 - x0);
	/* (xc, yc) is center of the circle. */

	th0 = qAtan2(y0 - yc, x0 - xc);
	th1 = qAtan2(y1 - yc, x1 - xc);

	th_arc = th1 - th0;
	if (th_arc < 0 && sweep_flag)
	    th_arc += 2 * Q_PI;
	else if (th_arc > 0 && !sweep_flag)
	    th_arc -= 2 * Q_PI;

	n_segs = qCeil(qAbs(th_arc / (Q_PI * 0.5 + 0.001)));

	for (i = 0; i < n_segs; i++) {
	    pathArcSegment(xc, yc,
			   th0 + i * th_arc / n_segs,
			   th0 + (i + 1) * th_arc / n_segs,
			   rx, ry, x_axis_rotation);
	}
    }
private:
    bool m_ok;
    QString m_string;
    QString m_path;
    ArcType m_arcType;
    qreal m_currentX, m_currentY;

};

// Filter to find <path> elements.
static struct PathFilter : public NodeFilter {
    bool operator()(QDomNode node) {
	if(node.toElement().tagName() == "path") {
	    return true;
	}
	return false;
    }
} pathFilter;


void PathConverterStep::convertEllipticalArcs(QDomDocument svgDoc)
{
    Tracer trace(Q_FUNC_INFO);
    QList<QDomNode> pathNodes = NodeFinder::find(svgDoc, &pathFilter);
    foreach(QDomNode node, pathNodes) {
	QDomElement elem = node.toElement();
	if(elem.isNull()) {
	    continue;
	}
	// Get the path d-section, describing the path commands.
	QDomAttr attr = elem.attributeNode("d");
	QString d =  attr.value();
	QString oldPath = d;

	// Find a or A, which denotes the start of an elliptical arc command.
	int arcIndex = d.indexOf("a", 0, Qt::CaseInsensitive);
	if(arcIndex == -1) {
	    // Not found in this path node.
	    continue;
	}

	bool relativeEllipticalArc = d.contains("a");

	PathParser parser;

	// First find the starting point by looking at the moveTo command.
	// Find 'm' or 'M'
	int mIndex = d.indexOf("M", 0, Qt::CaseInsensitive);
	QString dataToParse = d.mid(mIndex + 1, -1);
	parser.parseMoveTo(dataToParse);
        
	// Then parse and convert the arcs.
	dataToParse = d.mid(arcIndex + 1, -1);
	int consumedBytes = 
                parser.parseEllipticalArc(dataToParse,
                                          relativeEllipticalArc ? PathParser::ArcRelative : PathParser::ArcAbsolute);
	
	if(!parser.success()) {
	    m_logger.error(tr("Unable to parse elliptical arc %1").arg(dataToParse));
	    continue;
	}

	// Remove the elliptical arc part.
	d.remove(arcIndex, consumedBytes);

	// Replace with new part.
	d.insert(arcIndex, parser.path());
	attr.setValue(d);
    }
}
