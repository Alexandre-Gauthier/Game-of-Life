#ifndef RANDOM_UTIL_H
#define RANDOM_UTIL_H


#include <random>


class RandomUtil
{
public:
	RandomUtil() = delete;
	~RandomUtil() = delete;

	// Retourne vrai selon la probabilité spécifiée entre 0 et 1.
	static bool generateEvent(double probability = 0.5);

private:
	static std::random_device randomDevice;
	static std::mt19937 randomGenerator;
};



#endif // RANDOM_UTIL_H