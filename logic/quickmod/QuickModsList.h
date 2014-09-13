/* Copyright 2013 MultiMC Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <QAbstractListModel>

#include "logic/quickmod/QuickModVersion.h"
#include "logic/quickmod/QuickModMetadata.h"
#include "logic/BaseInstance.h"

class QUrl;

class QuickModDatabase;
class Mod;
class SettingsObject;
class OneSixInstance;

// TODO: make the database a global instead.
//       Make this class a temporary view on top of database, only constructed when needed.
class QuickModsList : public QAbstractListModel
{
	Q_OBJECT
public:
	enum Flag
	{
		NoFlags = 0x0,
		DontCleanup = 0x1
	};
	Q_DECLARE_FLAGS(Flags, Flag)

	explicit QuickModsList(const Flags flags = NoFlags, QObject *parent = 0);
	~QuickModsList();

	enum Roles
	{
		NameRole = Qt::UserRole,
		UidRole,
		RepoRole,
		DescriptionRole,
		WebsiteRole,
		IconRole,
		LogoRole,
		UpdateRole,
		ReferencesRole,
		DependentUrlsRole,
		ModIdRole,
		CategoriesRole,
		MCVersionsRole,
		TagsRole,
		QuickModRole
	};
	QHash<int, QByteArray> roleNames() const;

	int rowCount(const QModelIndex &) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;

	QVariant data(const QModelIndex &index, int role) const;

	bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
						 const QModelIndex &parent) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
					  const QModelIndex &parent);
	Qt::DropActions supportedDropActions() const;
	Qt::DropActions supportedDragActions() const;

	// TODO: move to database.
	QList<QuickModMetadataPtr> allModMetadata(const QuickModRef &uid) const;
	QuickModMetadataPtr someModMetadata(const QuickModRef &uid) const;
	QuickModMetadataPtr quickmodMetadata(const QString &internalUid) const;
	QuickModVersionPtr version(const QuickModVersionRef &version) const;
	QuickModVersionRef latestVersionForMinecraft(const QuickModRef &modUid, const QString &mcVersion) const;
	QStringList minecraftVersions(const QuickModRef &uid) const;
	QList<QuickModVersionRef> versions(const QuickModRef &uid, const QString &mcVersion) const;
	QList<QuickModRef> updatedModsForInstance(std::shared_ptr<OneSixInstance> instance) const;
	bool haveUid(const QuickModRef &uid, const QString &repo = QString()) const;

	// TODO: remove this
	inline QuickModDatabase *database() const
	{
		return m_storage;
	}

	// TODO: move to database (all of these)
public slots:
	void registerMod(const QString &fileName);
	void registerMod(const QUrl &url);
	void updateFiles();

public:
	// TODO: move to database (all of these)
	// called from QuickModDownloadAction
	void addMod(QuickModMetadataPtr mod);
	void addVersion(QuickModVersionPtr version);

	void modIconUpdated();
	void modLogoUpdated();

	// FIXME: NUKE this abomination. Whatever it is, it has to die.
	void cleanup();

signals:
	void error(const QString &message);

private:
	/// Gets the index of the given mod in the list.
	int getQMIndex(QuickModMetadataPtr mod) const;
	QuickModMetadataPtr getQMPtr(QuickModMetadata *mod) const;

	// FIXME: only keep the real data in database. REMOVE THIS.
	QHash<QuickModRef, QList<QuickModMetadataPtr>> m_mods;
	// list that stays ordered for the model, can stay.
	QList<QuickModRef> m_uids; 
	// FIXME: only keep the real data in database. REMOVE THIS.
	QHash<QString, QHash<QString, QuickModVersionPtr>> m_versions;

	QuickModDatabase *m_storage;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QuickModsList::Flags)
