#include "EcaController.h"


#include "ConsoleUtil.h"
#include <limits>
#include <algorithm>

std::string EcaController::sWelcomeText(
R"-(


ACE
Logiciel de simulation d'un automate cellulaire elementaire



-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
Actions disponibles pendant le deroulement du programme :
	- (P)                   quitter
	- (1-2-3-4-5)           recule de 100 - 10 - 5 - 2 - 1
	- (barre d'espacement)  reprise de la meme regle
	- (6-7-8-9-0)           avance de 1 - 2 - 5 - 10 - 100
	- (N-M)                 recule-avance a la prochaine regle d'interet
	- (Z-X-C-V)             centre 1/2 - 1/4 - 1/8 - 1/16
	- (A-S-D)               aleatoire 25%  - 50% - 75%
	- (Q-W)                 damier 0 - 1
	- (...)                 avance a la prochaine regle
-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-'-



appuyer sur une touche ...)-");
std::string EcaController::sSpaceSizeText("Veuillez entrer la taille de l'espace");
std::string EcaController::sTimeSizeText("Veuillez entrer la taille du temps");
std::string EcaController::sIsQuittingText(
R"-(
Desirez-vous quitter?
   (O)ui
   ... toute autre touche pour poursuivre)-");

std::string EcaController::sQuitInterruptionText(
R"-(
Fermeture interrompue.


Appuyez sur une touche pour poursuivre...)-");

char EcaController::sQuitConfirmationCharacter{ 'O' };



EcaController::EcaController(EcaModel * model, EcaView * view)
	: mModel{ model }, mView{ view }, mGenerateAction(0, 9), mModelAction()
{
	if (!model || !view) {
		throw std::invalid_argument("EcaController::EcaController : model and view must be valid.");
	}

	mGenerateAction.setAction((int)GenerationMode::Centered_1_2,		[](EcaModel & model, EcaController & controller)-> void { model.generateFromCentered(2); });
	mGenerateAction.setAction((int)GenerationMode::Centered_1_4,		[](EcaModel & model, EcaController & controller)-> void { model.generateFromCentered(4); });
	mGenerateAction.setAction((int)GenerationMode::Centered_1_8,		[](EcaModel & model, EcaController & controller)-> void { model.generateFromCentered(8); });
	mGenerateAction.setAction((int)GenerationMode::Centered_1_16,		[](EcaModel & model, EcaController & controller)-> void { model.generateFromCentered(16); });
	mGenerateAction.setAction((int)GenerationMode::Random25,			[](EcaModel & model, EcaController & controller)-> void { model.generateFromRandom(0.25); });
	mGenerateAction.setAction((int)GenerationMode::Random50,			[](EcaModel & model, EcaController & controller)-> void { model.generateFromRandom(0.50); });
	mGenerateAction.setAction((int)GenerationMode::Random75,			[](EcaModel & model, EcaController & controller)-> void { model.generateFromRandom(0.75); });
	mGenerateAction.setAction((int)GenerationMode::Checked0,			[](EcaModel & model, EcaController & controller)-> void { model.generateFromChecked(State(false)); });
	mGenerateAction.setAction((int)GenerationMode::Checked1,			[](EcaModel & model, EcaController & controller)-> void { model.generateFromChecked(State(true)); });
	mGenerateAction.setDefaultAction((int)GenerationMode::Random50);

	mModelAction.setAction((int)KeyBinding::Action_Quit,				[](EcaModel & model, EcaController & controller)-> void { controller.quit(); });
	mModelAction.setAction((int)KeyBinding::Action_Prev100,				[](EcaModel & model, EcaController & controller)-> void { model.previousRule(100);										controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Prev10,				[](EcaModel & model, EcaController & controller)-> void { model.previousRule(10);										controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Prev5,				[](EcaModel & model, EcaController & controller)-> void { model.previousRule(5);										controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Prev2,				[](EcaModel & model, EcaController & controller)-> void { model.previousRule(2);										controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Prev1,				[](EcaModel & model, EcaController & controller)-> void { model.previousRule(1);										controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Same,				[](EcaModel & model, EcaController & controller)-> void { 																controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Next_1,				[](EcaModel & model, EcaController & controller)-> void { model.nextRule(1);											controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Next_2,				[](EcaModel & model, EcaController & controller)-> void { model.nextRule(2); 											controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Next_5,				[](EcaModel & model, EcaController & controller)-> void { model.nextRule(5); 											controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Next_10,				[](EcaModel & model, EcaController & controller)-> void { model.nextRule(10); 											controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_Next_100,			[](EcaModel & model, EcaController & controller)-> void { model.nextRule(100); 											controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_PrevNotable,			[](EcaModel & model, EcaController & controller)-> void { model.prevNotableRule(); 										controller.generate(); });
	mModelAction.setAction((int)KeyBinding::Action_NextNotable,			[](EcaModel & model, EcaController & controller)-> void { model.nextNotableRule(); 										controller.generate(); });
	mModelAction.setAction((int)KeyBinding::GenMode_Centered1_2,		[](EcaModel & model, EcaController & controller)-> void { controller.mGenerationMode = GenerationMode::Centered_1_2;	controller.generate(); });
	mModelAction.setAction((int)KeyBinding::GenMode_Centered1_4,		[](EcaModel & model, EcaController & controller)-> void { controller.mGenerationMode = GenerationMode::Centered_1_4;	controller.generate(); });
	mModelAction.setAction((int)KeyBinding::GenMode_Centered1_8,		[](EcaModel & model, EcaController & controller)-> void { controller.mGenerationMode = GenerationMode::Centered_1_8;	controller.generate(); });
	mModelAction.setAction((int)KeyBinding::GenMode_Centered1_16,		[](EcaModel & model, EcaController & controller)-> void { controller.mGenerationMode = GenerationMode::Centered_1_16;	controller.generate(); });
	mModelAction.setAction((int)KeyBinding::GenMode_Random25,			[](EcaModel & model, EcaController & controller)-> void { controller.mGenerationMode = GenerationMode::Random25;		controller.generate(); });
	mModelAction.setAction((int)KeyBinding::GenMode_Random50,			[](EcaModel & model, EcaController & controller)-> void { controller.mGenerationMode = GenerationMode::Random50;		controller.generate(); });
	mModelAction.setAction((int)KeyBinding::GenMode_Random75,			[](EcaModel & model, EcaController & controller)-> void { controller.mGenerationMode = GenerationMode::Random75;		controller.generate(); });
	mModelAction.setAction((int)KeyBinding::GenMode_Checked0,			[](EcaModel & model, EcaController & controller)-> void { controller.mGenerationMode = GenerationMode::Checked0;		controller.generate(); });
	mModelAction.setAction((int)KeyBinding::GenMode_Checked1,			[](EcaModel & model, EcaController & controller)-> void { controller.mGenerationMode = GenerationMode::Checked1;		controller.generate(); });
	mModelAction.setDefaultAction((int)KeyBinding::Action_Next_1);
}

void EcaController::start()
{
	showIntroduction();
	setOptions();
	generate();

	do {
		mModelAction.doActionFromKey(ConsoleUtil::getUpperChar(), *mModel, *this);
	} while (!mQuit);
}

void EcaController::showIntroduction()
{
	mView->show(sWelcomeText);
	ConsoleUtil::getUpperChar();
	ConsoleUtil::clearScreen();
}

void EcaController::setOptions()
{
	size_t spaceSize{ (size_t)ConsoleUtil::getInt(sSpaceSizeText, 16, 100, true) };
	size_t timeSize{ (size_t)ConsoleUtil::getInt(sTimeSizeText, 5, 50, true) };
	mModel->resize(spaceSize, timeSize);
	mModel->setRule(0);
}

void EcaController::generate()
{
	mGenerateAction.doActionFromKey((int)mGenerationMode, *mModel, *this);
	mView->show(*mModel);
}

void EcaController::quit()
{
	mView->show(sIsQuittingText, true);
	mQuit = ConsoleUtil::validateUpperChar(sQuitConfirmationCharacter);
	if (!mQuit) {
		mView->show(sQuitInterruptionText, true);
	}
}







