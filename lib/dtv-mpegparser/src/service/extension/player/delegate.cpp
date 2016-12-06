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

#include "delegate.h"
#include "player.h"
#include "extension.h"
#include "../../../provider/filter.h"
#include <util/log.h>
#include <util/assert.h>
#include <util/mcr.h>

namespace tuner {
namespace player {

Delegate::Delegate()
	: _player(NULL), _esType(pes::type::other)
{
}


Delegate::~Delegate()
{
	DTV_ASSERT(!_player);
}

bool Delegate::initialize( Player *player, pes::type::type esType ) {
	_player = player;
	_esType = esType;
	DTV_ASSERT(_player);
	if (!init()) {
		LWARN( "Delegate", "Cannot initialize delegate" );
		_player = NULL;
		_esType = pes::type::other;
		return false;
	}

	return true;
}

void Delegate::finalize() {
	fin();
	_player = NULL;
}

bool Delegate::init() {
	return true;
}

void Delegate::fin() {
}

StreamInfo *Delegate::canPlay( const ElementaryInfo & /*info*/, ID /*tag*/ ) const {
	return NULL;
}

void Delegate::start() {
}

void Delegate::stop() {
}

pes::type::type Delegate::esType() const {
	return _esType;
}

Player *Delegate::player() const {
	DTV_ASSERT(_player);
	return _player;
}

const std::string Delegate::url() const {
	return player()->makeURL( urlType() );
}

bool Delegate::startStream( ID pid, pes::type::type esType ) {
	pes::FilterParams params;
	params.pid  = pid;
	params.type = esType;
	params.mode = mode();
	params.pipe = pipe(esType);
	return player()->extension()->startStream( &params );
}

void Delegate::stopStream( ID pid ) {
	player()->extension()->stopStream( pid );
}

pes::mode::type Delegate::mode() const {
	return pes::mode::decode;
}

stream::Pipe *Delegate::pipe( pes::type::type /*esType*/ ) const {
	return NULL;
}

const std::string Delegate::urlType() const {
	return "decode";
}

//	AvDelegate
AvDelegate::AvDelegate()
{
}

AvDelegate::~AvDelegate()
{
}

pes::mode::type AvDelegate::mode() const {
	return pes::mode::pvr;
}

const std::string AvDelegate::urlType() const {
	return "srvdtv";
}

//	Forward delegate
ForwardDelegate::ForwardDelegate( Delegate *dlg )
	: _dlg(dlg)
{
}

ForwardDelegate::~ForwardDelegate() {}

bool ForwardDelegate::startStream( ID pid, pes::type::type esType ) {
	return _dlg->startStream( pid, esType );
}

void ForwardDelegate::stopStream( ID pid ) {
	_dlg->stopStream( pid );
}

}
}

