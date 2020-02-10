#ifndef ECA_VIEW_H
#define ECA_VIEW_H


class EcaModel;
#include <string>


class EcaView
{
public:
	EcaView() = default;
	~EcaView() = default;

	void show(std::string const & toUser, bool clearScreen = true);
	void show(EcaModel const & model);

private:
	std::string getHorizontalAxis(size_t from, size_t to, size_t offsetChar);
};


#endif // ECA_VIEW_H