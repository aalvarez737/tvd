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

#include "tunerplayer.h"
#include <util/log.h>

namespace pvr {

TunerPlayer::TunerPlayer()
{
}

TunerPlayer::~TunerPlayer()
{
}

bool TunerPlayer::initialize() {
	return true;
}

void TunerPlayer::finalize() {
}

void TunerPlayer::onMediaChanged( const MediaChangedCallback &callback ) {
	_onMediaChanged = callback;
}

//	Player methods
int TunerPlayer::nextVideo() {
	return -1;
}

int TunerPlayer::videoCount() const {
	return 0;
}

void TunerPlayer::videoInfo( int /*id=-1*/, Channel * /*ch*/, info::Basic & /*info*/ ) const {
}

int TunerPlayer::nextAudio() {
	return -1;
}

int TunerPlayer::audioCount() const {
	return 0;
}

void TunerPlayer::audioInfo( int /*id=-1*/, Channel * /*ch*/, info::Audio & /*info*/ ) const {
}

int TunerPlayer::nextSubtitle() {
	return -1;
}

int TunerPlayer::subtitleCount() const {
	return 0;
}

void TunerPlayer::subtitleInfo( int /*id=-1*/, Channel * /*ch*/, info::Basic & /*info*/ ) const {
}

int TunerPlayer::playVideoStream( int /*streamID*/, std::string & /*url*/ ) {
	return -1;
}

void TunerPlayer::stopVideoStream( int /*playerID*/ ) {
}

void TunerPlayer::notifyStart( bool start ) {
	LDEBUG( "Tuner", "Start stream: start=%d", start );
	if (!_onMediaChanged.empty()) {
		_onMediaChanged(start);
	}
}

}

