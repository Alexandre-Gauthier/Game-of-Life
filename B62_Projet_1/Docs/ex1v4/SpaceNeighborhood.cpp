#include "SpaceNeighborhood.h"



SpaceNeighborhood::SpaceNeighborhood(std::vector<State> const & space, std::vector<State>::const_iterator stateIt)
	: mSpace{ space }, mStateIt{ stateIt }
{
}

State const & SpaceNeighborhood::left() const
{
	return mStateIt == mSpace.begin() ? mSpace.back() : *std::prev(mStateIt);
}

State const & SpaceNeighborhood::center() const
{
	return *mStateIt;
}

State const & SpaceNeighborhood::right() const
{
	return mStateIt == std::prev(mSpace.end()) ? mSpace.front() : *std::next(mStateIt);
}

int SpaceNeighborhood::toInt() const
{
	return	((int)left().value() << 2) |
			((int)center().value() << 1) |
			((int)right().value() << 0);
}
