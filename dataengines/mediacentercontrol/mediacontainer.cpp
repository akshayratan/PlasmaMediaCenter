/***************************************************************************
 *   Copyright 2011 by Sinny Kumari <ksinny@gmail.com>                     *
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
#include "mediacontainer.h"
#include "mediaservice.h"

MediaContainer::MediaContainer(QObject *parent)
    : Plasma::DataContainer(parent)
{
    updateData();
}

void MediaContainer::updateData()
{
    Media* m_media=new Media;
    switch(m_media->state()) {
        case Media::Playing:
            setData("State", "playing");
            break;
        case Media::Paused:
            setData("State", "paused");
            break;
        case Media::Stopped:
            setData("State", "stopped");
            break;
    }
    setData("Progress",m_media->position()); 
    setData("MediaType", "Audio");
    setData("Url","/home/Music/sintel.mp3");
}

#include "mediacontainer.moc"