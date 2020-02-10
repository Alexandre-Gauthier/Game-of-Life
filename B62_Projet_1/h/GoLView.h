#ifndef GOL_VIEW_H
#define GOL_VIEW_H
#include <String>
#include <vector>
#include "..\Console\ConsoleColor.h"
#include <string>

class Console;
class ConsoleWriter;
class ConsoleKeyReader;
class ConsoleColor;
class ConsoleImage;
class Space;

class GoLView
{
public:
	GoLView();
	~GoLView();

	void drawStates(Space  & space);
	void drawText(std::string text, int x, int y);
	void setUp();
	void toggleInactiveColor();
	void toggleActiveColor();


private:
	//Console mConsole;
	size_t const ConsoleWidth{ 200 }, ConsoleHeight{ 200 };
	int16_t FontWidth{ 4 }, FontHeight{ 4 };
	std::string const mTitle{ "GoL" };
	//wchar_t const mFont{ L"Consolas" };
	ConsoleWriter * mConsoleWriter;
	ConsoleKeyReader * mConsoleReader;
	ConsoleImage * mBackground, * mOutput; 
	
	size_t mIndexBG;
	size_t mIndexColor;
	ConsoleColor mActiveColor;
	std::vector<ConsoleColor> mBgColor;
	std::vector<ConsoleColor> mCharacterColor;
	
	//std::vector<std::vector<ConsoleImage>> &mSpace;
};



#endif // !GOL_VIEW_H
