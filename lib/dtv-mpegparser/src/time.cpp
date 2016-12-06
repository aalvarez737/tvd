/*******************************************************************************

  Copyright (C) 2010, 2011 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV-connector implementation.

    DTV-connector is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV-connector is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementaci�n de DTV-connector.

    DTV-connector es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los t�rminos de la Licencia P�blica General Reducida GNU como es publicada por la
  Free Software Foundation, seg�n la versi�n 2 de la licencia.

    DTV-connector se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANT�A; ni siquiera la garant�a impl�cita de COMERCIALIZACI�N o ADECUACI�N
  PARA ALG�N PROP�SITO PARTICULAR. Para m�s detalles, revise la Licencia P�blica
  General Reducida GNU.

    Ud. deber�a haber recibido una copia de la Licencia P�blica General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/
#include "time.h"
#include <util/assert.h>

namespace tuner {

namespace time {
	Time clock;
}

Time::Time() {
}
	
Time::~Time() {
}

bool Time::isValid() {
	_mutex.lock();
	bool valid = _systemDelta.is_special() ? false : true;
	_mutex.unlock();
	return valid;
}

Time::TimeValidSignal &Time::onTimeValidChanged() {
	return _signal;
}

void Time::get( pt::ptime &value ) {
	_mutex.lock();
	value = pt::microsec_clock::local_time();
	if (!_systemDelta.is_special()) {
		value -= _systemDelta;
	}
	_mutex.unlock();	
}

void Time::invalidate() {
	_mutex.lock();
	_systemDelta = pt::time_duration(pt::pos_infin);
	DTV_ASSERT(_systemDelta.is_special());
	_mutex.unlock();
	_signal( false );
}

void Time::update( const pt::ptime &now ) {
	_mutex.lock();
	pt::ptime cur = pt::microsec_clock::local_time();
	bool notify = _systemDelta.is_special() ? true : false;
	_systemDelta = cur-now;
	_mutex.unlock();

	if (notify) {
		_signal( true );
	}
}

}

