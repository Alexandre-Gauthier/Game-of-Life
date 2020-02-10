#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include <regex>
#include "../h/RLEReader.h"
#include "../h/Space.h"
#include "../h/GoLRule.h"

//#(C|c|N|O|R|r).* Regex commentaire
//x = [0-9]*, y = [0-9]* Regex regle

RLEReader::RLEReader() {

}

RLEReader::~RLEReader(){

}

bool RLEReader::read(std::string const & fileName, Space & space, std::vector<Rule> & rule) {
	std::ifstream iStream(fileName, std::ios::in);
	std::string line;
	mFileOver = false, mFileXSizeRespected = true, mFileYSizeRespected = true;
	if (iStream.is_open()) {
		std::getline(iStream, line);

		if (isStandardRLEFile(iStream, line)) {
			setSize(line);
			setRule(line, rule);
			setStartingPoint(space.width(), space.height());
			mMultiplier = 0;
			while (!iStream.eof() && !mFileOver) {
				std::getline(iStream, line);
				for (char& c : line) {
					if (mCurrentYPosition < mFileYSize+mStartingYPosition) {
						treatCharcter(c, space);
					}
					else{
						mFileYSizeRespected = false;
					}
					if (!mFileXSizeRespected || !mFileYSizeRespected) {
						return false;
					}
				}
			}
		}
		return true;
	}

	return false;
}

void RLEReader::setSize(std::string const & line) {
	int multiplier = {};
	bool xIsSet{ false };
	for (const char& c : line) {
		if (c == 44) {
			if (!xIsSet) {
				mFileXSize = multiplier;
				xIsSet = true;
			}
			else {
				mFileYSize = multiplier;
			}
			multiplier = 0;
		}
		else if (isNumber(c)) {
			modifyMultiplier(multiplier, c);
		}
	}
}

void RLEReader::setRule(std::string const & line, std::vector<Rule> &rule) {
	std::vector<size_t> currentVector{}, bornVector{}, surviveVector{}, dieVector{};
	bool ruleMet{ false };
	for (const char & c : line) {
		if(c == 82 || c == 114) {
			ruleMet = true;
		}
		if (ruleMet) {
			if (isNumber(c)) {
				currentVector.push_back(charToNumber(c));
			}
			else if (c == 47) {
				bornVector = currentVector;
				currentVector.clear();
			}
		}
	}
	surviveVector = currentVector;
	dieVector.push_back(3);
	if (ruleMet) {
		rule.at(0) = (Rule(bornVector, surviveVector, dieVector));
	}
	
}

char RLEReader::charToNumber(char c) {
	return c - 48;
}

void RLEReader::setStartingPoint(int width, int height) {
	mStartingXPosition = (width - mFileXSize) / 2;
	mStartingYPosition = (height - mFileYSize) / 2;
	mCurrentXPosition = mStartingXPosition;
	mCurrentYPosition = mStartingYPosition;
}

void RLEReader::modifyMultiplier(int & multiplier, char const & c) {
	multiplier *= 10;
	multiplier += (c - 48);
}

bool RLEReader::isNumber(char const & c) {
	return (c > 47 && c < 58);
}

void RLEReader::treatCharcter(char const & c, Space & space) {
	if (isNumber(c)) {
		modifyMultiplier(mMultiplier, c);
	}
	else {
		if (mMultiplier == 0) {
			mMultiplier = 1;
		}
		if(c == 'b'){
			addInactive(space);
		}
		else if (c == 'o') {
			addActive(space);
		}
		else if (c == '$') {
			endOfRow(space);
		}
		else if (c == '!') {
			endOfFile();
		}
		mMultiplier = 0;
	}
}

void RLEReader::addActive(Space & space) {
	for (int i = 0; i < mMultiplier; ++i) {
		if (i + mCurrentXPosition < mStartingXPosition + mFileXSize) {
			space_t & spaceMatrix = space.getSpace();
			spaceMatrix[i + mCurrentXPosition][mCurrentYPosition].setAlive(1);
		}
		else {
			mFileXSizeRespected = false;
			break;
		}
	}
	mLastChar = 'o';
	mCurrentXPosition += mMultiplier;
	
}

void RLEReader::addInactive(Space & space) {
	for (int i = 0; i < mMultiplier; ++i) {
		if (i + mCurrentXPosition < mStartingXPosition + mFileXSize) {
			space.getSpace()[i + mCurrentXPosition][mCurrentYPosition].setDie();
		}
		else {
			mFileXSizeRespected = false;
			break;
		}
	}
	mLastChar = 'b';
	mCurrentXPosition += mMultiplier;
}

void RLEReader::endOfRow(Space & space) {
	
	mMultiplier = mFileXSize - (mCurrentXPosition-mStartingXPosition);
	if (mLastChar == 'o') {
		addInactive(space);
	}
	else if (mLastChar == 'b') {
		addActive(space);
	}
	mCurrentXPosition = mStartingXPosition;
	mCurrentYPosition += 1;
}

void RLEReader::endOfFile() {
	mFileOver = true;
}

bool RLEReader::isStandardRLEFile(std::ifstream & stream, std::string & line) {
	while (isComment(line)) {
		std::getline(stream, line);
	}
	return isSeparator(line);
}

bool RLEReader::isComment(std::string const & line) {
	return regexCheck(line, commentRegex);
}

bool RLEReader::isSeparator(std::string const & line) {
	return regexCheck(line,separatorRegex);
}

bool RLEReader::regexCheck(std::string const & line, std::string const & regex) {
	std::regex matchRegex(regex);
	if (std::regex_match(line, matchRegex)) {
		return true;
	}
	return false;
}
