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

	Este archivo es parte de la implementación de DTV-pvr.

		DTV-pvr es Software Libre: Ud. puede redistribuirlo y/o modificarlo
	bajo los términos de la Licencia Pública General Reducida GNU como es publicada por la
	Free Software Foundation, según la versión 2 de la licencia.

		DTV-pvr se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
	GARANTÍA; ni siquiera la garantía implícita de COMERCIALIZACIÓN o ADECUACIÓN
	PARA ALGÚN PROPÓSITO PARTICULAR. Para más detalles, revise la Licencia Pública
	General Reducida GNU.

		Ud. debería haber recibido una copia de la Licencia Pública General Reducida GNU
	junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/

#pragma once

#include <string>

namespace pvr {
namespace parental {

class Control {
public:
	Control();
	virtual ~Control();

	virtual bool hasSex() const=0;
	virtual bool hasViolence() const=0;
	virtual bool hasDrugs() const=0;
	virtual int age() const=0;

	bool operator==( const Control &control ) const;

	std::string getAgeName() const;
	std::string getContentName() const;
};

class WithoutControl : public Control {
public:
	WithoutControl() {}
	virtual ~WithoutControl() {}

	virtual bool hasSex() const { return false; }
	virtual bool hasViolence() const { return false; }
	virtual bool hasDrugs() const { return false; }
	virtual int age() const { return 0; }
};

Control *defaultControl();

}
}

