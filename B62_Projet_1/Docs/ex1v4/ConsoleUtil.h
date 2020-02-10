#ifndef CONSOLE_UTIL_H
#define CONSOLE_UTIL_H


#include <string>


class ConsoleUtil
{
public:
	ConsoleUtil() = delete;
	~ConsoleUtil() = delete;

	// Vide l'�cran
	static void clearScreen();

	// Retourne la saisie d'un caract�re au clavier.
	// Le caract�re retourn� est mis en majuscule.
	static char getUpperChar();

	// Retourne vrai si le caract�re saisie au clavier 
	// correspond au caract�re attendu (insensible � la casse).
	static bool validateUpperChar(char capChar);

	// Retourne un entier saisie au clavier.
	static int getInt(std::string const & title);

	// Retourne un entier born� saisie au clavier.
	static int getInt(std::string title, int min, int max, bool addLimitsToTitle = true);

private:
	// isStringInt return true if all character meet the integer literal requirements.
	// La fonction std::stoi retourne un entier m�me si la fin de la cha�ne de caract�res est invalide (en autant qu'il y ait un int au d�but).
	static bool isStrictInt(std::string const & str);
};


#endif // CONSOLE_UTIL_H