#include "BitUtil.h"


#include <sstream>
#include <stdexcept>


bool BitUtil::isBitSet(size_t number, size_t digit)
{
	if (digit >= sizeof(size_t) * 8) {
		throw std::invalid_argument("Invalid argument in isBitSet.");
	}

	return (number >> digit) & 0b1;
}

std::string BitUtil::int2bin(int value, size_t nFirstDigit)
{
	std::stringstream strStream;
	if (nFirstDigit > sizeof(int) * 8) {
		strStream << std::string(nFirstDigit - sizeof(int) * 8, '0');
	}

	for (int i{ (int)nFirstDigit - 1 }; i >= 0; --i) {
		strStream << isBitSet(value, i) ? '1' : '0';
	}

	return strStream.str();
}


