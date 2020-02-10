#include "MathUtil.h"


#include <cmath>


double MathUtil::warp(double value, double begin, double end) 
{
	const double width{ end - begin };
	return value - std::floor((value - begin) / width) * width;
}

double MathUtil::warp(double value, double width) 
{
	return value - std::floor(value / width) * width;
}

int MathUtil::warp(int value, int begin, int end) 
{
	const int width{ end - begin };
	return value - (value - begin) / width * width;
}

int MathUtil::warp(int value, int width) 
{
	return value - value / width * width;
}

size_t MathUtil::warp(size_t value, size_t begin, size_t end) 
{
	return (size_t)warp((int)value, (int)begin, (int)end);
}

size_t MathUtil::warp(size_t value, size_t width)
{
	return (size_t)warp((int)value, (int)width);
}

