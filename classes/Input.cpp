#include "Input.hpp"

Input::~Input(void) {

}

Input::Input(void) {


	std::cout << "Nombre de participants ? ";
	std::cin >> this->nb_participants;
	std::cout << "Loser bracket ? (Y/N) ";
	char tmp;
	std::cin >> tmp;
	this->loser_bracket = (tmp == 'Y' || tmp == 'y' ? true : false);
	
	// std::cout << "Nombre de personnes par match de phase à élimination (le nombre peut être réduit lors des phases suivantes) ? ";
	// std::cin >> this->nb_elim;
	// std::cout << "Nombre de qualifiés par match de phase à élimination (le nombre peut être réduit lors des phases suivantes) ? ";
	// std::cin >> this->qualif_elim;
	// std::cout << "Vérifiez vos informations avant de valider : (Y/N) ";
	// std::cin >> tmp;
	// if (tmp == 'y' || tmp == 'Y')
	// 	break;
}

void Input::generateGroupStages(void) {

	std::cout << std::endl << "Génération de la phase de poules en cours..." << std::endl;
	std::cout << "Nombre MAX de personnes par poules ? ";
	std::cin >> this->nb_poules;
	std::cout << "Nombre de qualifiés par poule ? ";
	std::cin >> this->qualif_poules;

	int left = this->nb_participants;
	while (left && left % this->nb_poules) {
		this->groupStages.push_back(this->nb_poules-1);
		left -= this->nb_poules-1;
	}
	while (left) {
		this->groupStages.push_back(this->nb_poules);
		left -= this->nb_poules;
	}
}

void Input::calculateQualified(void) {
	int qualified = 0, smaller_groups = 0;
	std::vector<int>::iterator it = this->groupStages.begin();

	while (it != this->groupStages.end()) {
		if (*it == this->nb_poules)
			qualified += this->qualif_poules;
		else
			smaller_groups++;
		it++;
	}
	if ((qualified + smaller_groups * (this->qualif_poules-1)) % 2 == 0 && smaller_groups) {
		qualified = qualified + smaller_groups * (this->qualif_poules-1);
		std::cout << "Il y aura une personne en moins qualifiée dans les poules de moins de " << this->nb_poules << " joueurs" << std::endl;
	} else {
		qualified = qualified + smaller_groups * this->qualif_poules;
		std::cout << "Toutes les poules auront le même nombre de qualifiés" << std::endl;
	}

	this->qualified = qualified;
	std::cout << "Il y aura " << qualified << " qualifiés après cette phase" << std::endl;
}

void Input::printGroupStages(void) const {
	char a = 'A';
	std::vector<int>::const_iterator it = this->groupStages.begin();
	while (it != this->groupStages.end()) {
		std::cout << "Poule " << a << " : " << *it << " joueurs" << std::endl;
		a++;
		it++;
	}
}

void Input::generateNextStages(void) {
	std::cout << std::endl << "Génération des phases à élimination..." << std::endl;
	std::cout << "Nombre MAX de personnes par match de phase à élimination ? ";
	std::cin >> this->nb_elim;
	std::cout << "Nombre MAX de qualifiés par match de phase à élimination ? ";
	std::cin >> this->qualif_elim;


	int phase = 1;
	int qualified = this->qualified;
	int left = qualified;
	int smaller_groups = 0;
	int to_be_qualified = 0;

	std::cout << "GENERATION DU WINNER BRACKET" << std::endl << std::endl;
	while (qualified > 2) {
		this->winnerBracket.push_back(KnockoutStage(qualified));
		this->winnerBracket[phase-1].groups.clear();
		if (qualified == this->nb_elim) {
			this->winnerBracket[phase-1].nb_qualif = 1;
			this->winnerBracket[phase-1].qualified = 2;
			this->winnerBracket[phase-1].groups.push_back(this->nb_elim/2);
			this->winnerBracket[phase-1].groups.push_back(this->nb_elim/2);
		} else {
			while (left && left % this->nb_elim) {
				this->winnerBracket[phase-1].groups.push_back(this->nb_elim-1);
				left -= this->nb_elim-1;
				smaller_groups++;
			}
			while (left) {
				this->winnerBracket[phase-1].groups.push_back(this->nb_elim);
				left -= this->nb_elim;
				to_be_qualified += this->qualif_elim;
			}
			if ((to_be_qualified + smaller_groups * (this->qualif_elim-1)) % 2 == 0 && smaller_groups)
				to_be_qualified = to_be_qualified + smaller_groups * (this->qualif_elim-1);
			else
				to_be_qualified = to_be_qualified + smaller_groups * this->qualif_elim;
			this->winnerBracket[phase-1].qualified = to_be_qualified;
			this->winnerBracket[phase-1].nb_qualif = this->qualif_elim;
		}

		std::cout << std::endl << "Phase " << phase << " avec " << qualified << " joueurs : " << std::endl;
		std::cout << this->winnerBracket[phase-1];
		if ((to_be_qualified + smaller_groups * (this->qualif_elim-1)) % 2 == 0 && smaller_groups)
			std::cout << "Il y aura une personne en moins qualifiée dans les groupes de moins de " << this->nb_elim << " joueurs" << std::endl;
		else
			std::cout << "Tous les groupes auront le même nombre de qualifiés" << std::endl;
		

		qualified = this->winnerBracket[phase-1].qualified;
		left = qualified;
		phase++;
		smaller_groups = 0;
		to_be_qualified = 0;
	}

	std::cout << std::endl << "Il ne reste que " << qualified << " joueurs, la phase " << phase << " sera donc la finale " << (this->loser_bracket ? "du winner bracket !" : "!") << std::endl;

	if (this->loser_bracket)
		this->generateLoserBracket();
}

void Input::generateLoserBracket(void) {
	
	int tour = 1;
	int player_left = this->nb_participants - this->qualified;
	int left = player_left;
	int smaller_groups = 0;
	int left_next_round = 0;
	int a_checker = 0;
	
	std::cout << std::endl << std::endl << "GENERATION DU LOSER BRACKET" << std::endl << std::endl;
	while (player_left > 1) {
		this->loserBracket.push_back(KnockoutStage(player_left, false));
		this->loserBracket[tour-1].groups.clear();

		if (player_left == 2) {
			this->loserBracket[tour-1].nb_qualif = 1;
			this->loserBracket[tour-1].qualified = 1;
			this->loserBracket[tour-1].groups.push_back(2);
			left_next_round = 1;
		}		
		else if (player_left == this->nb_elim) {
			this->loserBracket[tour-1].nb_qualif = 1;
			this->loserBracket[tour-1].qualified = 2;
			this->loserBracket[tour-1].groups.push_back(this->nb_elim/2);
			this->loserBracket[tour-1].groups.push_back(this->nb_elim/2);
			left_next_round = 2;
		} else {
			while (left && left % this->nb_elim) {
				this->loserBracket[tour-1].groups.push_back(this->nb_elim-1);
				left -= this->nb_elim-1;
				smaller_groups++;
			}
			while (left) {
				this->loserBracket[tour-1].groups.push_back(this->nb_elim);
				left -= this->nb_elim;
				left_next_round += this->qualif_elim;
			}
			
			if ((left_next_round + smaller_groups * (this->qualif_elim-1)) % 2 == 0 && smaller_groups)
				left_next_round = left_next_round + smaller_groups * (this->qualif_elim-1);
			else
				left_next_round = left_next_round + smaller_groups * this->qualif_elim;
			this->loserBracket[tour-1].qualified = left_next_round;
			this->loserBracket[tour-1].nb_qualif = this->qualif_elim;
		}


		std::cout << std::endl << "Phase " << tour << " avec " << player_left << " joueurs : " << std::endl;
		std::cout << this->loserBracket[tour-1];
		if ((left_next_round + smaller_groups * (this->qualif_elim-1)) % 2 == 0 && smaller_groups)
			std::cout << "Il y aura une personne en moins qualifiée dans les groupes de moins de " << this->nb_elim << " joueurs"<< std::endl;
		else
			std::cout << "Tous les groupes auront le même nombre de qualifiés" << std::endl;
		
		player_left = this->loserBracket[tour-1].qualified;
		tour++;
		smaller_groups = 0;
		left_next_round = 0;

		if ((size_t)a_checker < this->winnerBracket.size() && this->winnerBracket[a_checker].joueurs - this->winnerBracket[a_checker].qualified >= player_left) {
			player_left += this->winnerBracket[a_checker].joueurs - this->winnerBracket[a_checker].qualified;
			std::cout << "Les perdants du winner bracket rejoignent le prochain round, il y aura donc " << player_left << " joueurs au prochain round !" << std::endl;
			a_checker++;
		}
		left = player_left;
	}
	std::cout << "Il ne reste qu'un joueur, qui va donc affronter en finale du loser bracket le perdant de la finale du winner bracket pour une place en grande finale !" << std::endl;
}