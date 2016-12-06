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

#include <string>

namespace util {
namespace task {
	class Dispatcher;
}
}

namespace tuner {
	class Provider;
	class ResourceManager;

	namespace player {
		class Delegate;
		class Player;
		namespace ts {
			class Output;
		}
	}
}

namespace pvr {

class CaptionPlayer;

namespace dvb {

class CaptionViewer;

class Delegate {
public:
	Delegate();
	virtual ~Delegate();

	virtual util::task::Dispatcher *dispatcher() const=0;
	tuner::Provider *createProvider() const;
	virtual tuner::ResourceManager *createResources() const=0;
	virtual const std::string spec() const;
	virtual bool withEPG() const;
	virtual bool withCC() const;
	virtual bool withEWBS() const;
	virtual int areaCode() const;
	CaptionViewer *createCaptionViewer( bool isCC ) const;
	tuner::player::Player *createPlayer() const;

protected:
	virtual tuner::Provider *createProviderImpl() const;
	virtual tuner::player::Delegate *createPlayerDelegate() const;
	virtual CaptionPlayer *createCaptionPlayer(bool isCC) const;

	tuner::player::Delegate *createPlayerDelegate( const std::string &use ) const;
};

}
}

