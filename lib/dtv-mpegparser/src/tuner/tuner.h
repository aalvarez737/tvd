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
#pragma once

#include "types.h"
#include <vector>

namespace tuner {

class Service;
class Extension;
class ServiceProvider;
class Provider;
class ResourceManager;

class Tuner {
public:
	Tuner( Provider *provider, ResourceManager *resMgr );
	~Tuner();

	//	Setup
	void attach( Extension *ext );
	void detach( Extension *ext );
	void onServiceReady( const OnServiceReadyCallback &callback );

	//	Initialize/Finalize
	bool initialize();
	void finalize();

	//	Start/Stop
	void start();
	void stop();

	//	Tune service
	bool startService( size_t networkID, ID srvID );
	void stopService( ID srvID );
	void stopAllServices();

	//	Scan
	bool isScanning() const;
	void startScan( ScanIterator *iter );
	void stopScan();

	//	Getters
	void status( status::Type &st ) const;
	size_t currentNetwork() const;
	std::string currentNetworkName() const;
	size_t networks() const;

protected:
	//	Aux tune/scan
	void onLockChanged();
	void onLockTimeout();
	bool startNetwork( size_t net );
	void nextScan();
	void endNetScan();

	//	Aux scan extension notification
	void serviceReady( Service *srv );

private:
	ScanIterator *_scanIt;
	Provider *_provider;
	ServiceProvider *_srvMgr;
	OnServiceReadyCallback _onServiceReady;
};

}

