#ifndef RANDOM_UTIL_H
#define RANDOM_UTIL_H


#include <random>


class RandomUtil
{
public:
	RandomUtil() = delete;
	~RandomUtil() = delete;

	static int generateEvent(double min, double max); //Uniforme
	static bool generateEvent(double probability); //Bernoulli
private:
	static std::random_device randomDevice;
	static std::mt19937 randomGenerator;
};



#endif // RANDOM_UTIL_H