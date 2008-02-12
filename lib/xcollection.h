/**
 *  This file is a part of Promoe, an XMMS2 Client.
 *
 *  Copyright (C) 2008 Thomas Frauendorfer
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#ifndef __XCOLLECTION_H__
#define __XCOLLECTION_H__

class XClient;

#include <QObject>
class QStringList;
class QString;
class QUrl;

class XCollection : public QObject
{
	Q_OBJECT

	public:
		XCollection (XClient *client);
		QStringList list (QString ns = "Playlists");

		bool remove (QString name, QString ns);

		// idlist specific
		bool setActivePlaylist (QString name);
		QString activePlaylist ();
		bool addIdlist (QString name);
		bool playlistAddUrl (QUrl url, QString plsname = "");

	signals:
		void collectionModified (QString collection, QString ns, int type,
		                         QString newname);

		void activePlaylistChanged (QString newActive, QString oldActive);

	protected slots:
		void on_connect (XClient *);

	private:
		class Private;
		Private* d;

		XClient *m_client;
};

#endif