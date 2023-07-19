#pragma once
#ifndef __CCONTROL_H__
#define __CCONTROL_H__

#include "CBitmap.h"
#include "CPacman.h"
#include "CPacdot.h"
#include "CFantasma.h"
#include "CBono.h"

class CControl {

public:
	//constructor de CControl.
	CControl(Graphics^ gr) {

		ANCHO_P = (int)gr->VisibleClipBounds.Width;
		ALTO_P = (int)gr->VisibleClipBounds.Height;

		//creando ref. a vector CEntidad.
		vEntidad = new vector<CEntidad*>;

		//agregando pacman.
		vEntidad->push_back(new CPacman(10, 50));

		//agregando fantasmas.
		for (int i = 0; i < 5; ++i) {
			__generarFantasma();
		}
		//agregando pacdots.
		for (int i = 0; i < 15; ++i) {
			__generarPacDot();
		}
		//agregando bono.
		__generarBono();
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

		__colisionesTotales();

		//pintando TODAS las entidades.
		__pintarEntidades(gr, bitmaps);
		//moviendo TODAS las entidades.
		__moverEntidades(gr);

		__verificacionesTotales();
	}
	void moverPersona(char key) {

		CPacman* pacman = (CPacman*)vEntidad->at(0);
		//movimiento de pacman.
		pacman->moverPacman(key);
	}

public:
	//atributos de clase CControl.
	int ANCHO_P, ALTO_P;

	vector<CEntidad*>* vEntidad;

	time_t super_vel_pacman;

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

		Bitmap^ bmpPacdot = bitmaps->searchBitmap("pacdot");
		bmpPacdot->MakeTransparent();

		Bitmap^ bmpBono = bitmaps->searchBitmap("bono");
		bmpBono->MakeTransparent();

		//pintando entidad pacman del arreglo.
		CPacman* pacman = (CPacman*)vEntidad->at(0);
		pacman->procesarPintar(gr, bmpPacman);

		//pintando entidades con su bitmap respectivo.
		for (CEntidad* _iter : *vEntidad) {

			//eva. entidades que sean tipo "fantasma".
			if (_iter->getEntidad()._Equal("fantasma")) {
				_iter->pintar(gr, bmpFantasma);
			}
			//eva. entidades que sean tipo "pacdot".
			else if (_iter->getEntidad()._Equal("pacdot")) {
				_iter->pintar(gr, bmpPacdot);
			}
			//eva. entidades que sean tipo "bono".
			else if (_iter->getEntidad()._Equal("bono")) {

				if (!pacman->getBono()) {
					_iter->pintar(gr, bmpBono);
				}
			}
		}
	}
	void __generarFantasma() {

		int speeds[] = { -6, -8, 6, 8 };

		int x, y, dx, dy, con = 0;

		while (con == 0) {

			x = nextInt((ANCHO_P / 2), ANCHO_P - 50);
			y = nextInt(50, ALTO_P - 62);

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
	void __generarPacDot() {

		int x, y, con = 0;

		while (con == 0) {

			x = nextInt(100, ANCHO_P - 150);
			y = nextInt(50, ALTO_P - 120);

			CPacdot* pacdot = new CPacdot(x, y);

			if (!__entidadColisionaCon("pacdot", pacdot->area())) {
				
				vEntidad->push_back(pacdot);
				con = 1;
			}

			if (con == 0) {
				delete pacdot;
			}
		}
	}
	void __generarBono() {

		int x, y, con = 0;

		while (con == 0) {

			x = nextInt(100, ANCHO_P - 80);
			y = nextInt(10, ALTO_P - 80);

			CBono* bono = new CBono(x, y);

			if (!__entidadColisionaCon("pacdot", bono->area())) {

				vEntidad->push_back(bono);
				con = 1;
			}

			if (con == 0) {
				delete bono;
			}
		}
	}

	void __quitarSuperVelocidad() {

		CPacman* pacman = (CPacman*)vEntidad->at(0);

		if (difftime(time(0), super_vel_pacman) >= 5 && pacman->getBono()) {

			pacman->setBono(false);
			pacman->setSpeed(pacman->getSaveSpeed());

			CBono* bono = (CBono*)vEntidad->at(vEntidad->size() - 1);

			bono->actualizarBono(nextInt(100, ANCHO_P - 80),
				nextInt(10, ALTO_P - 80));
		}
	}

	//colisiones y verificaciones.
	void __colisionesTotales() {

		__colisionPacmanBono();
		__colisionPacmanPacdot();
		__colisionPacmanFantasma();
	}
	void __verificacionesTotales() {
		__quitarSuperVelocidad();

		//verificando visible de entidades para dar una acción.
		__verificarVisible();
	}
	void __colisionPacmanBono() {

		CPacman* pacman = (CPacman*)vEntidad->at(0);

		if (__entidadColisionaCon("bono", pacman->area())) {

			//indicamos que pacman, tiene el bono.
			pacman->setBono(true);
			pacman->setSpeed(pacman->getSaveSpeed() * 2);
			super_vel_pacman = time(0);
		}
	}
	void __colisionPacmanPacdot() {

		CPacman* pacman = (CPacman*)vEntidad->at(0);

		for (int i = 1; i < vEntidad->size(); ++i) {

			if (vEntidad->at(i)->getEntidad()._Equal("pacdot")) {

				CPacdot* pacdot = (CPacdot*)vEntidad->at(i);

				if (pacdot->area().IntersectsWith(pacman->area())) {
					
					pacman->incrementarPuntos();
					pacdot->setVisible(false);
				}
			}
		}
	}
	void __colisionPacmanFantasma() {

		CPacman* pacman = (CPacman*)vEntidad->at(0);

		if (__entidadColisionaCon("fantasma", pacman->area())) {
			
			pacman->decrementarVidas();
			pacman->regresarPosicionInicial();
		}
	}
	bool __entidadColisionaCon(string entidad, Rectangle rec) {

		for (CEntidad* _iter : *vEntidad) {

			//eva. entidades que sean tipo "entidad".
			if (_iter->getEntidad()._Equal(entidad)) {

				if (_iter->area().IntersectsWith(rec)) {

					return true;
				}
			}
		}

		return false;
	}
	void __verificarVisible() {

		for (int i = 1; i < vEntidad->size(); ++i) {

			if (!vEntidad->at(i)->getVisible()) {
				//borramos entidad en pos. "i".
				__borrarEntidad(i);
			}
		}
	}
	void __borrarEntidad(int& pos) {

		//borramos elemento de vector "vEntidad" en índice "pos".
		vEntidad->erase(vEntidad->begin() + pos--);
	}
};

#endif