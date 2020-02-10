#ifndef SPACE_NEIGHBORHOOD_H
#define SPACE_NEIGHBORHOOD_H


#include <vector>
#include "State.h"


class SpaceNeighborhood
{
public:
	SpaceNeighborhood(std::vector<State> const & space, std::vector<State>::const_iterator stateIt);
	~SpaceNeighborhood() = default;

	State const & left() const;
	State const & center() const;
	State const & right() const;

	int toInt() const;

private:
	std::vector<State> const & mSpace;
	std::vector<State>::const_iterator mStateIt;
};



#endif // SPACE_NEIGHBORHOOD_H