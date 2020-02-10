#ifndef GOL_NEIGHBORHOOD_H
#define GOL_NEIGHBORHOOD_H


#include <vector>
#include "State.h"


class GoLNeighborhood
{
	using space_t = std::vector<std::vector<State>>;
	//using itCol_t = std::vector<State>::const_iterator;
	//using itRow_t = space_t::const_iterator;

public:
	GoLNeighborhood(space_t const & space, bool & isLooping, size_t & posX, size_t & posY);
	~GoLNeighborhood() = default;

	std::vector<size_t> & getOccurence(size_t & nbStates);

private:
	bool checkBorder(int & y, int const & max);
	std::vector<size_t> mOccurences;

	space_t const & mSpace;
	bool const & mIsLooping;
	size_t const & mPosX;
	size_t const & mPosY;
};



#endif // GOL_NEIGHBORHOOD_H