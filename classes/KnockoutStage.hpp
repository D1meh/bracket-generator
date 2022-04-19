#ifndef KNOCKOUTSTAGE_HPP
#define KNOCKOUTSTAGE_HPP

#include "../includes.hpp"

class KnockoutStage {

public:

	KnockoutStage(int joueurs, bool bracket = true);
	KnockoutStage(void);
	~KnockoutStage(void);

	int joueurs;
	int nb_qualif;
	int qualified;
	bool win_or_lose_bracket;
	bool same_number;

	std::vector<int> groups;

private:


};

std::ostream& operator<<(std::ostream& os, const KnockoutStage & stage);

#endif