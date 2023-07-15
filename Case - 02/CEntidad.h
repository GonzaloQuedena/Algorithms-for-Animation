#pragma once
#ifndef __CENTIDAD_H__
#define __CENTIDAD_H__

#include "Util.h"

class CEntidad {

public:
	//constructor de clase.
	CEntidad(int x, int y)
		: x(x), y(y), zoom(1.0f), visible(true) {

		dx = dy = width = height = idx = idy = limit_idx = 0;
	}

	//métodos de clase PUBLICOS.
	virtual void pintar(Graphics^ gr, Bitmap^ bmp) {

		Rectangle pieza = Rectangle(idx * width, idy * height, width, height);

		gr->DrawImage(bmp, area(), pieza, GraphicsUnit::Pixel);

		__actualizarIMG();
	}
	virtual void mover(Graphics^ gr) {

		if (x + dx < 0 || x + area().Width + dx > gr->VisibleClipBounds.Width) {
			dx *= -1;
		}
		if (y + dy < 0 || y + area().Height + dy > gr->VisibleClipBounds.Height) {
			dy *= -1;
		}

		x += dx;
		y += dy;
	}

	Rectangle area() {
		return Rectangle(x, y, width * zoom, height * zoom);
	}

	//métodos de acceso.
	string getEntidad() const {
		return entidad;
	}

protected:
	//atributos de clase.
	int x, y;
	int dx, dy;
	int width, height;

	int idx, idy, limit_idx;

	float zoom;

	bool visible;

	string entidad;

	//métodos de clase PRIVADOS.
	virtual void __actualizarIMG() {
		//actualizando ciclo de animación.
		idx = (idx == limit_idx) ? 0 : ++idx;
	}
};

#endif