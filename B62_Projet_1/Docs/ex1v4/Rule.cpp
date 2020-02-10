#include "Rule.h"


#include "State.h"
#include "MathUtil.h"
#include "BitUtil.h"
#include <algorithm>
#include <sstream>


const std::array<Rule::value_t, 24> Rule::sInterestingRules{ 11, 18, 22, 26, 28, 30, 50, 54, 57, 60, 90, 94, 102, 110, 122, 126, 146, 150, 154, 158, 188, 190, 220, 222 };
size_t Rule::sMaxRuleCount{ (size_t)std::pow(2, sizeof(Rule::value_t) * 8) };


Rule::Rule(value_t value)
	: mValue{ value }
{
}

void Rule::set(value_t value)
{
	mValue = mValue;
}

void Rule::next(size_t i)
{
	mValue = (value_t)((mValue + i) % sMaxRuleCount);
}

void Rule::previous(size_t i)
{
	mValue = MathUtil::warp((int)mValue - (int)i, (int)sMaxRuleCount);
}

void Rule::nextNotable()
{
	//auto it{ std::lower_bound(sInterestingRules.begin(), sInterestingRules.end(), (mValue + 1) % sMaxRuleCount) };
	//auto it{ std::lower_bound(sInterestingRules.begin(), sInterestingRules.end(), mValue, std::less_equal<Rule::value_t>()) };
	auto it{ std::upper_bound(sInterestingRules.begin(), sInterestingRules.end(), mValue) };
	if (it == sInterestingRules.end()) {
		mValue = sInterestingRules.front();
	} else {
		mValue = *it;
	}
}

void Rule::prevNotable()
{
	auto it{ std::upper_bound(sInterestingRules.rbegin(), sInterestingRules.rend(), mValue, std::greater<Rule::value_t>()) };
	if (it == sInterestingRules.rend()) {
		mValue = sInterestingRules.back();
	} else {
		mValue = *it;
	}
}

void Rule::apply(State & state, value_t combination) const
{
	state.setValue(BitUtil::isBitSet(mValue, combination));
}

std::string Rule::toString(bool includeBinaryRepresentation) const
{
	std::stringstream strStream;

	strStream	<< "Rule : " 
				<< (int)mValue;
	if (includeBinaryRepresentation) {
		strStream	<< "   ["
					<< BitUtil::int2bin(mValue, 8)
					<< "]";
	}
	strStream << std::endl;

	return strStream.str();
}
