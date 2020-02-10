// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Projet 1
//
// Auteurs : Alexandre Gauthier, Hugo Turgeon-Nozaki, William Frazilien, Joey Dallaire
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Inclusion des librairies
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "../h/GoLController.h"
#include "../h/GoLModel.h"
#include <iostream>
#include "../Console/Console.h"
#include "../h/GoLView.h"
#include "../h/Space.h"

#include "../h/Space.h"

int main() {
	//GoLController controller();
	GoLView view;
	GoLController controller;

	try {
		controller.start();
	}
	catch (std::exception e) {

	}

	return 0;
}