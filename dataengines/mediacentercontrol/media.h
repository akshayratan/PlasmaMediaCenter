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
#ifndef MEDIA_H
#define MEDIA_H

#include <QString>
#include <QUrl>

class Media
{
public:
    Media();
    QString name() const;
    enum State {
        Playing,
        Paused,
        Stopped
    };
    int length();
    bool isRunning();
    State state();
    int position();
    qreal volume();
    bool canPlay();
    void play();
    bool canPause();
    void pause();
    bool canStop();
    void stop();
    bool canGoPrevious();
    void previous();
    bool canGoNext();
    void next();
    bool canSetVolume();
    void setVolume(qreal volume=0);
    bool canSeek();
    void seek(int time=0);
    void setUrl(QUrl);
    QUrl getUrl();
    
protected:
    void setName(const QString& name);
    
private:
    QString m_name;
    Media::State m_state;
    int m_position;
    qreal m_volume;
    int m_length;
    QUrl m_url;
    
};

#endif // MEDIA_H
    