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

#ifndef SVGLISTITEMDELEGATE_H
#define SVGLISTITEMDELEGATE_H

#include <QAbstractItemDelegate>

class QSvgRenderer;

enum SvgRole {
    FILENAME_DATA_ROLE = 20,
    FULLPATH_DATA_ROLE,
    ITEM_STATE
};

enum SvgItemState {
    ITEM_DEFAULT = 40,
    ITEM_CONVERTING,
    ITEM_ERRORS,
    ITEM_WARNINGS,
    ITEM_CONVERTED
};

//static const int FILENAME_DATA_ROLE = 20;
//static const int FULLPATH_DATA_ROLE = 21;

class SvgListItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit SvgListItemDelegate(QObject *parent = 0);
    virtual ~SvgListItemDelegate();

    void setThumbnailSize(int w, int h);
public: // From QAbstractItemDelegate
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
private:
    QSvgRenderer *m_renderer;
    QSize m_size;
};

#endif // SVGLISTITEMDELEGATE_H
