//CoursB62
//Classe permettant la lecture de fichier RLE
//Date de création : 10 Mars 2019
//Auteurs:
//	- Hugo Turgeon-Nozaki

#ifndef RLE_READER_H
#define RLE_READER_H
#include <string>

class Space;
class Rule;

class RLEReader
{
	public:
		RLEReader();
		~RLEReader();
		bool read(std::string const & fileName, Space & space, std::vector<Rule> & rule);
		bool isComment(std::string const & line);
		bool isSeparator(std::string const & line);
		bool regexCheck(std::string const & line, std::string const & regex);
		bool isStandardRLEFile(std::ifstream  & stream, std::string & line);
		void setSize(std::string const & line);
		void setStartingPoint(int widht, int height);
		void modifyMultiplier(int & multiplier, char const & c);
		bool isNumber(char const & c);
		void treatCharcter(char const & c, Space & space);
		void addInactive(Space & space);
		void addActive(Space & space);
		void endOfRow(Space & space);
		void endOfFile();
	private:
		const std::string commentRegex = "#[CcNORr] .*";
		const std::string separatorRegex = "x = [0-9]*, y = [0-9]*(, rule = [Bb]?[0-9]*\\/[Ss]?[0-9]*)?";
		char mLastChar;
		int mMultiplier, mCurrentXPosition, mStartingXPosition, mCurrentYPosition, mStartingYPosition, mFileXSize, mFileYSize;
		void setRule(std::string const & line, std::vector<Rule> & rule);
		char charToNumber(char c);
		bool mFileOver, mFileXSizeRespected, mFileYSizeRespected;
		int mLineCounter;

};

#endif