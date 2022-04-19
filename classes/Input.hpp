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
	void generateVisualBracket(void);

private:

	int		nb_participants;

	int		nb_poules;
	int		qualif_poules;
	int		qualified;
	bool	same_number;

	int		nb_elim;
	int		qualif_elim;

	bool	loser_bracket;

	std::ofstream fd;

	std::vector<int> groupStages;
	std::vector<KnockoutStage> winnerBracket;
	std::vector<KnockoutStage> loserBracket;

	std::vector<std::string> visual;
	void visualGroupStages(void);
	void visualWinnerBracket(void);
	void visualLoserBracket(void);
	void writeAndClear(void);
};

#endif