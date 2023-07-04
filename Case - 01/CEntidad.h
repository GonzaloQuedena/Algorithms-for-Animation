#pragma once
#ifndef __CENTIDAD_H__
#define __CENTIDAD_H__

//librería a usar.
#include<string>

//propiedades de namespaces a usar.
using std::string;
using System::Drawing::Bitmap;
using System::Drawing::Pen;
using System::Drawing::Color;
using System::Drawing::Graphics;
using System::Drawing::Rectangle;;
using System::Drawing::GraphicsUnit;

//implementación de clase "CEntidad" (clase padre).
class CEntidad {

public:
	//constructor de CEntidad.
	CEntidad(int x, int y)
		//inicializando atributos.
		: x(x), y(y), zoom(1.0f), entidad("") {
		dx = dy = width = height = idx = idy = limit_idx = 0;
	}
	virtual void pintar(Graphics^ gr, Bitmap^ bmp) {
		//obteniendo pieza a pintar.
		Rectangle pieza = Rectangle(idx * width, idy * height, width, height);
		//pintando pieza seleccionada en un area especificada.
		gr->DrawImage(bmp, area(), pieza, GraphicsUnit::Pixel);

		//actualizando imagen (animación).
		actualizarIMG();
	}
	virtual void mover(Graphics^) = 0;

	Rectangle area() {
		//obteniendo rectangulo que circunscribe a la entidad.
		return Rectangle(x, y, width * zoom, height * zoom);
	}
	virtual Rectangle perfect_area() = 0;

	//métodos de acceso.
	string getEntidad() const {
		return entidad;
	}
	int getDx() const {
		return dx;
	}
	void setDx(int arg) {
		dx = arg;
	}

protected:
	//atributos de clase.
	int x, y;				  //para coordenadas de entidad.
	int dx, dy;				  //para camb. de coordenadas de entidad.
	int width, height;        //para dim. de entidad.

	int idx, idy, limit_idx;  //para camb. de animación de entidad.      

	float zoom;               //para camb. tamanio de img.
	string entidad;           //para indicar tipo de entidad.

	
	virtual void actualizarIMG() {
		//actualizando ciclo de animación.
		idx = (idx == limit_idx) ? 0 : ++idx;
	}
};

#endif