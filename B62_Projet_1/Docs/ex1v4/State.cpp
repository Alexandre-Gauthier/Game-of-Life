#include "State.h"


#include "RandomUtil.h"


char State::sInactiveRepresentation{ ' ' };
char State::sActiveRepresentation{ '*' };


State::State(value_t value)
	: mValue{ value }
{
}

State::value_t State::value() const
{
	return mValue;
}

void State::setValue(value_t value)
{
	mValue = value;
}

void State::randomize(double probability)
{
	mValue = RandomUtil::generateEvent(probability);
}

void State::toggle()
{
	mValue = !mValue;
}

State State::toggled() const
{
	return State(!mValue);
}

void State::setRepresentation(char inactive, char active)
{
	sInactiveRepresentation = inactive;
	sActiveRepresentation = active;
}

char State::toChar() const
{
	return mValue ? sActiveRepresentation : sInactiveRepresentation;
}
