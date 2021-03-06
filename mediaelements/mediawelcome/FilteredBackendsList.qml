/***************************************************************************
 *   Copyright 2012 by Sinny Kumari <ksinny@gmail.com>                     *
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
import org.kde.plasma.mediacentercomponents 0.1 as MediaCenterComponents
import org.kde.plasma.components 0.1 as PlasmaComponents

ListView {
    id: listView
    spacing: 20

    property alias backendsModel: filteredModel.sourceBackendsModel
    property alias categoryFilter: filteredModel.backendCategory
    property string currentBackendDescription: currentItem ? currentItem.currentBackendDescription : ""

    //FIXME: this is really bad looking :/
    highlight: PlasmaComponents.Highlight { }
    highlightFollowsCurrentItem: true

    Keys.onReturnPressed: { currentItem.launch() }
    Keys.onEnterPressed: { currentItem.launch() }

    model: MediaCenterComponents.FilteredBackendsModel {
        id: filteredModel
    }

    delegate: BackendsListDelegate {
        height: 64 + anchors.margins
        width: listView.width
        anchors.margins: 6
    }

    onCategoryFilterChanged: currentIndex = 0
}
