#pragma once
#ifndef __CENEMIGO_H__
#define __CENEMIGO_H__

#include"CEntidad.h"

//implementación de clase "CEnemigo" (clase hija).
class CEnemigo : public CEntidad {

public:
	//constructor de CEnemigo.
	CEnemigo(int x, int y, int dx)
		//inicializando atributos heredados.
		: CEntidad(x, y) {
		//inicializando atributos heredados.
		idy = 1;

		width = 68;
		height = 72;
		zoom = 0.9f;
		limit_idx = 3;
		
		this->dx = dx;
		this->entidad = "enemigo";
	}
	void mover(Graphics^ gr) {
		//eva. el mov. horizontal a la izq. no pase el límite.
		if (x + dx < 0) {
			dx = 0;
		}

		x += dx;
	}
	Rectangle perfect_area() {
		//obteniendo rectangulo que circunscribe de forma perfecta a la entidad.
		return Rectangle(x + 5, y + 14, area().Width - 30, area().Height - 18);
	}
};

#endif