/***************************************************************************
 *   Copyright 2012 Sinny Kumari <ksinny@gmail.com>                        *
 *   Copyright 2012 Shantanu Tushar <shantanu@kde.org>                     *
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
import org.kde.plasma.components 0.1 as PlasmaComponents

Item{
    id: listViewItem

    Row {
        anchors.fill: parent
        Rectangle {
            width: parent.width - removeFromPlaylistButton.width; height: parent.height
            color: listViewItem.ListView.isCurrentItem ? "#002378" : theme.backgroundColor
            opacity: 0.8;
            Text {
                anchors {
                    fill: parent; verticalCenter: parent.verticalCenter;
                    margins: 5
                }
                text: display
                color: (index == playlistModel.currentIndex) ? "red" : theme.textColor
                elide: Text.ElideRight
                font.pixelSize: 18
                style: Text.Sunken
            }

            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    listViewItem.ListView.view.model.currentIndex = index
                    playlistItem.playRequested(mediaUrl)
                }
            }
        }

        PlasmaComponents.ToolButton {
            id: removeFromPlaylistButton
            width: height
            height: parent.height

            iconSource: "list-remove"
            onClicked: {
                playlistModel.removeFromPlaylist (index);
            }
        }
    }
}
