#ifndef ECA_CONTROLLER_H
#define ECA_CONTROLLER_H


#include <array>
#include "EcaModel.h"
#include "EcaView.h"


#include "EcaActionKeyBinding.h"


class EcaController
{
public:
	EcaController(EcaModel * model = nullptr, EcaView * view = nullptr);
	~EcaController() = default;

	void start();

private:
	bool mQuit = false;
	EcaModel * mModel;
	EcaView * mView;

	enum class GenerationMode {
		Centered_1_2	= 0,
		Centered_1_4	= 1,
		Centered_1_8	= 2,
		Centered_1_16	= 3,
		Random25		= 4,
		Random50		= 5,
		Random75		= 6,
		Checked0		= 7,
		Checked1		= 8 
	};
	GenerationMode mGenerationMode = GenerationMode::Random50;
	EcaActionKeyBinding mGenerateAction;

	enum class KeyBinding : char {
		Action_Quit				= 'P',
		Action_Prev100			= '1',
		Action_Prev10			= '2',
		Action_Prev5			= '3',
		Action_Prev2			= '4',
		Action_Prev1			= '5',
		Action_Same				= ' ',
		Action_Next_1			= '6',
		Action_Next_2			= '7',
		Action_Next_5			= '8',
		Action_Next_10			= '9',
		Action_Next_100			= '0',
		Action_PrevNotable		= 'N',
		Action_NextNotable		= 'M',
		GenMode_Centered1_2		= 'Z', 
		GenMode_Centered1_4		= 'X',
		GenMode_Centered1_8		= 'C',
		GenMode_Centered1_16	= 'V',
		GenMode_Random25		= 'A',
		GenMode_Random50		= 'S',
		GenMode_Random75		= 'D',
		GenMode_Checked0		= 'Q',
		GenMode_Checked1		= 'W',
	};
	EcaActionKeyBinding mModelAction;
	
	void showIntroduction();
	void setOptions();
	void generate();
	void quit();

	static std::string sWelcomeText;
	static std::string sSpaceSizeText;
	static std::string sTimeSizeText;
	static std::string sIsQuittingText;
	static std::string sQuitInterruptionText;
	static char sQuitConfirmationCharacter;
};




#endif // ECA_CONTROLLER_H