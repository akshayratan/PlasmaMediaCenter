/***************************************************************************
 *   Copyright 2009 by Alessandro Diaferia <alediaferia@gmail.com>         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/
#include "playlistdelegate.h"

// Qt
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QFontMetrics>

// KDE
#include <KIconLoader>
#include <KApplication>
#include <KDebug>

// Plasma
#include <Plasma/Theme>
#include <Plasma/PaintUtils>
#include <Plasma/FrameSvg>

static const int COVER_PIXMAP_SIZE = 64;
static const int ITEM_MARGIN = 2;
static const int REMOVE_BUTTON_SIZE = 16;

PlaylistDelegate::PlaylistDelegate(QObject *parent) : QStyledItemDelegate(parent), m_frameSvg(new Plasma::FrameSvg(this))
{
    m_frameSvg->setImagePath("widgets/viewitem");
    m_frameSvg->setEnabledBorders(Plasma::FrameSvg::AllBorders);
    m_frameSvg->setCacheAllRenderedFrames(true);
    m_frameSvg->setElementPrefix("hover");
}

PlaylistDelegate::~PlaylistDelegate()
{
}

void PlaylistDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    painter->drawRect(option.rect);

        // hover state
    if (option.state & QStyle::State_MouseOver) {
        painter->save();
        m_frameSvg->resizeFrame(option.rect.size());
        m_frameSvg->paintFrame(painter, option.rect.topLeft());
        painter->restore();
    }

    // here we apply the margin to the contents rect
    QRect contentsRect = option.rect;
    contentsRect.setWidth(contentsRect.width() - 2*ITEM_MARGIN);
    contentsRect.setHeight(contentsRect.height() - 2*ITEM_MARGIN);
    contentsRect.translate(ITEM_MARGIN, ITEM_MARGIN);
//    painter->fillRect(contentsRect, Qt::green);

    // cover drawing
    QPixmap cover = index.data(CoverRole).isNull() ? KIconLoader::global()->loadIcon("audio-x-generic", KIconLoader::Desktop, COVER_PIXMAP_SIZE, KIconLoader::DisabledState)
                    : index.data(CoverRole).value<QPixmap>().scaled(COVER_PIXMAP_SIZE, COVER_PIXMAP_SIZE);
    painter->drawPixmap(contentsRect.x(), contentsRect.y(), cover);

    painter->setBrush(Plasma::Theme::defaultTheme()->color(Plasma::Theme::TextColor));

    // the y for the text
    int y = contentsRect.y();

    // song title
    if (option.state & QStyle::State_MouseOver &&
        qGray(Plasma::Theme::defaultTheme()->color(Plasma::Theme::HighlightColor).rgb()) > 192) {
        QPixmap title = Plasma::PaintUtils::shadowText(index.data(TrackNameRole).toString(),
                                                       Plasma::Theme::defaultTheme()->color(Plasma::Theme::HighlightColor),
                                                       Plasma::Theme::defaultTheme()->color(Plasma::Theme::TextColor));
        painter->drawPixmap(contentsRect.x() + COVER_PIXMAP_SIZE + ITEM_MARGIN, y, title);
    } else {
        painter->drawText(contentsRect.x() + COVER_PIXMAP_SIZE + ITEM_MARGIN, y + option.fontMetrics.height(), index.data(TrackNameRole).toString());
    }

//    y += option.fontMetrics.height() + ITEM_MARGIN;
    // artist


}

bool PlaylistDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize PlaylistDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int width = 0;
    int height = 0;

    width += ITEM_MARGIN + COVER_PIXMAP_SIZE + ITEM_MARGIN;
    const QFontMetrics &fm = option.fontMetrics;
    width += fm.width(index.data(TrackNameRole).toString());

    height += ITEM_MARGIN + COVER_PIXMAP_SIZE + ITEM_MARGIN;

    return QSize(width, height);
}
