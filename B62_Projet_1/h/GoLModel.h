#ifndef GOL_MODEL
#define GOL_MODEL

#include "../h/Space.h"
#include "../h/GoLRule.h"
#include "../h/RLEReader.h"

#include <vector>
#include <string>

class RLEReader;

class GoLModel
{
public:
	GoLModel();
	~GoLModel();

	void addRule(std::vector<size_t> born, std::vector<size_t> survive, std::vector<size_t> die, std::vector<Rule> & container);
	void setInterestingRules();
	void calcul();
	void generateFromRandom(double probability, bool regen = true);
	void generateFromPreviousRLE();
	void generateFromCurrentRLE();
	void generateFromNextRLE();
	void toggleBorder();
	void goNextRule();
	void addState();
	void removeState();
	void regen();

	Space & getCurrent();
	size_t getNbStates();

private:		
	std::vector<Rule> mRules;

	Space mCurrent;
	Space mNext;

	bool mRLEFileFound;
	bool mIsLooping;
	double mLastRandom;

	RLEReader mRLEReader;
	size_t nbStates = 2;
	std::vector<Rule> mintestingRules;
	std::vector<std::string> pathList;
	int currentPath;
	int totalPathNumber;
	std::string mRLEPath{ "RLE" };

	size_t mCurrInteres; //Current Interesting Rule

	void setRLEFilePath();
	void initiateRule();
	void createRandomRules();
	void clearRules(size_t start);
	void calculateNext();
	void swapCurrent();
	void displayCurrent(Space current);
};
#endif