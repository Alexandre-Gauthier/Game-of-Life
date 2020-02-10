#include "../h/GoLNeighborhood.h"

GoLNeighborhood::GoLNeighborhood(space_t const & space, bool & isLooping, size_t & posX, size_t & posY)
	:mSpace{ space }, mIsLooping{ isLooping }, mPosX{ posX }, mPosY{ posY }
{
}

std::vector<size_t> & GoLNeighborhood::getOccurence(size_t & nbStates)
{
	mOccurences.resize(nbStates);
	int dist = 1; // Pas encore totalement fonctionnel
	
	for (int dx = -dist; dx <= dist; ++dx){
		for (int dy = -dist; dy <= dist; ++dy){
			int nx = mPosX + dx;
			int ny = mPosY + dy;

			if (nx == mPosX && ny == mPosY) {
				continue;
			}

			if (checkBorder(ny, mSpace.size() - 1) && checkBorder(nx, mSpace[ny].size()-1)) {
				++mOccurences[mSpace[nx][ny].value()];
			}
		}
	}

	return mOccurences;
}

bool GoLNeighborhood::checkBorder(int & y, int const & max) {
	if (y < 0) {
		y = max;
		return mIsLooping;
	}
	else if (y > max) {
		y = 0;
		return mIsLooping;
	}
	
	return true;
}
