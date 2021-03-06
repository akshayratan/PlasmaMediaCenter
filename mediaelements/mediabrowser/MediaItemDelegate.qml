/***************************************************************************
 *   Copyright 2012 Sinny Kumari <ksinny@gmail.com>                        *
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

import QtQuick 1.1
import org.kde.qtextracomponents 0.1 as QtExtraComponents
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.mediacentercomponents 0.1 as MediaCenterComponents

Item {
    id: mediaItemDelegateItem
    width: GridView.view.cellWidth
    height: GridView.view.cellHeight
    scale: (GridView.isCurrentItem ? 1.1 : 1)
    clip: !GridView.isCurrentItem
    z: GridView.isCurrentItem ? 1 : 0

    property QtObject backend
    signal popupMenuRequested(int index, string mediaUrl, string mediaType, string display)
    signal playRequested(int index, string url, string currentMediaType)

    MediaItem {
        anchors.fill: parent;
        onClicked: {
            if (isExpandable) {
                backend.expand(index, mediaUrl, mediaType);
            } else {
                mediaItemDelegateItem.playRequested(index, mediaUrl, mediaType)
            }
        }
        onPressAndHold: {
            if( mediaType == "audio" || mediaType == "video") {
                popupMenuRequested(index, mediaUrl, mediaType, display);
            }
        }
    }
    Behavior on scale {
        NumberAnimation {
            duration: 100
        }
    }

    Keys.onReturnPressed: {
        if (isExpandable) {
            backend.expand(index);
        } else {
            mediaItemDelegateItem.playRequested(index, mediaUrl, mediaType)
        }
    }
}
