/*******************************************************************************

  Copyright (C) 2010, 2013 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV-zapper implementation.

    DTV-zapper is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV-zapper is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementaci�n de DTV-zapper.

    DTV-zapper es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los t�rminos de la Licencia P�blica General Reducida GNU como es publicada por la
  Free Software Foundation, seg�n la versi�n 2 de la licencia.

    DTV-zapper se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANT�A; ni siquiera la garant�a impl�cita de COMERCIALIZACI�N o ADECUACI�N
  PARA ALG�N PROP�SITO PARTICULAR. Para m�s detalles, revise la Licencia P�blica
  General Reducida GNU.

    Ud. deber�a haber recibido una copia de la Licencia P�blica General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include "tunerdelegate.h"
#include "closedcaptionplayer.h"
#include "player.h"
#include "tvd.h"
#include <mpegparser/service/extension/player/caption/delegate.h>
#include <mpegparser/service/extension/player/player.h>
#include <mpegparser/service/extension/player/extension.h>
#include <mpegparser/service/extension/time/timeextension.h>
#include <mpegparser/provider/provider.h>
#include <mpegparser/resourcemanager.h>
#include <util/assert.h>
#include <boost/filesystem.hpp>

#define RESOURCES_MEMORY_BLOCKS   1000
#define RESOURCES_MAX_MODULES     1000
#define RESOURCES_MAX_MODULE_SIZE (100*1024*1024)

namespace tvd {

namespace bfs = boost::filesystem;

TunerDelegate::TunerDelegate( Tvd *tvd )
	: _tvd(tvd)
{
	DTV_ASSERT(_tvd);
}

TunerDelegate::~TunerDelegate()
{
}

util::task::Dispatcher *TunerDelegate::dispatcher() const {
	return _tvd->dispatcher();
}

tuner::ResourceManager *TunerDelegate::createResources() const {
	//	Create resources manager from ramDisk
	bfs::path tmp(_tvd->ramDisk());
	tmp /= "resources";
	return new tuner::ResourceManager(
		tmp.string(),
		RESOURCES_MEMORY_BLOCKS,
		RESOURCES_MAX_MODULES,
		RESOURCES_MAX_MODULE_SIZE
	);
}

int TunerDelegate::areaCode() const {
	return _tvd->areaCode();
}

bool TunerDelegate::withEWBS() const {
	return true;
}

bool TunerDelegate::withCC() const {
	return true;
}

pvr::CaptionPlayer *TunerDelegate::createCaptionPlayer(bool isCC) const {
	return new ClosedCaptionPlayer(_tvd->defaultPlayer(),isCC);
}

tuner::player::Delegate *TunerDelegate::createPlayerDelegate() const {
	return pvr::dvb::Delegate::createPlayerDelegate( "ts" );
}

}
