/**
 *  This file is a part of Prome, an XMMS2 Client.
 *
 *  Copyright (C) 2005-2007 XMMS2 Team
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

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "XMMSHandler.h"

#include <QMainWindow>
#include <QSettings>

class QWidget;

class MainDisplay;
class ShadedDisplay;
class PlaylistWindow;
class EqualizerWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		MainWindow (QWidget *parent);
		~MainWindow (void);

		MainDisplay *getMD () { return m_display; }
		ShadedDisplay *getSD () { return m_shaded; }
		PlaylistWindow *getPL () { return m_playlistwin; }

		void setEQ (EqualizerWindow *e) { m_equalizer = e; }

		void raisePL (void);
		void moveEvent (QMoveEvent *event);

		void toggleEQ (bool UpdateButton);
		bool isTimemodeReverse(void) { QSettings s; return s.value("MainWindow/timemodereverse").toBool(); }
		void setTimemodeReverse(bool b) { QSettings s; return s.setValue("MainWindow/timemodereverse",b); }

	public slots:
		void switchDisplay ();

	private:
		bool isShaded (void) { QSettings s; return s.value("MainWindow/shaded").toBool(); }
		void setShaded (bool b) { QSettings s; return s.setValue("MainWindow/shaded", b); }
		MainDisplay *m_display;
		ShadedDisplay *m_shaded;
		EqualizerWindow *m_equalizer;
		PlaylistWindow *m_playlistwin;
};


#endif
