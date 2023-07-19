#pragma once
#ifndef __CBONO_H__
#define __CBONO_H__

#include "CEntidad.h"

class CBono : public CEntidad {

public:
	CBono(int x, int y)
		: CEntidad(x, y) {	

		width = 60;
		height = 75;

		entidad = "bono";

		zoom = 0.5f;

		limit_idx = 3;
	}

	void actualizarBono(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

#endif