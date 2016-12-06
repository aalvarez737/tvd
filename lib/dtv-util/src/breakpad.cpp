/*******************************************************************************

  Copyright (C) 2010, 2011 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV implementation.

    DTV is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementaci�n de DTV.

    DTV es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los t�rminos de la Licencia P�blica General Reducida GNU como es publicada por la
  Free Software Foundation, seg�n la versi�n 2 de la licencia.

    DTV se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANT�A; ni siquiera la garant�a impl�cita de COMERCIALIZACI�N o ADECUACI�N
  PARA ALG�N PROP�SITO PARTICULAR. Para m�s detalles, revise la Licencia P�blica
  General Reducida GNU.

    Ud. deber�a haber recibido una copia de la Licencia P�blica General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include "assert.h"
#include "log.h"
#include "client/linux/handler/exception_handler.h"

namespace util {

namespace impl {

static google_breakpad::MinidumpDescriptor *descriptor = NULL;
static google_breakpad::ExceptionHandler *eHandler = NULL;

static bool dumpCallback(
	const google_breakpad::MinidumpDescriptor& descriptor,
	void* /*context*/,
	bool succeeded )
{
	util::log::fin();
	printf("[util] Dump generated in: %s\n", descriptor.path());
	return succeeded;
}

}	//	namespace impl

void setupUnhandledException() {
	impl::descriptor = new google_breakpad::MinidumpDescriptor("/tmp");
	impl::eHandler = new google_breakpad::ExceptionHandler(
		*impl::descriptor,
		NULL,
		impl::dumpCallback,
		NULL,
		true,
		-1
	);
}

void dumpBacktrace() {
}

}
