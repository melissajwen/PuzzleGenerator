#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <math.h>
#include <algorithm>
#include "Puzzle.h"
#include "Timer.h"


class PuzzleGenerator{
public:
	PuzzleGenerator(int nRows, int nColumns, int minVal, int maxVal);
	Puzzle GeneratePuzzle(); 
	Puzzle SimulatedAnnealing(Puzzle puzzle);
	
private:
	int nRows, nColumns, minVal, maxVal;
	Timer timer;
	double maxtime;
};
