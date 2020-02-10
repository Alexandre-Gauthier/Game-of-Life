#include "EcaModel.h"


#include <algorithm>


void EcaModel::resize(size_t spaceSize, size_t timeSize)
{
	mSpaceTime.resize(spaceSize, timeSize);
}

size_t EcaModel::spaceSize() const
{
	return mSpaceTime.spaceSize();
}

size_t EcaModel::timeSize() const
{
	return mSpaceTime.timeSize();
}

void EcaModel::generateFromState(State const & state)
{
	mSpaceTime.initFill(state);
	applyRule();
}

void EcaModel::generateFromRandom(double probability)
{
	mSpaceTime.initRandom(probability);
	applyRule();
}

void EcaModel::generateFromCentered(size_t split)
{
	mSpaceTime.initCentered(split);
	applyRule();
}

void EcaModel::generateFromChecked(State const & state)
{
	mSpaceTime.initChecked(state);
	applyRule();
}

void EcaModel::setRule(Rule::value_t rule)
{
	mRule.set(rule);
}

void EcaModel::nextRule(size_t i)
{
	mRule.next(i);
}

void EcaModel::previousRule(size_t i)
{
	mRule.previous(i);
}

void EcaModel::nextNotableRule()
{
	mRule.nextNotable();
}

void EcaModel::prevNotableRule()
{
	mRule.prevNotable();
}

std::string EcaModel::spaceTimeToString() const
{
	return mSpaceTime.toString();
}

std::string EcaModel::ruleToString(bool includeBinaryRepresentation) const
{
	return mRule.toString(includeBinaryRepresentation);
}

void EcaModel::applyRule(size_t space, size_t time)
{
	mRule.apply(mSpaceTime.state(space, time), mSpaceTime.neighborhood(space, time - 1).toInt());
}

void EcaModel::applyRule(size_t time)
{
	for (size_t space{}; space < mSpaceTime.spaceSize(); ++space) {
		applyRule(space, time);
	}
}

void EcaModel::applyRule()
{
	for (size_t time{ 1 }; time < mSpaceTime.timeSize(); ++time) {
		applyRule(time);
	}
}

