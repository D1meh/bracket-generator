#include "KnockoutStage.hpp"

KnockoutStage::KnockoutStage(void) {
	std::cout << std::endl;
}

KnockoutStage::KnockoutStage(int joueurs, bool bracket) {
	this->joueurs = joueurs;
	this->win_or_lose_bracket = bracket;
	if (joueurs == 4) {
		this->nb_qualif = 1;
		this->qualified = 2;
		this->groups.push_back(2);
		this->groups.push_back(2);
		this->same_number = true;
	} else if (joueurs == 2) {
		this->nb_qualif = 1;
		this->qualified = 1;
		this->groups.push_back(2);
		this->same_number = true;
	}
}

KnockoutStage::~KnockoutStage(void) {
	this->groups.clear();
}

std::ostream& operator<<(std::ostream& os, const KnockoutStage & stage) {
	char poule = 'A';
	std::vector<int>::const_iterator it = stage.groups.begin();

	while (it != stage.groups.end()) {
		std::cout << "Groupe " << poule << " : " << *it << " joueurs " << std::endl;
		it++;
		poule++;
	}
	std::cout << "Nombre de qualifiés : " << stage.qualified << std::endl;
	return os;
}