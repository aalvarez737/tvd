/*******************************************************************************

  Copyright (C) 2010, 2011 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV-util implementation.

    DTV-util is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV-util is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementaci�n de DTV-util.

    DTV-util es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los t�rminos de la Licencia P�blica General Reducida GNU como es publicada por la
  Free Software Foundation, seg�n la versi�n 2 de la licencia.

    DTV-util se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANT�A; ni siquiera la garant�a impl�cita de COMERCIALIZACI�N o ADECUACI�N
  PARA ALG�N PROP�SITO PARTICULAR. Para m�s detalles, revise la Licencia P�blica
  General Reducida GNU.

    Ud. deber�a haber recibido una copia de la Licencia P�blica General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include "handler.h"
#include "timer.h"
#include "../mcr.h"
#include <boost/bind.hpp>

namespace util {
namespace timer {

Handler::Handler()
	: _pool("util::timer")
{
}

Handler::~Handler()
{
	clear();
}

util::id::Ident Handler::add( int ms, const Callback &callback ) {
	util::id::Ident id = _pool.alloc();
	_timers.push_back( new impl::Timer( id, ms, callback ) );
	return id;
}

void Handler::rm( const util::id::Ident &timerID ) {
	TimerList::iterator it=std::find_if(
		_timers.begin(),
		_timers.end(),
		boost::bind(&impl::Timer::id,_1) == timerID );
	if (it != _timers.end()) {
		delete (*it);
		_timers.erase( it );
	}
}

void Handler::reset( const util::id::Ident &timerID ) {
	TimerList::iterator it=std::find_if(
		_timers.begin(),
		_timers.end(),
		boost::bind(&impl::Timer::id,_1) == timerID );
	if (it != _timers.end()) {
		(*it)->reset();
		_timers.erase( it );
	}
}

void Handler::clear() {
	CLEAN_ALL( impl::Timer *, _timers );
}
	
int Handler::consume() {
	int min = std::numeric_limits<int>::max();
	
	if (!_timers.empty()) {
		std::vector<impl::Timer *> expired;
		impl::pt::ptime now = impl::pt::microsec_clock::local_time();

		//	Consume elapsed time, if any expired add to post processing
		BOOST_FOREACH( impl::Timer *timer, _timers ) {
			if (timer->consume( now )) {
				expired.push_back( timer );
			}
			if (timer->timer() < min) {
				min = timer->timer();
			}
		}

		//	Process timers
		BOOST_FOREACH( impl::Timer *timer, expired ) {
			timer->fire();
		}
	}

	if (min == std::numeric_limits<int>::max()) {
		min = -1;
	}

	return min;
}

}
}

