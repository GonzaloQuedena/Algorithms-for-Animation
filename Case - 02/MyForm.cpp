#include "MyForm.h"

using PACMAN::MyForm;
using PACMAN::Application;

int main() {
	srand(time(nullptr));
	Application::Run(gcnew MyForm);

	return 0;
}