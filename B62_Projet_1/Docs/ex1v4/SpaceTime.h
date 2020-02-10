#ifndef SPACE_TIME_H
#define SPACE_TIME_H


#include "Space.h"


class SpaceTime
{
public:
	SpaceTime() = default;
	SpaceTime(size_t spaceSize, size_t timeSize);
	~SpaceTime() = default;

	size_t spaceSize() const;
	size_t timeSize() const;
	bool isReady() const;

	void resize(size_t spaceSize, size_t timeSize);
	void initFill(State const & state);
	void initRandom(double probability = 0.5);
	void initCentered(size_t split = 2);
	void initChecked(State const & state = State());

	State & state(size_t space, size_t time);
	State state(size_t space, size_t time) const;

	SpaceNeighborhood neighborhood(size_t space, size_t time) const;

	std::string toString() const;

private:
	std::vector<Space> mValue;
};


#endif // SPACE_TIME_H
