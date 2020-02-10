#include "SpaceTime.h"


#include <sstream>
#include <algorithm>
#include <iomanip>


SpaceTime::SpaceTime(size_t spaceSize, size_t timeSize)
{
	resize(spaceSize, timeSize);
}

size_t SpaceTime::spaceSize() const
{
	return mValue.size() > 0 ? mValue[0].size() : 0;
}

size_t SpaceTime::timeSize() const
{
	return mValue.size();
}

bool SpaceTime::isReady() const
{
	return timeSize() > 0;
}

void SpaceTime::resize(size_t spaceSize, size_t timeSize)
{
	mValue.resize(timeSize);
	std::for_each(mValue.begin(), mValue.end(), [spaceSize](Space & space)->void { space.resize(spaceSize); });
}

void SpaceTime::initFill(State const & state)
{
	mValue[0].fill(state);
}

void SpaceTime::initRandom(double probability)
{
	mValue[0].randomize(probability);
}

void SpaceTime::initCentered(size_t split)
{
	mValue[0].setCentered(split);
}

void SpaceTime::initChecked(State const & state)
{
	mValue[0].setChecked(state);
}

State & SpaceTime::state(size_t space, size_t time)
{
	return mValue[time].state(space);
}

State SpaceTime::state(size_t space, size_t time) const
{
	return mValue[time].state(space);
}

SpaceNeighborhood SpaceTime::neighborhood(size_t space, size_t time) const
{
	return mValue[time].neighborhood(space);
}

std::string SpaceTime::toString() const
{
	size_t t{};
	std::stringstream strStream;

	std::for_each(mValue.begin(), mValue.end(), [&strStream, &t](Space const & space)->void { 
		strStream	<< std::setfill('0') << std::setw(2)
					<< t++ << "]  "
					<< space.toString() << std::endl; 
	});

	return strStream.str();
}

