#include "../h/Space.h"
#include "../h/GoLNeighborhood.h"

#include <vector>
#include <algorithm>

Space::Space()
	:Space(200, 200)
{
}

Space::Space(size_t width, size_t height)
{
	initializeSpace(width, height);
}

//Space::Space(size_t width, size_t height)
//{
//	fill(state);
//}

void Space::initializeSpace(size_t width, size_t height)
{
	//mSpace.resize(height);
	for (size_t i = 0; i < height; ++i) {
		std::vector<State> row;
		for (size_t j{ 0 }; j < width; ++j) {
			State state;
			row.push_back(state);
		}
		mSpace.push_back(row);
	}
}

//Return the vector or State

space_t & Space::getSpace()
{
	return  mSpace;
}

//Size of the whole space
size_t Space::height() const
{
	return mSpace.size();
}

//Size of a row
size_t Space::width(size_t row) const {
	return mSpace[row].size();
}

size_t Space::width() const {
	return mSpace[0].size();
}

bool Space::isReady() const
{
	return height() > 0;
}

void Space::clearSpace() {
	mSpace.clear();
}

void Space::resize(size_t size)
{
	mSpace.resize(size);
}

void Space::fill(State const & state)
{
	std::for_each(mSpace.begin(), mSpace.end(), [this, state](std::vector<State> & row) {fillRow(state, row); });
}

void Space::fillRow(State const & state, std::vector<State> & row)
{
	std::fill(row.begin(), row.end(), state);
}

void Space::randomize(double probability, double min, double max)
{
	std::for_each(mSpace.begin(), mSpace.end(), [this, probability, min, max](std::vector<State> & row) {randomizeRow(row, probability, min, max); });
}

void Space::randomizeRow(std::vector<State> & row, double probability, double min, double max)
{
	std::for_each(row.begin(), row.end(), [probability, min, max](State & cell) {cell.randomize(min, max, probability); });
}

GoLNeighborhood Space::getNeighborhood(bool & isLooping, size_t & posX, size_t & posY)
{
	return GoLNeighborhood(mSpace, isLooping, posX, posY);
}

