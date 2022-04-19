#include "includes.hpp"

int main(void) {
	Input d;
	d.generateGroupStages();
	d.printGroupStages();
	d.calculateQualified();
	d.generateNextStages();
	d.generateVisualBracket();
}