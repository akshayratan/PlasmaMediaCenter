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
#include "playlistwidget.h"

// Qt
#include <QGraphicsLinearLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVariant>
#include <QTreeView>

// QtDBus
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>

// KDE
#include <KDebug>
#include <KConfigGroup>
#include <KComboBox>

// Plasma
#include <Plasma/TreeView>
#include <Plasma/DataEngine>
#include <Plasma/DataEngineManager>
#include <Plasma/Service>
#include <Plasma/ServiceJob>
#include <Plasma/Delegate>
#include <Plasma/ComboBox>

// Taglib
#include <fileref.h>
#include <tag.h>

PlaylistWidget::PlaylistWidget(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_treeView(new Plasma::TreeView(this)),
      m_playlistEngine(0),
      m_coverEngine(0),
      m_model(new QStandardItemModel(this))
{
    // here we try to load the playlist engine
    m_playlistEngine = Plasma::DataEngineManager::self()->engine("playlist");
    if (!m_playlistEngine->isValid()) {
        m_playlistEngine = Plasma::DataEngineManager::self()->loadEngine("playlist");
        if (!m_playlistEngine->isValid()) {
            kWarning() << "unable to load playlist engine";
        }
    }

    // TODO: avoid this code duplication
    m_playlistEngine = Plasma::DataEngineManager::self()->engine("coverfetcher");
    if (!m_playlistEngine->isValid()) {
        m_playlistEngine = Plasma::DataEngineManager::self()->loadEngine("coverfetcher");
        if (!m_playlistEngine->isValid()) {
            kWarning() << "unable to load coverfetcher engine";
        }
    }

    connect (m_playlistEngine, SIGNAL(sourceAdded(const QString &)), this, SLOT(slotSourceAdded(const QString &)));

    m_treeView->setModel(m_model);
    Plasma::Delegate *delegate = new Plasma::Delegate(this);
    delegate->setRoleMapping(Plasma::Delegate::SubTitleRole, Plasma::Delegate::SubTitleRole);
    m_treeView->nativeWidget()->setItemDelegate(delegate);
    m_treeView->nativeWidget()->setHeaderHidden(true);
    m_treeView->nativeWidget()->setRootIsDecorated(false);

    m_interface = new QDBusInterface("org.kde.PlaylistEngine", "/PlaylistEngine", QString(), QDBusConnection::sessionBus(), this);

    m_comboBox = new Plasma::ComboBox(this);
    connect (m_comboBox->nativeWidget(), SIGNAL(currentIndexChanged(const QString &)), this, SLOT(showPlaylist(const QString &)));
    foreach (const QString &source, m_playlistEngine->sources()) {
        if (source == "currentPlaylist") {
            continue;
        }
        m_comboBox->addItem(source);
    }

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
    layout->addItem(m_comboBox);
    layout->addItem(m_treeView);
    setLayout(layout);
}

PlaylistWidget::~PlaylistWidget()
{
}

void PlaylistWidget::showPlaylist(const QString &playlistName)
{
    m_model->clear();
    QStringList files;

    foreach (const QVariant &tracks, m_playlistEngine->query(playlistName)) {
        files << tracks.toStringList();
        kDebug() << tracks;
    }

    foreach (const QString &track, files) {
        TagLib::FileRef ref(track.toLatin1());
        QStandardItem *item = new QStandardItem(ref.tag()->title().toCString(true));
        item->setData(ref.tag()->artist().toCString(true), Plasma::Delegate::SubTitleRole);
        QString coverSource = ref.tag()->artist().toCString(true);
        coverSource.append("|");
        coverSource.append(ref.tag()->album().toCString(true));
        item->setData(coverSource, CoverSourceRole);
        m_model->appendRow(item);
    }

    Plasma::Service *playlistService = m_playlistEngine->serviceForSource(playlistName);
    if (!playlistService) {
        kDebug() << "invalid service";
        return;
    }

    KConfigGroup op = playlistService->operationDescription("setCurrent");
    Plasma::ServiceJob *job = playlistService->startOperationCall(op); 
}

void PlaylistWidget::slotSourceAdded(const QString &source)
{
    if (source == "currentPlaylist") {
        return;
    }

    m_comboBox->addItem(source);
}