#include "../h//GoLController.h"
#include "../Console/ConsoleKeyEvent.h"

#include "../Console/Console.h"
#include "../Console/ConsoleContext.h"
#include "../Console/ConsoleKeyFilterModifiers.h"
#include "../Console/ConsoleKeyFilterUp.h"

#include <conio.h>

std::string GoLController::sWelcomeText(
	R"-(


Game Of Life

-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
Actions disponibles pendant le deroulement du programme :
	- (Q)                   quitter la simulation
	- (1-2-3-4-5-6-7-8-9)   change la vitesse de simulation
	- (barre d'espacement)  pause/reprend la simulation

	- (R)					Va à la règle intéressante suivante (pour la première espèce seulement)
	- (A-S-D-F-G-H)			Génère le monde aléatoirement selon des probabilités différentes
	- (*)								
	- (+)					Génère le monde avec un espèce de plus
	- (-)					Génère le monde avec un espèce de moins

	- (Z)					Génère le monde selon le fichier RLE précédent (1 espèce)
	- (X)					Génère le monde selon le fichier RLE actuel (1 espèce)
	- (C)					Génère le monde selon le fichier RLE suivant (1 espèce)

	- (B)					Active/Désactive les bordures cycliques
	- (P)					Change la couleur des cellules actives (1 espèce)
	- (O)					Change la couleur des cellules inactives (1 espèce)
-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-



appuyer sur une touche ...)-");


GoLController::GoLController()
	:mQuit{ false }, mPause{ false }, mSpeed {1}, mReader{ Console::getInstance().keyReader() }
{
	mGenerateAction.setAction((int)GenerationMode::PrevRLE,					[](GoLModel & model, GoLController & controller)-> void {model.generateFromPreviousRLE(); });
	mGenerateAction.setAction((int)GenerationMode::CurrentRLE,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromCurrentRLE(); });
	mGenerateAction.setAction((int)GenerationMode::NextRLE,					[](GoLModel & model, GoLController & controller)-> void {model.generateFromNextRLE(); });

	mModelAction.setAction((int)KeyBinding::Action_Quit,					[](GoLModel & model, GoLController & controller)-> void {controller.setQuit(); });
	mModelAction.setAction((int)KeyBinding::Action_QuitS,					[](GoLModel & model, GoLController & controller)-> void {controller.setQuit(); });
	mModelAction.setAction((int)KeyBinding::Action_Pause,					[](GoLModel & model, GoLController & controller)-> void {controller.setPause(); });
	mModelAction.setAction((int)KeyBinding::Action_BorderM,					[](GoLModel & model, GoLController & controller)-> void {model.toggleBorder();});
	mModelAction.setAction((int)KeyBinding::Action_BorderS,					[](GoLModel & model, GoLController & controller)-> void {model.toggleBorder();});
	mModelAction.setAction((int)KeyBinding::Action_ChangeColorActiveM,		[](GoLModel & model, GoLController & controller)-> void {controller.toggleActiveColor();});
	mModelAction.setAction((int)KeyBinding::Action_ChangeColorActiveS,		[](GoLModel & model, GoLController & controller)-> void {controller.toggleActiveColor();});
	mModelAction.setAction((int)KeyBinding::Action_ChangeColorInactiveM,	[](GoLModel & model, GoLController & controller)-> void {controller.toggleInactiveColor();});
	mModelAction.setAction((int)KeyBinding::Action_ChangeColorInactiveS,	[](GoLModel & model, GoLController & controller)-> void {controller.toggleInactiveColor();});
	mModelAction.setAction((int)KeyBinding::Action_SpeedTime1,				[](GoLModel & model, GoLController & controller)-> void {controller.setTickSpeed(1);});
	mModelAction.setAction((int)KeyBinding::Action_SpeedTime2,				[](GoLModel & model, GoLController & controller)-> void {controller.setTickSpeed(2); });
	mModelAction.setAction((int)KeyBinding::Action_SpeedTime3,				[](GoLModel & model, GoLController & controller)-> void {controller.setTickSpeed(3); });
	mModelAction.setAction((int)KeyBinding::Action_SpeedTime4,				[](GoLModel & model, GoLController & controller)-> void {controller.setTickSpeed(4); });
	mModelAction.setAction((int)KeyBinding::Action_SpeedTime5,				[](GoLModel & model, GoLController & controller)-> void {controller.setTickSpeed(5); });
	mModelAction.setAction((int)KeyBinding::Action_SpeedTime6,				[](GoLModel & model, GoLController & controller)-> void {controller.setTickSpeed(6); });
	mModelAction.setAction((int)KeyBinding::Action_SpeedTime7,				[](GoLModel & model, GoLController & controller)-> void {controller.setTickSpeed(7); });
	mModelAction.setAction((int)KeyBinding::Action_SpeedTime8,				[](GoLModel & model, GoLController & controller)-> void {controller.setTickSpeed(8); });
	mModelAction.setAction((int)KeyBinding::Action_SpeedTime9,				[](GoLModel & model, GoLController & controller)-> void {controller.setTickSpeed(9); });
	
	mModelAction.setAction((int)KeyBinding::GenMode_Random1M,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.01);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random1S,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.01);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random5M,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.05);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random5S,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.05);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random10S,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.10);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random10S,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.10);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random15M,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.15);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random15S,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.15);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random25M,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.25);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random25S,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.25);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random50M,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.5);  });
	mModelAction.setAction((int)KeyBinding::GenMode_Random50S,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromRandom(0.5);  });
	
	mModelAction.setAction((int)KeyBinding::Action_NextRuleM,				[](GoLModel & model, GoLController & controller)-> void {model.goNextRule();  });
	mModelAction.setAction((int)KeyBinding::Action_NextRuleS,				[](GoLModel & model, GoLController & controller)-> void {model.goNextRule();  });
	
	mModelAction.setAction((int)KeyBinding::GenMode_Previous_RLEM,			[](GoLModel & model, GoLController & controller)-> void {model.generateFromPreviousRLE();  });
	mModelAction.setAction((int)KeyBinding::GenMode_Previous_RLES,			[](GoLModel & model, GoLController & controller)-> void {model.generateFromPreviousRLE();  });
	mModelAction.setAction((int)KeyBinding::GenMode_Current_RLEM,			[](GoLModel & model, GoLController & controller)-> void {model.generateFromCurrentRLE();  });
	mModelAction.setAction((int)KeyBinding::GenMode_Current_RLES,			[](GoLModel & model, GoLController & controller)-> void {model.generateFromCurrentRLE();  });
	mModelAction.setAction((int)KeyBinding::GenMode_Next_RLEM,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromNextRLE();  });
	mModelAction.setAction((int)KeyBinding::GenMode_Next_RLES,				[](GoLModel & model, GoLController & controller)-> void {model.generateFromNextRLE();  });
	
	mModelAction.setAction((int)KeyBinding::GenMode_AddState,				[](GoLModel & model, GoLController & controller)-> void {model.addState();  });
	mModelAction.setAction((int)KeyBinding::GenMode_RemoveState,			[](GoLModel & model, GoLController & controller)-> void {model.removeState();  });
	
	mModelAction.setAction((int)KeyBinding::GenMode_RegenM,					[](GoLModel & model, GoLController & controller)-> void {model.regen();  });
	mModelAction.setAction((int)KeyBinding::GenMode_RegenS,					[](GoLModel & model, GoLController & controller)-> void {model.regen();  });
}

void GoLController::start()
{
	// ShowIntroduction
	// SetOption
	// Generate
	//showIntroduction();
	generate();
	tick();
}

int GoLController::tick()
{
	// Get Key Action
	ConsoleKeyReader::KeyEvents events;
	mView.setUp();
	//vitesse calcul x fois avant dafficher
	//boucle pas de time out juste une big boucle while
	while (!mQuit) {

		if (!mPause) {
			for (int i{ 0 }; i < mSpeed; ++i) {
				mModel.calcul();
			}
			//AFFICHE
			mView.drawStates(mModel.getCurrent());
		}
		mReader.read(events);
		if (events.size() > 0) {
			mModelAction.doActionFromKey(events.front().keyA(), mModel, *this);
		}
	}
	quit();
	return 0;
}



void GoLController::showIntroduction()
{
	ConsoleKeyReader::KeyEvents events;
	mView.drawText(GoLController::sWelcomeText, 10, 10);
	_getch();
}

// Pour choisir la méthode d'initialisation - getInput
void GoLController::setOptions()
{
}

// Pour générer une simulation selon l'input
void GoLController::generate()
{
	//mModel.generateFromRandom(0.05);
	mModel.generateFromCurrentRLE();
}

void GoLController::setPause()
{
	mPause = !mPause;
}

void GoLController::setQuit()
{
	mQuit = true;
	mPause = true;
}

void GoLController::quit()
{

}

void GoLController::setTickSpeed(int speed) {
	mSpeed = speed;
}

size_t GoLController::getNbStates() {
	return mModel.getNbStates();
}

void GoLController::toggleInactiveColor() {
	mView.toggleInactiveColor();
};

void GoLController::toggleActiveColor() {
	mView.toggleActiveColor();
};
