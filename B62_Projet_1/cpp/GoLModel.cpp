#include "../h/GoLModel.h"
#include "../h/Space.h"
#include "../h/GoLNeighborhood.h"
#include "../h/GoLRule.h"
#include "../h/RLEReader.h"

//#include <algorithm>
#include <utility>
#include <vector>
#include <filesystem>

namespace fs = std::experimental::filesystem;

using std::swap;

GoLModel::GoLModel()
	:mIsLooping{true},
	mRLEReader{RLEReader()},
	mLastRandom{ 0.15 },
	mRLEFileFound{false}
{
	setRLEFilePath();
	setInterestingRules();
	initiateRule();
};

GoLModel::~GoLModel() {};

void GoLModel::initiateRule() {
	std::vector<size_t> born{ 3 };
	std::vector<size_t> survive{ 2,3 };
	std::vector<size_t> die{ 2,3 };

	addRule(born, survive, die, mRules);

	createRandomRules();
}

void GoLModel::createRandomRules() {
	clearRules(1);
	for (size_t i{}; i < nbStates; ++i) {
		Rule rule(2, nbStates);
		mRules.push_back(rule);
	}
}

void GoLModel::clearRules(size_t start) {
	for (size_t i{ start }; i < mRules.size(); ++i) {
		mRules.erase(mRules.begin() + i);
	}

}
void GoLModel::setRLEFilePath() {
	//fs::create_directories("RLE");
	try
	{
		for (const auto & file : fs::directory_iterator(mRLEPath)) {
			pathList.push_back(file.path().string());
		}
		currentPath = 0;
		totalPathNumber = pathList.size()-1;
	}
	catch (const std::exception& e)
	{
		//Pour afficher que les fichiers ont pas bien loader
		e.what();
	}

}

void GoLModel::setInterestingRules() {
	std::vector<size_t> born{};
	std::vector<size_t> survive{};
	std::vector<size_t> die{};

	born = { 2 };
	survive = { 2,3 };
	die = { 3 };
	addRule(born, survive, die, mintestingRules);

	born = { 3,6 };
	survive = { 2,3 };
	die = { 3 };
	addRule(born, survive, die, mintestingRules);

	born = { 3,6,7,8 };
	survive = { 3,4,6,7,8 };
	die = { 3 };
	addRule(born, survive, die, mintestingRules);

	//Règle de notre CRU
	born = { 6,8 };
	survive = { 4,2,1 };
	die = { 3 };
	addRule(born, survive, die, mintestingRules);
}

void GoLModel::addRule(std::vector<size_t> born, std::vector<size_t> survive, std::vector<size_t> die, std::vector<Rule> & container){
	Rule rule(born, survive, die);
	container.push_back(rule);
};

void GoLModel::calcul() {
	calculateNext();
	swapCurrent();

}

void GoLModel::calculateNext() {
	space_t & curr = mCurrent.getSpace();
	space_t & next = mNext.getSpace();

	size_t width = mCurrent.width();
	size_t height = mCurrent.height();

	for (size_t y{}; y < height; y++) {
		for (size_t x{}; x < width; x++){
			next[x][y].setDie();

			//GoLNeighborhood & neighborhood =  mCurrent.getNeighborhood(mIsLooping, x, y);
			GoLNeighborhood neighborhood(curr, mIsLooping, x, y);
			std::vector<size_t> & occ = neighborhood.getOccurence(nbStates);
			
			for (char v{ 1 }; v < (char)occ.size(); v++) {
				if(curr[x][y].value()==0){
					if(mRules[v-1].canBorn(occ[v])){
						next[x][y].setAlive(v);
						//break;
					}
				}else{
					if (mRules[v-1].canSurvive(occ[v]) && !mRules[v - 1].willDie(v, occ)) {
						next[x][y].setAlive(curr[x][y].value());
						//break;
					}
				}
			}
		}
	}
};


void GoLModel::swapCurrent() {
	space_t & curr = mCurrent.getSpace();
	space_t & next = mNext.getSpace();
	std::swap(curr,next);
	//std::copy(std::begin(next),std::end(next),std::begin(curr));
}

void GoLModel::displayCurrent(Space current) {
};

void GoLModel::generateFromRandom(double probability,bool regen) {
	mLastRandom = probability;
	if (regen) {
		createRandomRules();
	}
	mCurrent.randomize(probability,1,nbStates-1);
};

void GoLModel::generateFromPreviousRLE() {
	if (currentPath == 0) {
		currentPath = totalPathNumber;
	}
	else {
		currentPath -= 1;
	}
	generateFromCurrentRLE();
};

void GoLModel::generateFromCurrentRLE() {
	Space space;
	mCurrent = space;
	if (pathList.size() > 0) {
		mRLEFileFound = mRLEReader.read(pathList.at(currentPath), mCurrent, mRules);
	}
	if (!mRLEFileFound) {
		generateFromRandom(mLastRandom);
	}
};

void GoLModel::generateFromNextRLE() {
	if (currentPath == totalPathNumber) {
		currentPath = 0;
	}
	else {
		currentPath += 1;
	}
	generateFromCurrentRLE();
};


void GoLModel::toggleBorder() {

	mIsLooping = !mIsLooping;
};

Space & GoLModel::getCurrent()
{
	return mCurrent;
};

void GoLModel::goNextRule() {
	++mCurrInteres;
	if (mCurrInteres >= mintestingRules.size()) {
		mCurrInteres = 0;
	}
	Rule nextInteres = mintestingRules[mCurrInteres];
	mRules[0] = nextInteres;

}
void GoLModel::addState()
{
	if (nbStates < 7) {
		nbStates++;
		Rule rule(2, nbStates);
		mRules.push_back(rule);
		regen();
	}
}

void GoLModel::removeState()
{
	if (nbStates > 2) {
		nbStates--;
		regen();
	}
}

void GoLModel::regen()
{
	generateFromRandom(mLastRandom,false);
}

size_t GoLModel::getNbStates(){
	return nbStates;
}


