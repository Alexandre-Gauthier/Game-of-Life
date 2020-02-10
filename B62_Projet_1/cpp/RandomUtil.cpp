#include "../h/RandomUtil.h"


std::random_device RandomUtil::randomDevice;
std::mt19937 RandomUtil::randomGenerator(randomDevice());


int RandomUtil::generateEvent(double min, double max)
{
	std::uniform_int_distribution<> randomDistribution(min,max);
	return randomDistribution(randomGenerator);
}

bool RandomUtil::generateEvent(double probability)
{
	std::bernoulli_distribution randomDistribution(probability);
	return randomDistribution(randomGenerator);
}

