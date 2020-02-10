#include "ConsoleUtil.h"


// La console est en mode canonique


#include <conio.h>			// Require for : _getch
#include <cstdlib>			// Require for : system
#include <ctype.h>			// Require for : toupper
#include <cctype>			// Require for : isdigit

#include <iostream>			// Require for : cin, cout, getline
#include <algorithm>		// Require for : all_of
#include <stdexcept>		// Require for : invalid_argument


// Définition des constantes utilisées
const std::string getIntRangeValuePrefix(" (entre ");
const std::string getIntRangeValueSeparator(" et ");
const std::string getIntRangeValueSuffix(")");

// Cet exemple possède plusieurs chaînes de caractères spécifiées directement dans le code.
// C'est une pratique non recommandée et il faudrait reprendre 


void ConsoleUtil::clearScreen()
{
	system("cls");
}


#define _GETCH_TWO_TIMES_				// See note 1 below - must be recompile to consider specific Windows update

char ConsoleUtil::getUpperChar()
{
	int keyCode{ _getch() };
#ifdef _GETCH_TWO_TIMES_				// (1) _getch must be call twice to catch the key code
	int functionKey{ _getch() };		// and the function key
#endif
	return (char)toupper(keyCode);
}

bool ConsoleUtil::validateUpperChar(char capChar)
{
	return getUpperChar() == (char)toupper(capChar);
}

int ConsoleUtil::getInt(std::string const & title)
{
	int value{};
	std::string str, exceptionMessage;
	bool fail{};
	do {
		fail = false;
		std::cout << title;
		std::getline(std::cin, str);
		try {
			if (!isStrictInt(str)) { // on pourrait éviter le throw en faisant le if avant le try : mais on le laisse ici à titre d'exemple pédagogique
				throw std::invalid_argument("end of string is invalid");
			}
			value = std::stoi(str);
		} catch (std::invalid_argument e) {
			exceptionMessage = std::string("No conversion could be performed - ") + e.what();
			fail = true;
		} catch (std::out_of_range e) {
			exceptionMessage = std::string("Value out of range - ") + e.what();
			fail = true;
		}
		if (fail) {
			std::cout << exceptionMessage << std::endl;
		}
	} while (fail);
	return value;
}

int ConsoleUtil::getInt(std::string title, int min, int max, bool addLimitsToTitle)
{
	if (min >= max) {
		throw std::invalid_argument("Invalid argument in getInt.");
	}

	if (addLimitsToTitle) {
		title += getIntRangeValuePrefix + std::to_string(min) + getIntRangeValueSeparator + std::to_string(max) + getIntRangeValueSuffix;
	}
	title += " : ";

	int value{};
	bool fail{};
	std::string exceptionMessage;
	do {
		fail = false;
		value = getInt(title);
		if (value < min) {
			exceptionMessage = "Value is lower than " + std::to_string(min) + "\n";
			fail = true;
		} else if (value > max) {
			exceptionMessage = "Value is higher than " + std::to_string(max) + "\n";
			fail = true;
		}
		if (fail) {
			std::cout << exceptionMessage;
		}
	} while (fail);
	return value;
}

bool ConsoleUtil::isStrictInt(std::string const & str)
{
	// Approche intéressante mais plus lente : 
	//		return std::regex_match(num, std::regex("[+-]?[0-9]+")); // <--- ce regex est insuffisant

	switch (str.length()) {
		case 0:	// empty string
			return false;
		case 1: // one char string => must be a digit
			return std::isdigit(str.front());
		default: // longer than one char string
			// first may be a '+' or '-' or a digit but all other must a digit
			if (str.front() == '+' || str.front() == '-') {
				return std::all_of(str.cbegin() + 1, str.cend(), std::isdigit);
			} else {
				return std::all_of(str.cbegin(), str.cend(), std::isdigit);
			}
	}
}
