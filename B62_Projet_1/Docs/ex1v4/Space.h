#ifndef SPACE_H
#define SPACE_H


#include "State.h"
#include "SpaceNeighborhood.h"
#include <string>
#include <vector>


class Space
{
public:
	Space() = default;
	Space(size_t size);
	Space(size_t size, State const & state);
	~Space() = default;

	size_t size() const;
	bool isReady() const;

	void resize(size_t size);
	void fill(State const & state);
	void randomize(double probability);
	void setCentered(size_t split = 2);
	void setChecked(State startingState = State());

	State & state(size_t i);
	State state(size_t i) const;

	SpaceNeighborhood neighborhood(size_t i) const;

	std::string toString() const;

private:
	std::vector<State> mValue;
};



#endif // SPACE_H