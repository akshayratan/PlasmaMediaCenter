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

ListModel {
    property int defaultIndex: 1
    ListElement {
        display: "Music"
        decoration: "audio-headphones"
        category: "audio"
    }
    ListElement {
        display: "Videos"
        decoration: "video-television"
        category: "video"
    }
    ListElement {
        display: "Pictures"
        decoration: "camera-photo"
        category: "image"
    }
//     ListElement {
//         display: "Others"
//         decoration: "plasma"
//         category: "other"
//     }
    ListElement {
        display: "Settings"
        decoration: "configure"
        category: "settings"
    }
}
