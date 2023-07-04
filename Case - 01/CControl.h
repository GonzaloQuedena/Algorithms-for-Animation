#pragma once
#ifndef __CCONTROL_H__
#define __CCONTROL_H__

#include<ctime>
#include<vector>

#include"CBitmap.h"
#include"CPersona.h"
#include"CEnemigo.h"

using std::vector;

//implementación de clase Control: maneja funcionamiento del juego.
class CControl {

public:
	//constructor de CControl.
	CControl(Graphics^ gr) {

		//almacenando dim. de formulario.
		ANCHO_P = gr->VisibleClipBounds.Width;
		ALTO_P = gr->VisibleClipBounds.Height;

		//ref. a instancia de vector "CEntidad*".
		vEntidad = new vector<CEntidad*>;

		//ref. a instancia de tipo "CPersona".
		persona = new CPersona(5, (ALTO_P / 2) - 64);

		//fact. de enemigos.
		aparecer_enemigo = time(0);
	}
	//destructor de CControl.
	~CControl() {
		for (CEntidad* _iter : *vEntidad) {
			delete _iter;
		}
		delete persona;
		delete vEntidad;
	}
	//métodos de clase PUBLICOS.
	void procesarJuego(Graphics^ gr, CBitmapV^ bitmaps) {  
		//evaluando TODAS las colisiones.
		colisionesTotales();
		//generando enemigos.
		generarEnemigoEnUnTiempo();
		
		//pintando TODAS las entidades.
		pintarEntidades(gr, bitmaps);
		//moviendo TODAS las entidades.
		moverEntidades(gr);
	}
	void moverPersona(char key) { 
		//movimiento de persona.
		persona->moverPersona(key);
	}
	bool ganarJuego() { 
		//eva. cuando se gana el juego.
		return (persona->getPuntos() >= 150);
	}
	bool perderJuego() { 
		//eva. cuando se pierde el juego.
		return (persona->getVidas() <= 0);
	}

private:
	//atributos de clase.
	short ANCHO_P, ALTO_P;       //para obtener dim. de consola.
	CPersona* persona;           //objeto para almacenar ref. a instancia.
	vector<CEntidad*>* vEntidad; //vector que almacena entidades.

	//para controlar tiempo de generación de enemigos.
	time_t aparecer_enemigo;

	//métodos de clase PRIVADOS.
	void moverEntidades(Graphics^ gr) {  
		//mov. de persona.
		persona->mover(gr);

		//mov. de entidades.
		for (CEntidad* _iter : *vEntidad) {  
			_iter->mover(gr);
		}
	}
	void pintarEntidades(Graphics^ gr, CBitmapV^ bitmaps) {  

		//obteniendo bitmaps para el pintado de entidades.
		Bitmap^ bmpPersona = bitmaps->buscarBitmap("persona");
		Bitmap^ bmpEnemigo = bitmaps->buscarBitmap("ash");

		//pintando persona.
		persona->procesarPintar(gr, bmpPersona);

		//pintando entidades con su bitmap respectivo.
		for (CEntidad* _iter : *vEntidad) {
			//eva. entidades que sean tipo "enemigo".
			if (_iter->getEntidad()._Equal("enemigo")) {
				_iter->pintar(gr, bmpEnemigo);
			}
		}
	}
	//generadores de entidades.
	void generarEnemigo() { 
		//var. para almacenar datos de entidad.
		int x, y, dx, con = 0;
		//mientras "con" sea 0, se repite.
		while (con == 0) {
		
			//almacenamos valores para el enemigo.
			x = ANCHO_P - 70;
			y = nextInt(30, ALTO_P - 80);
			dx = nextInt(4, 8);

			//generamos enemigo con los valores dados.
			CEnemigo* enemigo = new CEnemigo(x, y, -dx);
		
			//verificamos que el enemigo generado no aparezca encima de uno YA existente.
			if (!entidadColisionaCon("enemigo", enemigo->perfect_area())) {
				//en ese caso, lo agregamos al vector de Entidad.
				vEntidad->push_back(enemigo);
				//cambiamos estado de "con" a 1, indicando que ya se generó, por ende no se 
				//deberá volver a generar.
				con = 1;
			}

			//liberando memoria de ref. a la instancia generada de enemigo en caso "con" siga en 0.
			if (con == 0) {
				delete enemigo;
			}
		}
	}
	void generarEnemigoEnUnTiempo() { 

		//verificando que pase 4seg.
		if (difftime(time(0), aparecer_enemigo) >= 4) {
			//al pasar, generamos 4 enemigos.
			for (int i = 0; i < 4; ++i) {
				generarEnemigo();
			}
		
			//reiniciamos temporizador.
			aparecer_enemigo = time(0);
		}
	}
	//colisiones y verificaciones.
	void colisionesTotales() {
		//evalua colisión entre Persona/Enemigo.
		colisionPersonaEnemigo();
		//verifica dx de entidades para dar una acción.
		verificarDx();
	}
	void colisionPersonaEnemigo() { 
		//recorremos elementos del vector.
		for (int i = 0; i < vEntidad->size(); ++i) {
			//buscamos elemento de tipo "enemigo".
			if (vEntidad->at(i)->getEntidad()._Equal("enemigo")) {
				//obtenemos el elemento.
				CEnemigo* enemigo = (CEnemigo*)vEntidad->at(i);

				//evaluamos si existe colisión.
				if (enemigo->perfect_area().IntersectsWith(persona->perfect_area())) {
					//si se da la colisión, decrementamos vidas de persona.
					persona->decrementarVidas(-1);
					//re-establecemos "dx" de entidad "enemigo" en 0.
					enemigo->setDx(0);
				}
			}
		}
	}
	bool entidadColisionaCon(string entidad, Rectangle rec) { 
		//recorremos elementos del vector.
		for (CEntidad* _iter : *vEntidad) {
			//buscamos elemento según tipo requerido.
			if (_iter->getEntidad()._Equal(entidad)) {
				//verificamos si ese elemento se colisiona con un rec.
				//requerido.
				if (_iter->perfect_area().IntersectsWith(rec)) {

					//en caso se de colisión, retornamos true.
					return true;
				}
			}
		}

		//retornamos false, en caso no se haya encontrado nada.
		return false;
	}
	void verificarDx() { 
		for (int i = 0; i < vEntidad->size(); ++i) {
			//buscamos elemento según tipo requerido.
			if (vEntidad->at(i)->getDx() == 0 && vEntidad->at(i)->getEntidad()._Equal("enemigo")) {
				persona->incrementarPuntos(5);
			}
			if (vEntidad->at(i)->getDx() == 0) {
				//borramos entidad en pos. "i".
				borrarEntidad(i);
			}
		}
	}
	void borrarEntidad(int& pos) { 
		//borramos elemento de vector "vEntidad" en índice "pos".
		vEntidad->erase(vEntidad->begin() + pos--);
	}

	//útil.
	int nextInt(int min, int max) { 
		//generamos valor aleatorio entre "min-max".
		return min + rand() % ((max + 1) - min);
	}
};

#endif