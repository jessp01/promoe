/**
 *  This file is a part of Promoe, an XMMS2 Client.
 *
 *  Copyright (C) 2005-2016 XMMS2 Team
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

#ifndef __PLAYLISTVIEW_H__
#define __PLAYLISTVIEW_H__

//include "Playlist.h"
#include <xmmsclient/xmmsclient++.h>
#include "entryinfo.h"
class Skin;
class PlaylistModel;

#include <QObject>
#include <QAbstractItemDelegate>
#include <QListView>
#include <QPointer>
class QWidget;
class QModelIndex;

class PlaylistDelegate : public QAbstractItemDelegate {
	Q_OBJECT

	public:
		PlaylistDelegate (QObject *parent = NULL);
		~PlaylistDelegate () { }

		void paint( QPainter * painter, const QStyleOptionViewItem & option,
		            const QModelIndex & index ) const;

		QSize sizeHint ( const QStyleOptionViewItem &option,
		                 const QModelIndex &index ) const;
};


class PlaylistView : public QListView {
	Q_OBJECT

	public:
		PlaylistView (QWidget *parent);
		~PlaylistView () {}

		void setModel (QAbstractItemModel *model)
			{qWarning ("Trying to set wrong model in PlaylistView"); return;};
		void setModel (PlaylistModel *model);

	signals:
		void selectionPlaytimeChanged (uint32_t playtime);

	public slots:
		void contextMenuEvent (QContextMenuEvent *e);

		void handleStatus (const Xmms::Playback::Status st);
		void invertSelection (void);
		void cropSelected (void);
		void removeSelected (void);
		void showEntryInfo (void);
		void configureTooltips (void);
		void settingsChanged (void);
		void setPixmaps (Skin *skin);
		void currentPosChanged (QModelIndex);

	protected:
		void mouseDoubleClickEvent (QMouseEvent *event);

	protected slots:
		void selectionChanged (const QItemSelection &, const QItemSelection &);

	private:
		Xmms::Playback::Status m_status;
		QFont *m_font;
		QFontMetrics *m_fontmetrics;
		QColor m_color_active;
		QColor m_color_selected;
		QColor m_color_normal;
		QColor m_color_normal_bg;
		QPointer<EntryInfo> m_entry_info;
};


#endif
