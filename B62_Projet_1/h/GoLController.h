#ifndef GOL_CONTROLLER
#define GOL_CONTROLLER
#include "GoLActionKeyBinding.h"
#include "GoLModel.h"
#include "GoLView.h"
#include "../Console/Console.h"

class GoLController
{
public:
	GoLController();
	~GoLController() = default;
	void start();
	size_t getNbStates();
	void toggleInactiveColor();
	void toggleActiveColor();


private:
	bool mQuit;
	bool mPause;
	GoLModel mModel;
	GoLView mView;
	ConsoleKeyReader & mReader;

	enum class GenerationMode {
		PrevRLE = 0,
		CurrentRLE = 1,
		NextRLE = 2,
		Random1 = 3,
		Random5 = 4,
		Random10 = 5,
		Random15 = 6,
		Random25 = 7,
		Random50 = 8,
	};

	GenerationMode mGenerationMode{ GenerationMode::Random10 };
	GoLActionKeyBinding mGenerateAction;

	enum class KeyBinding : char {
		Action_Quit = 'Q',
		Action_QuitS = 'q',
		Action_SpeedTime1 = '1',
		Action_SpeedTime2 = '2',
		Action_SpeedTime3 = '3',
		Action_SpeedTime4 = '4',
		Action_SpeedTime5 = '5',
		Action_SpeedTime6 = '6',
		Action_SpeedTime7 = '7',
		Action_SpeedTime8 = '8',
		Action_SpeedTime9 = '9',
		Action_Pause = ' ',
		Action_NextRuleM = 'R',
		Action_NextRuleS = 'r',
		Action_BorderM = 'B',
		Action_BorderS = 'b',
		Action_ChangeColorActiveM = 'P',
		Action_ChangeColorActiveS = 'p',
		Action_ChangeColorInactiveM = 'O',
		Action_ChangeColorInactiveS = 'o',

		GenMode_Random1M = 'A',
		GenMode_Random1S = 'a',
		GenMode_Random5M = 'S',
		GenMode_Random5S = 's',
		GenMode_Random10M = 'D',
		GenMode_Random10S = 'd',
		GenMode_Random15M = 'F',
		GenMode_Random15S = 'f',
		GenMode_Random25M = 'G',
		GenMode_Random25S = 'g',
		GenMode_Random50M = 'H',
		GenMode_Random50S = 'h',

		GenMode_Previous_RLEM = 'Z',
		GenMode_Previous_RLES = 'z',
		GenMode_Current_RLEM = 'X',
		GenMode_Current_RLES = 'x',
		GenMode_Next_RLEM = 'C',
		GenMode_Next_RLES = 'c',

		GenMode_AddState = '+',
		GenMode_RemoveState = '-',
		GenMode_RegenM = 'V',
		GenMode_RegenS = 'v'
	};

	GoLActionKeyBinding mModelAction;

	int tick();
	int mSpeed;
	void showIntroduction();
	void setOptions();
	void generate();
	void setPause();
	void setTickSpeed(int speed);
	void setQuit();
	void quit();

	static std::string sWelcomeText;
};



#endif