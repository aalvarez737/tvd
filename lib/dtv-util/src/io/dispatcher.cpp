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

#include "dispatcher.h"
#include "../assert.h"
#include "../log.h"
#include "generated/config.h"
#if IO_USE_EV
#	include "ev/dispatcher.h"
#endif
#if IO_USE_EVENT
#	include "event/dispatcher.h"
#endif
#if IO_USE_UV
#	include "uv/dispatcher.h"
#endif

#include "../cfg/configregistrator.h"
#include <boost/bind.hpp>

namespace util {
namespace io {

#if IO_USE_EV
#	define DEFAULT_IO_HANDLER "ev"
#elif IO_USE_EVENT
#	define DEFAULT_IO_HANDLER "event"
#elif IO_USE_UV
#	define DEFAULT_IO_HANDLER "uv"
#else
#	define DEFAULT_IO_HANDLER "dummy"
#endif

REGISTER_INIT_CONFIG( io ) {
	root().addNode( "io" )
		.addValue( "use", "Event loop to use", std::string(DEFAULT_IO_HANDLER) );
}

Dispatcher *Dispatcher::create() {
	const std::string &use = util::cfg::getValue<std::string> ("io.use");
	LINFO("io", "Using dispatcher: %s", use.c_str());
#if IO_USE_EV
	if (use == "ev") {
		return new ev::Dispatcher();
	}
#endif

#if IO_USE_EVENT
	if (use == "event") {
		return new event::Dispatcher();
	}
#endif

#if IO_USE_UV
	if (use == "uv") {
		return new uv::Dispatcher();
	}
#endif

	DTV_ASSERT(false);
	return NULL;
}

Dispatcher::Dispatcher()
	: _pool("ev::io"), _isEmbedded(false)
{
}

Dispatcher::~Dispatcher()
{
}

//	Initialization
bool Dispatcher::initialize() {
	return true;
}

void Dispatcher::finalize() {
}

void Dispatcher::embedded( bool val ) {
	_isEmbedded = val;
}

bool Dispatcher::isEmbedded() const {
	return _isEmbedded;
}

id::Ident Dispatcher::allocID() {
	return _pool.alloc();
}

}
}

