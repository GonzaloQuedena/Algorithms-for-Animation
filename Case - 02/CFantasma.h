#pragma once
#ifndef __CFANTASMA_H__
#define __CFANTASMA_H__

#include "CEntidad.h"

string ghost_color[] = { "red", "orange", "pink", "lightblue", "purple" };

class CFantasma : public CEntidad {

public:
	CFantasma(int x, int y, int dx, int dy)
		: CEntidad(x, y) {

		width = 47;
		height = 49;

		entidad = "fantasma";

		zoom = 0.7f;

		this->dx = dx;
		this->dy = dy;

		__asignarFantasma(ghost_color[nextInt(0, 4)]);
	}

private:
	int save_idx;

	void __actualizarIMG() {

		if (dx > 0)idy = 0;
		else if (dx < 0)idy = 2;
		else if (dy > 0)idy = 1;
		else if (dy < 0)idy = 3;


		//actualizando ciclo de animación.
		idx = (idx == limit_idx) ? save_idx : ++idx;
	}
	void __asignarFantasma(string ghost) {

		if (ghost._Equal("red")) {
			idx = save_idx = 0;
			limit_idx = 1;
		}
		else if (ghost._Equal("orange")) {
			idx = save_idx = 2;
			limit_idx = 3;
		}
		else if (ghost._Equal("pink")) {
			idx = save_idx = 4;
			limit_idx = 5;
		}
		else if (ghost._Equal("lightblue")) {
			idx = save_idx = 6;
			limit_idx = 7;
		}
		else if (ghost._Equal("purple")) {
			idx = save_idx = 8;
			limit_idx = 9;
		}
	}

};

#endif
