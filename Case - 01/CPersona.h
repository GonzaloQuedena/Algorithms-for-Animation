#pragma once
#ifndef __CPERSONA_H__
#define __CPERSONA_H__

#include"CEntidad.h"

//implementación de clase "CPersona" (clase hija).
class CPersona : public CEntidad {

public:
	//constructor de CPersona.
	CPersona(int x, int y)
		//inicializando atributos propios y heredados.
		: CEntidad(x, y), speed(10), vidas(3), puntos(0) {
		//inicializando atributos heredados.
		idy = 2;
		limit_idx = 3;
		dx = dy = idx = 0;
		width = height = 64;

		zoom = 0.9f;
	}
	void mover(Graphics^ gr) {
		//eva. que exista mov. vertical siempre que se encuentre dentro del FORM. 
		if (y + dy > 10 && y + area().Height + dy < gr->VisibleClipBounds.Height) {
			y += dy;
		}
	}
	void moverPersona(char key) {

		//camb. dirección de entidad según valor de "key".
		switch (key) {

		case 'W':  //mov. arriba.
			dy = -speed;
			dx = 0;
			break;

		case 'S':  //mov. abajo.
			dy = speed;
			dx = 0;
			break;

		case 'N':  //NOT mov.
			dx = dy = 0;
			break;

		}
	}
	Rectangle perfect_area() {
		//obteniendo rectangulo que circunscribe de forma perfecta a la entidad.
		return Rectangle(x + 10, y + 14, area().Width - 25, area().Height - 18);
	}
	void procesarPintar(Graphics^ gr, Bitmap^ bmp) {
		//pintando estadísticas de entidad.
		pintarStats(gr);
		//pintando entidad.
		pintar(gr, bmp);
	}
	void decrementarVidas(int arg) {
		vidas += arg;
	}
	void incrementarPuntos(int arg) {
		puntos += arg;
	}
	//métodos de acceso.
	int getVidas() const {
		return vidas;
	}
	int getPuntos() const {
		return puntos;
	}

private:
	//atributos de clase CPersona.
	int vidas;   //vidas de entidad.
	int speed;   //velocidad de mov. de entidad.
	int puntos;  //puntos de entidad.

	void actualizarIMG() {
		//actualizando ciclo de animación siempre que existe mov.
		if (dy != 0) {
			idx = (idx == limit_idx) ? 0 : ++idx;
		}
	}
	void pintarStats(Graphics^ gr) {
		//mostrando valor de vidas.
		gr->DrawString("VIDAS: " + vidas.ToString(), gcnew System::Drawing::Font("Times New Roman", 14),
			gcnew System::Drawing::SolidBrush(Color::Black), 10, 10);
		//mostrando valor de puntos.
		gr->DrawString("PUNTOS: " + puntos.ToString(), gcnew System::Drawing::Font("Times New Roman", 14),
			gcnew System::Drawing::SolidBrush(Color::Black), 120, 10);
	}
};

#endif