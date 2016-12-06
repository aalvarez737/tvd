/*******************************************************************************

	Copyright (C) 2010, 2013 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

	This file is part of DTV-canvas implementation.

	DTV-canvas is free software: you can redistribute it and/or modify it
	under the terms of the GNU Lesser General Public License as published by the Free
	Software Foundation, either version 2 of the License.

	DTV-canvas is distributed in the hope that it will be useful, but WITHOUT ANY
	WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
	A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License along with
	this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

	Este archivo es parte de la implementaci�n de DTV-canvas.

	DTV-canvas es Software Libre: Ud. puede redistribuirlo y/o modificarlo
	bajo los t�rminos de la Licencia P�blica General Reducida GNU como es publicada por la
	Free Software Foundation, seg�n la versi�n 2 de la licencia.

	DTV-canvas se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
	GARANT�A; ni siquiera la garant�a impl�cita de COMERCIALIZACI�N o ADECUACI�N
	PARA ALG�N PROP�SITO PARTICULAR. Para m�s detalles, revise la Licencia P�blica
	General Reducida GNU.

	Ud. deber�a haber recibido una copia de la Licencia P�blica General Reducida GNU
	junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/

#pragma once

#include "types.h"
#include "../../mediaplayer.h"
#include <boost/thread.hpp>
#include <string>

namespace canvas {

class StreamsInfo;

namespace ffmpeg {

class MediaPlayer : public canvas::MediaPlayer {
public:
	explicit MediaPlayer( System *sys );
	virtual ~MediaPlayer();

	//	Implementation
	int stopInput() const;

protected:
	//	Aux volume
	virtual bool startImpl( const std::string &url );
	virtual void stopImpl();
	virtual void pauseImpl( bool needPause );

	virtual void muteImpl( bool needsMute );
	virtual void volumeImpl( Volume vol );

	virtual void moveResizeImpl( const Rect &rect );

	//	Streams info implementation
	virtual canvas::StreamsInfo *createStreamsInfo();
	virtual bool switchVideoStreamImpl( int id );
	virtual bool switchAudioStreamImpl( int id );
	virtual bool switchSubtitleStreamImpl( int id );

	bool open( const std::string &url );
	void close();

	//	Input aux
	void inputThread();
	bool areQueuesFull() const;

	//	Streams
	Stream *getStreamByIndex( int sIndex ) const;
	Stream *getStream( stream::type t ) const;

	//	Clock
	double getMasterClock() const;
	double getExternalClock() const;

	//	Video
	void videoThread();
	bool queuePicture( AVFrame *srcFrame, double pts, int64_t pos );
	int getVideoFrame( AVFrame *frame, uint64_t *pts, AVPacket *pkt );

private:
	AVFormatContext *_ic;

	//	Clock
	sync::type _syncClock;

	//	Input
	bool _exit;
	boost::thread _iThread;
	boost::mutex _iMutex;
	boost::condition_variable _iWakeup;

	//	Streams
	Stream *_streams[stream::last];
};

}
}
