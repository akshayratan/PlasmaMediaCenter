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
#include "media.h"
#include "kdebug.h"

Media::Media()
{
    m_state = Paused;
    m_length = 339767;
    m_volume = 0.5;
    m_position = 0;
    m_url = "file:///home/sinny/raj.mp3";
    m_dirty = false;
}

QString Media::name() const
{
    return m_name;
}

Media::State Media::state()
{
    return m_state;
}
bool Media::status()
{
    return m_dirty;
}

int Media::length()
{
    return m_length;
}

int Media::position()
{
    return m_position;
}

qreal Media::volume()
{
    return m_volume;
}

bool Media::canPlay()
{
    return (m_state==Paused||m_state==Stopped);
}

void Media::play()
{
    m_state = Playing;
    emit mediaDataUpdated();
    
    kDebug() << "play";
}

bool Media::canPause()
{
    return (m_state==Playing);
}

void Media::pause()
{
        m_state = Paused;
        emit mediaDataUpdated();
        kDebug() << "pause";
}

bool Media::canStop()
{
    return (m_state==Playing||m_state==Paused);
}

void Media::stop()
{
    m_state = Stopped;
    m_position = 0;
    emit mediaDataUpdated();
    kDebug() << "stop";
}

bool Media::canGoPrevious()
{
    return true;
}

void Media::previous()
{
    kDebug() << "previous";
}

bool Media::canGoNext()
{
    return true;
}

void Media::next()
{
    kDebug() << "next";
}

bool Media::canSetVolume()
{
    return true;
}

void Media::setVolume(qreal volume)
{
    m_volume = volume;
    kDebug() << "volumeSet";
}

bool Media::canSeek()
{
    return (m_state==Playing||m_state==Paused);
}

void Media::seek(int time)
{
    m_position = time;
    m_dirty = true;
    emit mediaDataUpdated();
    kDebug() << "seek to " << m_position;
}

bool Media::canMediaProgress()
{
    return (m_state==Playing);
}

void Media::mediaProgress(int time)
{
    m_position = time;
    m_dirty = false;
    emit mediaDataUpdated();
    kDebug() << "progress to " << m_position;
}
void Media::setName(const QString& name)
{
    m_name = name;
}

void Media::setUrl(QUrl url)
{
    m_url = url;
    emit mediaDataUpdated();
}

QUrl Media::getUrl()
{
    return m_url;
}
#include "media.moc"