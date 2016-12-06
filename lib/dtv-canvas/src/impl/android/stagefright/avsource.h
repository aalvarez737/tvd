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

#include <media/stagefright/dtvmediasource.h>
#include <string>

namespace a = ::android;

struct AVFormatContext;
struct AVCodecContext;

namespace canvas {
namespace android {
namespace stagefright {

class AVFormatSource {
public:
	AVFormatSource();
	virtual ~AVFormatSource();

	bool initialize( const std::string &url );
	void finalize();
    
	a::status_t start( a::MetaData *params=NULL );
	a::status_t stop();

	a::sp<a::MetaData> getFormat();
	
	a::status_t read( a::MediaBuffer **buffer, const a::MediaSource::ReadOptions *options=NULL );

private:
	AVFormatContext *_dataSource;
	AVCodecContext *_videoTrack;
	a::MediaBufferGroup _group;
	a::sp<a::MetaData> _format;
	int _videoIndex;
};

}
}
}

