/*
    Copyright (C) 2011  Shantanu Tushar shantanu@kde.org

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef LOCALMUSICMODEL_H
#define LOCALMUSICMODEL_H

#include "../localfilesabstractmodel.h"

#include <QtGui/QImage>

#include <id3v2tag.h>
#include <mpegfile.h>
#include <attachedpictureframe.h>

class LocalMusicModel : public LocalFilesAbstractModel
{
    Q_OBJECT
public:
    explicit LocalMusicModel (QObject* parent);
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QImage imageForFile(const QString& file) const;
    QImage imageForTag(TagLib::ID3v2::Tag *tag) const;
private:
    mutable QHash<int, bool> m_wasImageFound;
};

#endif // LOCALMUSICMODEL_H
