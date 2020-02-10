#include "..\h\GoLRule.h"
#include <algorithm>
#include "../h/RandomUtil.h"

Rule::Rule(vInt_t born, vInt_t survive, vInt_t die)
	:mBorn{ born }, mSurvive{ survive }, mDie{die}
{
}

Rule::Rule(double min, double max)
{
	randomV(mBorn, 3, 4);
	randomV(mSurvive, min, max);
	randomV(mDie, min, max);
}

bool Rule::canBorn(size_t & nb)
{
	return std::find(mBorn.begin(), mBorn.end(), nb) != mBorn.end();
}

bool Rule::canSurvive(size_t & nb)
{
	return std::find(mSurvive.begin(), mSurvive.end(), nb) != mSurvive.end();
}

bool Rule::willDie(char & index, std::vector<size_t> & occ)
{

	size_t qty = 0;
	for (char i{ 1 }; i < occ.size(); ++i) {
		if (i != index) {
			qty += occ[i];
		}
	}
	return std::find(mDie.begin(), mDie.end(), qty) != mDie.end();
}

vInt_t Rule::getBorn()
{
	return mBorn;
}

vInt_t Rule::getSurvive()
{
	return vInt_t();
}

vInt_t Rule::getDie()
{
	return vInt_t();
}

void Rule::randomV(vInt_t & vec, double min, double max)
{
	int nb = RandomUtil::generateEvent(1, 3);
	for (int i{}; i < nb; ++i) {
		vec.push_back((size_t)RandomUtil::generateEvent(min, max));
	}
}

