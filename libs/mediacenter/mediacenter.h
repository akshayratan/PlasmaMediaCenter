/***********************************************************************************
 *   Copyright 2009-2010 by Alessandro Diaferia <alediaferia@gmail.com>            *
 *                                                                                 *
 *                                                                                 *
 *   This library is free software; you can redistribute it and/or                 *
 *   modify it under the terms of the GNU Lesser General Public                    *
 *   License as published by the Free Software Foundation; either                  *
 *   version 2.1 of the License, or (at your option) any later version.            *
 *                                                                                 *
 *   This library is distributed in the hope that it will be useful,               *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of                *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
 *   Lesser General Public License for more details.                               *
 *                                                                                 *
 *   You should have received a copy of the GNU Lesser General Public              *
 *   License along with this library.  If not, see <http://www.gnu.org/licenses/>. *
 ***********************************************************************************/

#ifndef MEDIACENTER_H
#define MEDIACENTER_H

#include "mediacenter_export.h"

#include <QPair>
#include <QHash>

namespace Phonon {
class MediaSource;
}

namespace MediaCenter {

enum AdditionalMediaRoles {
    MediaUrlRole = Qt::UserRole + 1,
    IsExpandableRole,
    MediaTypeRole,
    DecorationTypeRole,
    HideLabelRole,
    ResourceIdRole,
    MediaThumbnailRole
};

enum MediaType {
    Music,
    Picture,
    Video
};

MEDIACENTER_EXPORT QHash<int, QByteArray> appendAdditionalMediaRoles (const QHash<int, QByteArray> &roles);
} // namespace MediaCenter

#endif // MEDIACENTER_H
