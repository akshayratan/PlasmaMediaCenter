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
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "mediacenter_export.h"

#include <Plasma/Applet>

#include <mediacenter/mediacenter.h>

namespace MediaCenter {

/**
 * @class Playlist playlist.h
 * This is the base class for the playlist applet in a media containment.
 * Use this as base class for implementing basic playlist handling.
 * Remember to use Playlist dataengine and eventually the cover fetcher dataengines
 * in order to retrieve useful data for the playlist items.
 */

class MEDIACENTER_EXPORT Playlist : public Plasma::Applet
{
    Q_OBJECT
public:
    Playlist(QObject *parent, const QVariantList &args);
    virtual ~Playlist();

    /**
     * @return the number of items in the current playlist.
     */
    virtual int length() = 0;

    //TODO Find a better way to handle playlists and types
    /**
    * This function forces the plaliyts to show only a certain mediatype
    */
    virtual void setPlaylistMediaType(const MediaCenter::MediaType &) = 0;

    /**
     * @return the list of strings identifying the medias
     * in the current playlist.
     */
    virtual QList<MediaCenter::Media> medias(MediaCenter::MediaType) = 0;

public Q_SLOTS:
    /**
     * Use this slot in order to append the media.
     * @note: the default implementation does nothing.
     */
    virtual void appendMedia(const QList<MediaCenter::Media> &medias, const QString &playlist = QString());

Q_SIGNALS:
    /**
     * Emit this signal whenever a new media gets added to the current playlist.
     * Use the index to specify at which position the item has been dropped to.
     */
    void mediaAdded(int index, const QString &mediaString);

    /**
     * Use this convenience signal if the media has just been dropped at the end of
     * the playlist.
     */
    void mediasAppended(const QList<MediaCenter::Media> &medias);

    /**
     * This signal is emitted whenever the current playlist changes
     * in multiple playlists mode.
     *
     * @param medias is the list of strings identifying the medias in the playlist.
     * @param playlistName is the name for the new playlist.
     */
    void playlistChanged(const QStringList &medias, const QString &playlistName);

    /**
     * This signal should be emitted whenever a new media has to be played.
     * For example emit this signal when the user clicks on a specific media
     * in the playlist.
     */
    void mediaActivated(const MediaCenter::Media &);

};

}

#endif // PLAYLIST_H