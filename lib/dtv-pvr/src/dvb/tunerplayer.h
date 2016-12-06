/*******************************************************************************

  Copyright (C) 2010, 2013 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV-pvr implementation.

    DTV-pvr is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV-pvr is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementaci�n de DTV-pvr.

    DTV-pvr es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los t�rminos de la Licencia P�blica General Reducida GNU como es publicada por la
  Free Software Foundation, seg�n la versi�n 2 de la licencia.

    DTV-pvr se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANT�A; ni siquiera la garant�a impl�cita de COMERCIALIZACI�N o ADECUACI�N
  PARA ALG�N PROP�SITO PARTICULAR. Para m�s detalles, revise la Licencia P�blica
  General Reducida GNU.

    Ud. deber�a haber recibido una copia de la Licencia P�blica General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/

#pragma once

#include "../tunerplayer.h"
#include <mpegparser/types.h>
#include <vector>

namespace util {
namespace task {
	class Dispatcher;
}
}

namespace util {
namespace task {
	class Dispatcher;
}
}

namespace tuner {
namespace player {
	class Player;
	namespace es {
		class Player;
	}
}
}

namespace pvr {

class CaptionPlayer;

namespace dvb {

class Tuner;

class TunerPlayer : public pvr::TunerPlayer {
public:
	explicit TunerPlayer( Tuner *tuner );
	virtual ~TunerPlayer();

	virtual bool initialize();
	virtual void finalize();

	//	Player methods
	virtual void play( Channel *ch );
	virtual void stop( Channel *ch );

	virtual int nextVideo();
	virtual int videoCount() const;
	virtual void videoInfo( int streamID, Channel *ch, info::Basic &info ) const;

	virtual int nextAudio();
	virtual int audioCount() const;
	virtual void audioInfo( int streamID, Channel *ch, info::Audio &info ) const;

	virtual int nextSubtitle();
	virtual int subtitleCount() const;
	virtual void subtitleInfo( int streamID, Channel *ch, info::Basic &info ) const;

	virtual int playVideoStream( int streamID, std::string &url );
	virtual void stopVideoStream( int playerID );

	//	Getters
	virtual const std::string url() const;
	util::task::Dispatcher *dispatcher() const;

protected:
	//	MPEG player
	void onStartMedia( bool start );
	tuner::player::Player *player() const;

private:
	Tuner *_tuner;
	tuner::player::Player *_player;
	CaptionPlayer *_ccPlayer;
};

}
}

