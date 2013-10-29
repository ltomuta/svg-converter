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

#include "svglistitemdelegate.h"
#include "tracer.h"

#include <QtGui/QPainter>
#include <QtGui/QPixmapCache>
#include <QtSvg/QSvgRenderer>

SvgListItemDelegate::SvgListItemDelegate(QObject *parent) :
    QAbstractItemDelegate(parent)
{
    m_renderer = new QSvgRenderer(this);

}

SvgListItemDelegate::~SvgListItemDelegate()
{
    delete m_renderer;
}

void SvgListItemDelegate::setThumbnailSize(int w, int h)
{
    m_size = QSize(w,h);
}

void SvgListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    // Save painter state so we can restore after we're done
    painter->save();

    if (option.state & QStyle::State_Selected) {
        // If selected, draw highligh with gradient
        QLinearGradient gradient(option.rect.topLeft(), option.rect.bottomLeft());
        gradient.setColorAt(0, option.palette.highlight().color().darker());
        gradient.setColorAt(1, option.palette.highlight().color());

        // Fill the rounded rectangle
        QPainterPath roundedRect;
        roundedRect.addRoundedRect(option.rect, 5.0, 5.0);
        painter->setClipPath(roundedRect);

        painter->fillPath(roundedRect, gradient);
    }

    // Add some padding to the list item rect
    const int PADDING = 4;
    QRect paddedRect = option.rect.adjusted(PADDING, PADDING, -PADDING, -PADDING);

    // Get the data from model
    QVariant variant = index.model()->data(index, FULLPATH_DATA_ROLE);
    QString name = variant.toString();

    // If icon for file is not yet in cache, we have to render it and store it
    QPixmap icon(m_size);
    if (!QPixmapCache::find(name, &icon)) {
        // No icon cached yet
        if (m_renderer->load(name)) {
            QPixmap newIcon(m_size);
            QPainter iconPainter(&newIcon);

            iconPainter.fillRect(0,0,m_size.width(), m_size.height(), Qt::white);
            iconPainter.save();
            m_renderer->render(&iconPainter);
            QPixmapCache::insert(name, newIcon);
            iconPainter.restore();
            icon = newIcon;
        }
    }
    painter->drawPixmap(paddedRect, icon);

    QVariant variant2 = index.model()->data(index, ITEM_STATE);
    int state = variant2.toInt();
    QString overlayIconName;
    switch (state)
    {
    case ITEM_CONVERTING:
        overlayIconName = ":/gfx/converting_overlay.png";
        break;
    case ITEM_ERRORS:
        overlayIconName = ":/gfx/errors_overlay.png";
        break;
    case ITEM_WARNINGS:
        overlayIconName = ":/gfx/warnings_overlay.png";
        break;
    case ITEM_CONVERTED:
        overlayIconName = ":/gfx/success_overlay.png";
        break;
    default:
        break;
    }
    if (!overlayIconName.isEmpty()) {
        QPixmap overlay(overlayIconName);

        static const int OVERLAY_ICON_SIZE = 24;
        int ovx = paddedRect.x() + paddedRect.width() - OVERLAY_ICON_SIZE;
        int ovy = paddedRect.y() + paddedRect.height() - OVERLAY_ICON_SIZE;
        painter->drawPixmap(ovx, ovy, OVERLAY_ICON_SIZE, OVERLAY_ICON_SIZE, overlay);
    }
    // Restore painter to original state
    painter->restore();
}

QSize SvgListItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return m_size;
}

