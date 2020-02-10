#ifndef STATE_H
#define STATE_H



class State
{
public:
	using value_t = bool;

	State() = default;
	State(value_t value);
	~State() = default;

	value_t value() const;
	void setValue(value_t value);
	void randomize(double probability = 0.5);

	void toggle();
	State toggled() const;

	static void setRepresentation(char inactive, char active);
	char toChar() const;

private:
	value_t mValue = false;
	static char sInactiveRepresentation;
	static char sActiveRepresentation;
};



#endif // STATE_H
