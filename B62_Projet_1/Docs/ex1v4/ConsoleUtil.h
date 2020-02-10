#ifndef CONSOLE_UTIL_H
#define CONSOLE_UTIL_H


#include <string>


class ConsoleUtil
{
public:
	ConsoleUtil() = delete;
	~ConsoleUtil() = delete;

	// Vide l'écran
	static void clearScreen();

	// Retourne la saisie d'un caractère au clavier.
	// Le caractère retourné est mis en majuscule.
	static char getUpperChar();

	// Retourne vrai si le caractère saisie au clavier 
	// correspond au caractère attendu (insensible à la casse).
	static bool validateUpperChar(char capChar);

	// Retourne un entier saisie au clavier.
	static int getInt(std::string const & title);

	// Retourne un entier borné saisie au clavier.
	static int getInt(std::string title, int min, int max, bool addLimitsToTitle = true);

private:
	// isStringInt return true if all character meet the integer literal requirements.
	// La fonction std::stoi retourne un entier même si la fin de la chaîne de caractères est invalide (en autant qu'il y ait un int au début).
	static bool isStrictInt(std::string const & str);
};


#endif // CONSOLE_UTIL_H