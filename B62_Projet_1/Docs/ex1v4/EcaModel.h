#ifndef ECA_MODEL_H
#define ECA_MODEL_H


#include "SpaceTime.h"
#include "Rule.h"


class EcaModel
{
public:
	EcaModel() = default;
	~EcaModel() = default;

	void resize(size_t spaceSize, size_t timeSize);
	size_t spaceSize() const;
	size_t timeSize() const;

	void generateFromState(State const & state);
	void generateFromRandom(double probability = 0.5);
	void generateFromCentered(size_t split = 2);
	void generateFromChecked(State const & state = State());

	void setRule(Rule::value_t rule);
	void nextRule(size_t i = 1);
	void previousRule(size_t i = 1);
	void nextNotableRule();
	void prevNotableRule();

	std::string spaceTimeToString() const;
	std::string ruleToString(bool includeBinaryRepresentation = true) const;

private:
	SpaceTime mSpaceTime;
	Rule mRule;

	void applyRule(size_t space, size_t time);
	void applyRule(size_t time);
	void applyRule();
};


#endif // ECA_MODEL_H
