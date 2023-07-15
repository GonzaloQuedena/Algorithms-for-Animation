#pragma once
#ifndef __UTIL_H__
#define __UTIL_H__

#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using std::string;
using std::vector;
using System::Drawing::Bitmap;
using System::Drawing::Graphics;
using System::Drawing::Rectangle;
using System::Drawing::GraphicsUnit;

//funcion util.
int nextInt(int min, int max) {
	//generamos valor aleatorio entre "min-max".
	return min + rand() % ((max + 1) - min);
}

#endif