#ifndef RULE_H
#define RULE_H


#include <array>

class State;
class Space;


class Rule
{
public:
	using value_t = unsigned char;

	Rule() = default;
	Rule(value_t value);
	~Rule() = default;

	void set(value_t value);

	void next(size_t i = 1);
	void previous(size_t i = 1);
	void nextNotable();
	void prevNotable();

	void apply(State & state, value_t combination) const;

	std::string toString(bool includeBinaryRepresentation = true) const;

private:
	value_t mValue = 0;

	static const std::array<value_t, 24> sInterestingRules;
	static size_t sMaxRuleCount;
};



#endif // RULE_H
