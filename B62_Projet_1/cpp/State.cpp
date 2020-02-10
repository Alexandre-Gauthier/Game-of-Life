#include "../h/State.h"
#include "../h/RandomUtil.h"


State::State()
	:mValue{}
{
}

State::State(value_t value)
	: mValue{ value }
{
}

State::value_t State::value() const &
{
	return mValue;
}

void State::setAlive(char value)
{
	mValue = value;
}

void State::setDie() 
{
	mValue = 0;
}

void State::randomize(double min, double max, double probability)
{
	mValue = RandomUtil::generateEvent(probability) ? RandomUtil::generateEvent(min, max) : 0;

}

State State::isAlive() const
{
	return (mValue > 0) ? true : false;
	
}

