#ifndef STATE_H
#define STATE_H


class State
{
public:
	using value_t = char;

	State();
	State(value_t value);
	~State() = default;

	value_t value() const &;
	void setAlive(char value);
	void setDie();

	void randomize(double min, double max, double probability);
	State isAlive() const;
private:
	value_t mValue;
	static char sDieRepresentation;
	static char sAliveRepresentation;
};



#endif // STATE_H