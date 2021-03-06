/*******************************************************************************

  Copyright (C) 2010, 2013 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV-canvas implementation.

    DTV-canvas is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV-canvas is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementación de DTV-canvas.

    DTV-canvas es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los términos de la Licencia Pública General Reducida GNU como es publicada por la
  Free Software Foundation, según la versión 2 de la licencia.

    DTV-canvas se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANTÍA; ni siquiera la garantía implícita de COMERCIALIZACIÓN o ADECUACIÓN
  PARA ALGÚN PROPÓSITO PARTICULAR. Para más detalles, revise la Licencia Pública
  General Reducida GNU.

    Ud. debería haber recibido una copia de la Licencia Pública General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/

#pragma once

#include "../../fontinfo.h"
#include "../../canvas.h"

typedef struct FT_LibraryRec_ *FT_Library;
typedef unsigned int GLuint;

namespace canvas {
namespace gl {

class FontLoader;
class Font;
class Surface;

bool initGL();

class Canvas : public canvas::Canvas {
public:
	Canvas();
	virtual ~Canvas();

	virtual std::string name();

	GLuint drawingShaders() const;
	GLuint blitingShaders() const;
	GLuint textShaders() const;

protected:
	virtual bool init();
	virtual void fin();

	virtual canvas::Surface *createSurfaceImpl( ImageData *img );
	virtual canvas::Surface *createSurfaceImpl( const Rect &rect );
	virtual canvas::Surface *createSurfaceImpl( const std::string &file );

	virtual canvas::Font *createFont( const std::string &filename, size_t size );

private:
	FT_Library _freeType;
};

}
}
