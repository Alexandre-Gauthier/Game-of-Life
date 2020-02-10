#include "Space.h"


#include <algorithm>
#include <sstream>


Space::Space(size_t size)
	: mValue(size)
{
}

Space::Space(size_t size, State const & state)
	: Space(size)
{
	fill(state);
}

size_t Space::size() const
{
	return mValue.size();
}

bool Space::isReady() const
{
	return size() > 0;
}

void Space::resize(size_t size)
{
	mValue.resize(size);
}

void Space::fill(State const & state)
{
	std::fill(mValue.begin(), mValue.end(), state);
}

void Space::randomize(double probability)
{
	std::for_each(mValue.begin(), mValue.end(), [probability](State & state)->void { state.randomize(probability); });
}

void Space::setCentered(size_t split)
{
	State currentState(false);
	fill(currentState);
	currentState.toggle();

	double step{ (double)mValue.size() / split }, i{ step };
	while (i < (double)mValue.size()) {
		mValue[(int)std::round(i)] = currentState;
		i += step;
	}
}

void Space::setChecked(State startingState)
{
	State currentState(startingState.toggled());
	std::generate(mValue.begin(), mValue.end(), [&currentState]()->State { currentState.toggle(); return currentState; });
}

State & Space::state(size_t i)
{
	return mValue[i];
}

State Space::state(size_t i) const
{
	return mValue[i];
}

SpaceNeighborhood Space::neighborhood(size_t i) const
{
	return SpaceNeighborhood(mValue, std::next(mValue.cbegin(), i));
}

std::string Space::toString() const
{
	std::stringstream strStream;

	std::for_each(mValue.begin(), mValue.end(), [&strStream](State const & state)->void { strStream << state.toChar(); });

	return strStream.str();
}

