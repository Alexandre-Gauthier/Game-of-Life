#include "..\h\GoLView.h"
#include "..\Console\ConsoleKeyReader.h"
#include "..\Console\ConsoleWriter.h"
#include "..\Console\Console.h"
#include "..\Console\ConsoleContext.h"
#include "..\Console\ConsoleKeyFilterModifiers.h"
#include "..\Console\ConsoleKeyFilterUp.h"
#include "..\Console\ConsoleImage.h"
#include "..\Console\ConsoleColor.h"
#include "..\h\Space.h"
#include "..\h\State.h"
#include <string>

GoLView::GoLView() :
	mConsoleWriter{ nullptr },
	mConsoleReader{ nullptr },
	mBackground{ nullptr },
	mOutput{ nullptr },
	mBgColor{ ConsoleColor::black, ConsoleColor::red, ConsoleColor::green, ConsoleColor::blue, ConsoleColor::yellow, ConsoleColor::magenta, ConsoleColor::cyan, ConsoleColor::white },
	mCharacterColor{ ConsoleColor::Yellow,ConsoleColor::Red,ConsoleColor::Blue,ConsoleColor::Green,ConsoleColor::Magenta,ConsoleColor::Cyan }
{
	ConsoleContext context(ConsoleWidth, ConsoleHeight, mTitle, FontWidth, FontHeight, L"Consolas");
	Console::defineContext(context);

	Console::getInstance().keyReader().installFilter(new ConsoleKeyFilterModifiers);
	Console::getInstance().keyReader().installFilter(new ConsoleKeyFilterUp);
	mConsoleReader = &Console::getInstance().keyReader();
	mConsoleWriter = &Console::getInstance().writer();

	mBackground = &mConsoleWriter->createImage("background");
	mBackground->fill(' ', mBgColor[mIndexBG]);

	mOutput = &mConsoleWriter->createImage("output");
	mActiveColor = mCharacterColor[0];
}

GoLView::~GoLView()
{
}

void GoLView::setUp() {
}

void GoLView::drawStates(Space & space) {
	*mOutput = *mBackground;
	int row{}, col{};
	std::vector<std::vector<State>> & space2= space.getSpace();
	for (std::vector<State> & dimension : space.getSpace())
	{
		for (State state : dimension) {
			switch (state.value())
			{
			case 1:
				mOutput->drawPoint(row, col, char(219), mActiveColor);
				break;
			case 2:
				mOutput->drawPoint(row, col, char(219), mCharacterColor[1]);
				break;
			case 3:
				mOutput->drawPoint(row, col, char(219), mCharacterColor[2]);
				break;
			case 4:
				mOutput->drawPoint(row, col, char(219), mCharacterColor[3]);
				break;
			case 5:
				mOutput->drawPoint(row, col, char(219), mCharacterColor[4]);
				break;
			case 6:
				mOutput->drawPoint(row, col, char(219), mCharacterColor[5]);
				break;
			default:
				break;
			}
			++col;
		}
		col = 0;
		++row;
	}
	mConsoleWriter->write(*mOutput);

}

void  GoLView::drawText(std::string text,int x,int y) {
	ConsoleContext context(ConsoleWidth, ConsoleHeight, mTitle, 20, 20, L"Consolas");
	Console::defineContext(context);

	*mOutput = *mBackground;
	mOutput->drawText(x,y,text, mCharacterColor[0],true);
	mConsoleWriter->write(*mOutput);
}

void GoLView::toggleInactiveColor() {
	++mIndexBG;
	if (mIndexBG >= mBgColor.size()) {
		mIndexBG = 0;
	}
	mBackground->fill(' ', mBgColor[mIndexBG]);
}
void GoLView::toggleActiveColor()
{
	++mIndexColor;
	if (mIndexColor >= mCharacterColor.size()) {
		mIndexColor = 0;
	}
	mActiveColor = mCharacterColor[mIndexColor];
}

