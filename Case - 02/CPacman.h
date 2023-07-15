#pragma once
#ifndef __CPACMAN_H__
#define __CPACMAN_H__

#include "CEntidad.h"

class CPacman : public CEntidad {

public:
	CPacman(int x, int y)
		: CEntidad(x, y), speed(12) {

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

private:
	int speed;

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