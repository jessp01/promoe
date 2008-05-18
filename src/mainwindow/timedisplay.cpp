/**
 *  This file is a part of Promoe, an XMMS2 Client.
 *
 *  Copyright (C) 2005-2008 XMMS2 Team
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

#include "timedisplay.h"

#include <QPainter>
#include <QPixmap>
#include <QMap>


TimeDisplay::TimeDisplay (QWidget *parent) : QWidget (parent)
{
	setFixedSize (63, 13);
}

/*
 * This method takes the playtime in seconds
 */
void TimeDisplay::setTime (int time)
{
	// Hack to make display hours and seconds instead of seconds and minutes
	// if time (or reversetime) is 100 Minutes or longer
	if ((time >= 6000) || (time <= -6000)) {
		time /= 60;
	}

	if (m_time == time) return;

	m_time = time;
	update ();
}

void
TimeDisplay::paintEvent (QPaintEvent *event)
{
	if (m_pixmaps.size () < 11) {
		qDebug ("too small");
		return;
	}
	QPainter paint;
	paint.begin (this);

	if (m_time < 0) {
		// draw minus
		paint.drawPixmap (0, 0, m_pixmaps[11]);
	} else {
		// draw blank
		paint.drawPixmap (0, 0, m_pixmaps[10]);
	}
	uint showtime = abs(m_time);
	if (showtime < 6000) {
		// draw minutes
		uint min = showtime / 60;
		paint.drawPixmap (12, 0, m_pixmaps[min/10]);
		paint.drawPixmap (24, 0, m_pixmaps[min%10]);
		// draw seconds
		uint sec = showtime % 60;
		paint.drawPixmap (42, 0, m_pixmaps[sec/10]);
		paint.drawPixmap (54, 0, m_pixmaps[sec%10]);
	} else {
		// Just give up and draw '-' if min would become 100 or bigger
		paint.drawPixmap (12, 0, m_pixmaps[11]);
		paint.drawPixmap (24, 0, m_pixmaps[11]);
		paint.drawPixmap (42, 0, m_pixmaps[11]);
		paint.drawPixmap (54, 0, m_pixmaps[11]);

	}
	paint.end ();
}

void
TimeDisplay::mouseReleaseEvent (QMouseEvent *event)
{
	emit clicked();
}
