#include <xmmsclient/xmmsclient++.h>

#include "XmmsQT4.h"
#include "XMMSHandler.h"

#include <QErrorMessage>

XMMSHandler *XMMSHandler::singleton = NULL;

XMMSHandler *XMMSHandler::getInstance (void)
{
	if (!singleton) {
		singleton = new XMMSHandler ();
	}

	return singleton;
}

XMMSHandler::XMMSHandler (void) : sigc::trackable ()
{
	m_xmmsc = new XMMSClient ("promoe");

	if (!m_xmmsc->connect (getenv ("XMMS_PATH"))) {
		QErrorMessage *err = new QErrorMessage ();
		err->showMessage ("Couldn't connect to XMMS2, please try again.");
		err->exec ();
		exit (-1);
	}
	m_qt4 = new XmmsQT4 (m_xmmsc->getConn (), qApp);

	XMMSResultValue<uint> *r = m_xmmsc->signal_playback_playtime ();
	r->connect (sigc::mem_fun (this, &XMMSHandler::playback_playtime));

	r = m_xmmsc->playback_current_id ();
	r->connect (sigc::mem_fun (this, &XMMSHandler::playback_current_id));

	r = m_xmmsc->broadcast_playback_current_id ();
	r->connect (sigc::mem_fun (this, &XMMSHandler::playback_current_id));

	r = m_xmmsc->broadcast_playback_status ();
	r->connect (sigc::mem_fun (this, &XMMSHandler::playback_status));

	XMMSResultValueList<uint> *l = m_xmmsc->playlist_list ();
	l->connect (sigc::mem_fun (this, &XMMSHandler::playlist_list));
}

void
XMMSHandler::playlist_list (XMMSResultValueList<uint> *res) 
{
	delete res;
}

void
XMMSHandler::playback_status (XMMSResultValue<uint> *res)
{
	uint status;
	res->getValue (&status);

	emit playbackStatusChanged (status);
}

void 
XMMSHandler::playback_playtime (XMMSResultValue<uint> *res)
{
	uint i;
	res->getValue (&i);

	emit playtimeChanged (i);
	
	res->restart ();
}

void 
XMMSHandler::playback_current_id (XMMSResultValue<uint> *res)
{
	uint i;
	res->getValue (&i);

	if (i > 0) {
		XMMSResultDict *r = m_xmmsc->medialib_get_info (i);
		r->connect (sigc::mem_fun (this, &XMMSHandler::medialib_info));
	}

	if (res->getClass() == XMMSC_RESULT_CLASS_DEFAULT) {
		delete res;
	}
}

void
XMMSHandler::setPlaytime (void)
{
	/*
	uint pos = m_mw->getMD ()->m_slider->getPos();
	qDebug ("pos = %d", pos);
	delete m_xmmsc->playback_seek_ms (pos);
	*/

}

void 
XMMSHandler::medialib_info (XMMSResultDict *res)
{
	int bitrate, samplerate, channels, duration;
	char str[4096];

	// Make this NICER! 
	res->entryFormat (str, 4096, "${artist} - ${album} - ${title}");


	res->getValue ("bitrate", &bitrate);
	res->getValue ("samplerate", &samplerate);
	res->getValue ("channels:out", &channels);
	res->getValue ("duration", &duration);

	emit mediainfoChanged (QString::fromUtf8 (str), bitrate,
	                       samplerate, channels, duration);

	delete res;
}

XMMSHandler::~XMMSHandler ()
{
}

