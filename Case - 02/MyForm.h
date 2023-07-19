#pragma once

#include "CBitmap.h"
#include "CControl.h"

namespace PACMAN {

	using namespace System;
	using namespace System::Windows::Forms;
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
		MyForm(void) {
			InitializeComponent();
			InitializeBitmaps();
			InitializeBufferedGraphics();

			control = new CControl(gr);
		}

	protected:
		~MyForm() {

			if (components) {
				delete components;
			}

			delete control;
		}
	private:
		System::Windows::Forms::Timer^ clock;
		System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->clock = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// clock
			// 
			this->clock->Tick += gcnew System::EventHandler(this, &MyForm::clock_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(684, 361);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
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
		MemoryStream^ pacman = urlConvertedToImage("https://raw.githubusercontent.com/GonzaloQuedena/Algorithms-for-Animation/main/Sprites/pacman.png");
		bitmaps->add_bitmap(gcnew CBitmap("pacman", pacman));

		MemoryStream^ fantasma = urlConvertedToImage("https://raw.githubusercontent.com/GonzaloQuedena/Algorithms-for-Animation/main/Sprites/ghosts.png");
		bitmaps->add_bitmap(gcnew CBitmap("fantasma", fantasma));

		MemoryStream^ pacdot = urlConvertedToImage("https://raw.githubusercontent.com/GonzaloQuedena/Algorithms-for-Animation/main/Sprites/pacdot.png");
		bitmaps->add_bitmap(gcnew CBitmap("pacdot", pacdot));

		MemoryStream^ bono = urlConvertedToImage("https://raw.githubusercontent.com/GonzaloQuedena/Algorithms-for-Animation/main/Sprites/pacman-bonus.png");
		bitmaps->add_bitmap(gcnew CBitmap("bono", bono));
	}
	private: void PintarBackground() {
		//pintando fondo de formulario.
		bf->Graphics->Clear(Color::WhiteSmoke);
	}
	private: void ProcesarJuego() {
		//pintando fondo.
		PintarBackground();

		//ejecutando proceso del juego.
		control->procesarJuego(bf->Graphics, bitmaps);

		//renderizando procesos.
		bf->Render(gr);
	}
	private: void MoverPacman(Keys e) {

		switch (e) {

		case Keys::W:
		case Keys::Up:
			control->moverPersona('W');
			break;

		case Keys::S:
		case Keys::Down:
			control->moverPersona('S');
			break;

		case Keys::A:
		case Keys::Left:
			control->moverPersona('A');
			break;

		case Keys::D:
		case Keys::Right:
			control->moverPersona('D');
			break;

		}
	}
		   //eventos.
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		clock->Interval = 60;
		clock->Enabled = true;
	}
	private: System::Void clock_Tick(System::Object^ sender, System::EventArgs^ e) {
		ProcesarJuego();
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		MoverPacman(e->KeyCode);
	}
	};
}
