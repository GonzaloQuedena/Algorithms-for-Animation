#pragma once
#ifndef __CBITMAP_H__
#define __CBITMAP_H__

//propiedades de namespaces a usar.
using System::Byte;
using System::String;
using System::Net::WebClient;
using System::Drawing::Bitmap;
using System::IO::MemoryStream;
using System::Collections::Generic::List;

//implementación de clase CBitmap.
ref class CBitmap {

public:
	//constructores de clase: SOBRECARGA.
	CBitmap(String^ name, MemoryStream^ address)
		: name(name) {

		bitmap = gcnew Bitmap(address);
	}
	CBitmap(String^ name, String^ address)
		: name(name->ToLower()) {

		bitmap = gcnew Bitmap(address);
	}
	//métodos de acceso.
	Bitmap^ getBitmap() {  //para obtener "Bitmap" de la entidad.
		return bitmap;
	}
	String^ getName() {  //para obtener "name" de la entidad.
		return name;
	}

private:
	//atributos de clase.
	Bitmap^ bitmap;  //almacena mapa de bits (img).
	String^ name;    //almacena nombre de la entidad.
};

//implementación de clase CBitmapV: almacena conjunto de elementos "CBitmap^".
ref class CBitmapV {

public:
	//constructor de clase.
	CBitmapV() {
		//ref. a instancia de una List<CBitmap^>.
		vBitmaps = gcnew List<CBitmap^>;
	}
	//métodos de clase.
	void add_bitmap(CBitmap^ bmp) {  //para agregar un elemento al conjunto.
		//agregando elemento al conjunto.
		vBitmaps->Add(bmp);
	}
	Bitmap^ searchBitmap(String^ name) {  //para obtener el "Bitmap^" deseado.

		//recorriendo lista de que almacena CBitmap.
		for (int i = 0; i < vBitmaps->Count; ++i) {
			//evaluando cada elemento hasta encontrar el deseado
			if (vBitmaps[i]->getName()->Equals(name)) {
				//al encontrarlo, obtenemos el cbitmap.
				Bitmap^ bmp = vBitmaps[i]->getBitmap();

				//retornamos el bitmap.
				return bmp;
			}
		}
	}

private:
	//atributos de clase.
	List<CBitmap^>^ vBitmaps;  //almacena conjunto de "CBitmap^".
};

//función para obtener datos de una img. cargada por url.
MemoryStream^ urlConvertedToImage(String^ url) {

	//crear cliente web.
	WebClient^ webClient = gcnew WebClient();
	//descargando datos de img del url.
	array<Byte>^ imageBytes = webClient->DownloadData(url);

	//retornando un flujo de memoria y cargando los datos de la img.  en el flujo
	return gcnew MemoryStream(imageBytes);
}

#endif