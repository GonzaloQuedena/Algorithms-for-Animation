#pragma once
#ifndef __CPACMAN_H__
#define __CPACMAN_H__

#include "CEntidad.h"

class CPacman : public CEntidad {

public:
	CPacman(int x, int y)
		: CEntidad(x, y), puntos(0), vidas(5), bono(false) {

		save_X = x;
		save_Y = y;

		speed = save_speed = 12;

		dx = speed;

		width = 89;
		height = 75;

		limit_idx = 1;

		zoom = 0.5f;

		entidad = "pacman";
	}

	void moverPacman(char key) {

		switch (key) {

		case 'W':
			dy = -speed;
			dx = 0;
			break;

		case 'S':
			dy = speed;
			dx = 0;
			break;

		case 'A':
			dx = -speed;
			dy = 0;
			break;

		case 'D':
			dx = speed;
			dy = 0;
			break;

		}
	}

	void procesarPintar(Graphics^ gr, Bitmap^ bmp) {

		//pintando estadísticas de entidad.
		__pintarStats(gr);
		//pintando entidad.
		pintar(gr, bmp);
	}

	void decrementarVidas() {
		--vidas;
	}

	void incrementarPuntos() {
		++puntos;
	}

	void regresarVelocidadNormal() {
		speed = save_speed;
	}
	
	void regresarPosicionInicial() {
		x = save_X;
		y = save_Y;
	}

	int getSaveSpeed() const {
		return save_speed;
	}

	void setSpeed(int arg) {
		speed = arg;
	}

	bool getBono() const {
		return bono;
	}

	void setBono(bool arg) {
		bono = arg;
	}

private:
	int vidas;
	bool bono;
	int speed, save_speed;
	int puntos;
	int save_X, save_Y;

	void __pintarStats(Graphics^ gr) {
		printS(gr, "VIDAS: " + vidas.ToString(), 14, 15, 10);
		printS(gr, "PACDOTS: " + puntos.ToString(), 14, 115, 10);
	}

	void __actualizarIMG() {

		if (dx > 0)idy = 0;
		else if (dx < 0)idy = 2;
		else if (dy > 0)idy = 1;
		else if (dy < 0)idy = 3;

		//actualizando ciclo de animación.
		idx = (idx == limit_idx) ? 0 : ++idx;
	}
};

#endif