#ifndef INPUT_HPP
#define INPUT_HPP

#include "../includes.hpp"

class KnockoutStage;

class Input {

public:

	Input(void);
	~Input(void);

	void generateGroupStages(void);
	void printGroupStages(void) const;
	void calculateQualified(void);
	void generateNextStages(void);
	void generateLoserBracket(void);

private:

	int		nb_participants;

	int		nb_poules;
	int		qualif_poules;
	int		qualified;

	int		nb_elim;
	int		qualif_elim;

	bool	loser_bracket;

	std::vector<int> groupStages;
	std::vector<KnockoutStage> winnerBracket;
	std::vector<KnockoutStage> loserBracket;
};

#endif