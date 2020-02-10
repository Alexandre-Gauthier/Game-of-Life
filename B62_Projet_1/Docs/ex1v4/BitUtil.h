#ifndef BIT_UTIL_H
#define BIT_UTIL_H


#include <string>


class BitUtil
{
public:
	// Retourne vrai si un bit est actif
	static bool isBitSet(size_t number, size_t digit);

	// Effectue la conversion d'un nombre entier vers 
	// un text représentant le nombre binaire.
	static std::string int2bin(int value, size_t nFirstDigit);

};





#endif // BIT_UTIL_H