#ifndef SPACE_H
#define SPACE_H

#include "State.h"
#include <vector>
#include "../h/GoLNeighborhood.h"


using space_t = std::vector<std::vector<State>>;

class Space
{
public:
	Space();
	Space(size_t width, size_t height);
	//Space(size_t width, size_t height, State const & state);
	~Space() = default;

	space_t & getSpace();
	size_t height() const;
	size_t width(size_t row) const;
	size_t width() const;
	bool isReady() const;
	void clearSpace();

	void resize(size_t size);
	void fill(State const & state);
	void fillRow(State const & state, std::vector<State> & row);
	void randomize(double probability, double min, double max);
	void randomizeRow(std::vector<State> & row, double probability, double min, double max);
	GoLNeighborhood getNeighborhood(bool & isLooping, size_t & posX, size_t & posY);

private:
	void initializeSpace(size_t width, size_t height);
	space_t mSpace;
};

#endif // SPACE_H