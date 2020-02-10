#include "EcaView.h"


#include "EcaModel.h"
#include "ConsoleUtil.h"
#include <iostream>
#include <sstream>


void EcaView::show(std::string const & toUser, bool clearScreen)
{
	if (clearScreen) {
		ConsoleUtil::clearScreen();
	}

	std::cout << toUser;
}

void EcaView::show(EcaModel const & model)
{
	const size_t offset{ 5 };
	std::string separator((int)model.spaceSize() + offset, '-');
	separator += '\n';

	ConsoleUtil::clearScreen();
	std::cout	<< separator
				<< model.ruleToString(true)
				<< separator
				<< getHorizontalAxis(0, model.spaceSize() - 1, offset)
				<< model.spaceTimeToString();
}


// Approche naïve mais simple 
std::string EcaView::getHorizontalAxis(size_t from, size_t to, size_t offsetChar)
{
	size_t nDigitsRequired{ (size_t)std::floor(std::log10(to)) + 1ull };
	size_t strLength{ to - from + 1 + offsetChar };
	std::vector<std::string> strList(nDigitsRequired);
	for (size_t d{}; d < nDigitsRequired; ++d) {
		strList[d].resize(strLength + 1);
		strList[d][strLength] = '\0';
	}

	for (size_t i{}; i < offsetChar; ++i) {
		for (size_t d{}; d < nDigitsRequired; ++d) {
			strList[d][i] = ' ';
		}
	}
	for (size_t i{ offsetChar }; i < strLength; ++i) {
		for (size_t d{}; d < nDigitsRequired; ++d) {
			strList[d][i] = '0' + (char)((int)(from / pow(10, nDigitsRequired - d - 1)) % 10);
		}
		++from;
	}

	std::stringstream strStream;
	for (size_t d{}; d < nDigitsRequired; ++d) {
		strStream << strList[d] << std::endl;
	}
	return strStream.str();
}
