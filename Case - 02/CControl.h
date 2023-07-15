#pragma once
#ifndef __CCONTROL_H__
#define __CCONTROL_H__

#include "CBitmap.h"
#include "CPacman.h"
#include "CFantasma.h"

class CControl {

public:
	//constructor de CControl.
	CControl(Graphics^ gr) {

		ANCHO_P = (int)gr->VisibleClipBounds.Width;
		ALTO_P = (int)gr->VisibleClipBounds.Height;

		//creando ref. a vector CEntidad.
		vEntidad = new vector<CEntidad*>;

		//agregando pacman.
		vEntidad->push_back(new CPacman(10, 10));

		//agregando fantasmas.
		for (int i = 0; i < 5; ++i) {
			__generarFantasma();
		}
	}

	//destructor de CControl.
	~CControl() {

		//liberando memoria.
		for (CEntidad* _iter : *vEntidad) {
			delete _iter;
		}
		delete vEntidad;
	}

	//métodos de clase PUBLICOS.
	void procesarJuego(Graphics^ gr, CBitmapV^ bitmaps) {

		//pintando TODAS las entidades.
		__pintarEntidades(gr, bitmaps);
		//moviendo TODAS las entidades.
		__moverEntidades(gr);
	}
	void moverPersona(char key) {

		CPacman* pacman = (CPacman*)vEntidad->at(0);
		//movimiento de pacman.
		pacman->moverPacman(key);
	}

public:
	int ANCHO_P, ALTO_P;
	vector<CEntidad*>* vEntidad;

	//métodos de clase PRIVADOS.
	void __moverEntidades(Graphics^ gr) {

		//mov. de entidades.
		for (CEntidad* _iter : *vEntidad) {
			_iter->mover(gr);
		}
	}
	void __pintarEntidades(Graphics^ gr, CBitmapV^ bitmaps) {

		//obteniendo bitmaps para el pintado de entidades.
		Bitmap^ bmpPacman = bitmaps->searchBitmap("pacman");
		bmpPacman->MakeTransparent();

		Bitmap^ bmpFantasma = bitmaps->searchBitmap("fantasma");
		bmpPacman->MakeTransparent();

		//pintando entidades con su bitmap respectivo.
		for (CEntidad* _iter : *vEntidad) {

			//eva. entidades que sean tipo "pacman".
			if (_iter->getEntidad()._Equal("pacman")) {
				_iter->pintar(gr, bmpPacman);
			}
			//eva. entidades que sean tipo "fantasma".
			else if (_iter->getEntidad()._Equal("fantasma")) {
				_iter->pintar(gr, bmpFantasma);
			}
		}
	}
	void __generarFantasma() {

		int speeds[] = { -6, -8, 6, 8 };

		int x, y, dx, dy, con = 0;

		while (con == 0) {

			x = nextInt((ANCHO_P / 2), ANCHO_P - 50);
			y = nextInt(10, ALTO_P - 62);

			dx = speeds[nextInt(0, 3)];
			dy = speeds[nextInt(0, 3)];

			CFantasma* fantasma = new CFantasma(x, y, dx, dy);

			if (!__entidadColisionaCon("fantasma", fantasma->area())) {
				vEntidad->push_back(fantasma);
				con = 1;
			}

			if (con == 0) {
				delete fantasma;
			}
		}
	}
	bool __entidadColisionaCon(string entidad, Rectangle rec) {

		for (CEntidad* _iter : *vEntidad) {

			//eva. entidades que sean tipo "pacman".
			if (_iter->getEntidad()._Equal(entidad)) {

				if (_iter->area().IntersectsWith(rec)) {

					return true;
				}
			}
		}

		return false;
	}
};

#endif