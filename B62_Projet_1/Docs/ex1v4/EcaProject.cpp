// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Exercice 1 - version 4
// 
// Exercice incrémental d'approfondissement du langage C++
// 
// Auteur : CVM
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Inclusion des librairies
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include "EcaController.h"
#include "EcaModel.h"
#include "EcaView.h"
#include "ConsoleUtil.h"
#include <iostream>


using namespace std;

int main()
{
	EcaModel model;
	EcaView view;
	EcaController controller(&model, &view);

	
	// Gestion trivial des exceptions.
	try {
		controller.start();
	} catch (std::exception e) {
		ConsoleUtil::clearScreen();
		std::cout	<< "Ce programme a rencontre une erreur et doit terminer. L'erreur est :" << std::endl
					<< e.what() << std::endl << std::endl << std::endl << std::endl
					<< "Appuyer sur une touche pour continuer...";
		ConsoleUtil::getUpperChar();
	} catch (...) {
		ConsoleUtil::clearScreen();
		std::cout	<< "Ce programme a rencontre une erreur inconnue et doit terminer." << std::endl
					<< std::endl << std::endl << std::endl << std::endl
					<< "Appuyer sur une touche pour continuer...";
		ConsoleUtil::getUpperChar();
	}

	return 0;
}

