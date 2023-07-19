#pragma once
#ifndef __CPACDOT_H__
#define __CPACDOT_H__

#include "CEntidad.h"

class CPacdot : public CEntidad {

public:
	CPacdot(int x, int y)
		: CEntidad(x, y) {

		width = 130;
		height = 117;

		entidad = "pacdot";

		zoom = 0.2f;
	}
};

#endif