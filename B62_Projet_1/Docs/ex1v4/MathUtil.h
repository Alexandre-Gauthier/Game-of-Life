#ifndef MATH_UTIL_H
#define MATH_UTIL_H


class MathUtil
{
public:
	MathUtil() = delete;
	~MathUtil() = delete;

	static double warp(double value, double begin, double end);
	static double warp(double value, double width);
	static int warp(int value, int begin, int end);
	static int warp(int value, int width);
	static size_t warp(size_t value, size_t begin, size_t end);
	static size_t warp(size_t value, size_t width);
};


#endif // MATH_UTIL_H
