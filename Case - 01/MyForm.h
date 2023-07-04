#pragma once

#include"CControl.h"
#include "CBitmap.h"

namespace BITMAPTEST {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form {

	private:
		//graphics.
		Graphics^ gr;
		BufferedGraphics^ bf;
		BufferedGraphicsContext^ sp;

		//bitmaps.
		CBitmapV^ bitmaps;
		
		//controlador.
		CControl* control;
	public:
		//constructor de FORM.
		MyForm(void) {
			//inicializando componentes (form).
			InitializeComponent();
			//inicializando graphics.
			InitializeBufferedGraphics();
			//inicializando bitmaps.
			InitializeBitmaps();

			//creando ref. a instancia CControl.
			control = new CControl(gr);
		}

	protected:
		//destructor de FORM.
		~MyForm() {
			if (components) {
				delete components;
			}

			delete control;
		}
	private: 
		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Timer^ crono;
		System::Windows::Forms::Button^ btnSalir;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->crono = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnSalir = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// crono
			// 
			this->crono->Enabled = true;
			this->crono->Interval = 38;
			this->crono->Tick += gcnew System::EventHandler(this, &MyForm::crono_Tick);
			// 
			// btnSalir
			// 
			this->btnSalir->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnSalir->Enabled = false;
			this->btnSalir->Font = (gcnew System::Drawing::Font(L"MV Boli", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSalir->Location = System::Drawing::Point(182, 146);
			this->btnSalir->Name = L"btnSalir";
			this->btnSalir->Size = System::Drawing::Size(131, 44);
			this->btnSalir->TabIndex = 0;
			this->btnSalir->UseVisualStyleBackColor = true;
			this->btnSalir->Visible = false;
			this->btnSalir->Click += gcnew System::EventHandler(this, &MyForm::btnSalir_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(513, 349);
			this->Controls->Add(this->btnSalir);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion

		//métodos propios.
	private: void InitializeBufferedGraphics() { 
		gr = this->CreateGraphics();
		sp = BufferedGraphicsManager::Current;
		bf = sp->Allocate(gr, this->ClientRectangle);
	}
	private: void InitializeBitmaps() {  
		//generando ref. a instancia BitmapV.
		bitmaps = gcnew CBitmapV;

		//agregando bitmaps.
		MemoryStream^ persona = urlConvertedToImage("https://raw.githubusercontent.com/GonzaQued/Algorithms-for-Animation/main/Sprites/basic-person.png");
		bitmaps->add_bitmap(gcnew CBitmap("persona", persona));

		MemoryStream^ enemigo = urlConvertedToImage("https://raw.githubusercontent.com/GonzaQued/Algorithms-for-Animation/main/Sprites/ash.png");
		bitmaps->add_bitmap(gcnew CBitmap("ash", enemigo));
	}
	private: void PintarBackground() {
		//pintando fondo de formulario.
		bf->Graphics->Clear(Color::WhiteSmoke);
	}
	private: void MoverPersona(bool val, Keys e) {
		//eva. si "val" es true, indicamos SI movimiento.
		if (val) {

			switch (e) {

			case Keys::W:
			case Keys::Up:
				control->moverPersona('W');
				break;

			case Keys::S:
			case Keys::Down:
				control->moverPersona('S');
				break;

			}
		}
		//en caso "val" sea false, indicamos NO movimiento.
		else {
			control->moverPersona('N');
		}
	}
	private: void ActivarBotonSalir(String^ msg) {
		//activando boton.
		btnSalir->Enabled = true;
		btnSalir->Visible = true;
		//impriendo cadena.
		btnSalir->Text = msg;
	}
	private: void EjecutarResultado(String^ msg) {
		//obteniendo dim. de FORM.
		const int ANCHO_P = (int)gr->VisibleClipBounds.Width;
		const int ALTO_P = (int)gr->VisibleClipBounds.Height;
		//pintando fondo de FORM.
		PintarBackground();
		//desactivando timer.
		crono->Enabled = false;
		//activando boton.
		ActivarBotonSalir(msg);
	}
	private: void ResultadoJuego() {
		//eva. resultado de juego.
		if (control->ganarJuego()) {
			EjecutarResultado("GANASTE!");
		}
		if (control->perderJuego()) {
			EjecutarResultado("PERDISTE!");
		}
 	}
	private: void ProcesarJuego() {
		//pintando fondo.
		PintarBackground();
		//ejecutando proceso del juego.
		control->procesarJuego(bf->Graphics, bitmaps);
		//evaluando resultado del juego.
		ResultadoJuego();

		//renderizando procesos.
		bf->Render(gr);
	}

		//eventos FORM.
	private: System::Void crono_Tick(System::Object^ sender, System::EventArgs^ e) {
		ProcesarJuego();
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		MoverPersona(true, e->KeyCode);
	}
	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		MoverPersona(false, e->KeyCode);
	}
	private: System::Void btnSalir_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
    };
}
