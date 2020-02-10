#ifndef GOL_RULE
#define GOL_RULE

#include <vector>
using vInt_t = std::vector<size_t>;

class Rule
{
	
public:
	Rule() = default;
	Rule(vInt_t born, vInt_t survive, vInt_t die);
	Rule(double min, double max);
	~Rule() = default;

	bool canBorn(size_t & nb);
	bool canSurvive(size_t & nb);
	bool willDie(char & index, std::vector<size_t> & occ);

	vInt_t getBorn();
	vInt_t getSurvive();
	vInt_t getDie();

private:
	vInt_t mBorn;
	vInt_t mSurvive;
	vInt_t mDie;

	void randomV(vInt_t & vec,double min, double max);

};

#endif
