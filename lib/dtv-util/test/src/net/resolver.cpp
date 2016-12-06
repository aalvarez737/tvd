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
#include "../../../src/net/resolver.h"
#include <gtest/gtest.h>

TEST( NetResolver, hostname ) {
	std::vector<util::net::SockAddr> addresses;

	const char *host = "localhost";
	ASSERT_TRUE( util::net::resolve( addresses, host ) );
	ASSERT_TRUE( addresses.size() == 2*3 );
}

TEST( NetResolver, hostname_port ) {
	std::vector<util::net::SockAddr> addresses;

	const char *host = "localhost";
	const char *port = "80";	
	ASSERT_TRUE( util::net::resolve( addresses, host, port ) );
	ASSERT_TRUE( addresses.size() == 2*3 );
}

TEST( NetResolver, hostname_port_ipv4 ) {
	std::vector<util::net::SockAddr> addresses;

	const char *host = "www.tecnologia.lifia.info.unlp.edu.ar";
	const char *port = "80";
	ASSERT_TRUE( util::net::resolve( addresses, host, port, util::net::family::ipv4, util::net::type::stream ) );
	ASSERT_TRUE( addresses.size() == 1 );
}

TEST( NetResolver, hostname_port_stream ) {
	std::vector<util::net::SockAddr> addresses;

	const char *host = "www.tecnologia.lifia.info.unlp.edu.ar";
	const char *port = "80";
	ASSERT_TRUE( util::net::resolve( addresses, host, port, util::net::family::any, util::net::type::stream ) );
	ASSERT_TRUE( addresses.size() == 1 );
}

TEST( NetResolver, hostname_port_dgram ) {
	std::vector<util::net::SockAddr> addresses;

	const char *host = "www.tecnologia.lifia.info.unlp.edu.ar";
	const char *port = "80";
	ASSERT_TRUE( util::net::resolve( addresses, host, port, util::net::family::any, util::net::type::dgram ) );
	ASSERT_TRUE( addresses.size() == 1 );
}

