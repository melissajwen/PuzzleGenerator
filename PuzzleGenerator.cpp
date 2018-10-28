#include "PuzzleGenerator.h"
#include <limits>

using namespace std;

static double INITIAL_TEMP = 100.0;
static double EPSILON = 0.01;
static double ALPHA = 0.999;

PuzzleGenerator::PuzzleGenerator(int _nRows, int _nColumns, int _minVal, int _maxVal)
	:nRows(_nRows), nColumns(_nColumns), minVal(_minVal), maxVal(_maxVal)
{}

Puzzle PuzzleGenerator::GeneratePuzzle()
{
	timer.StartTimer();
	maxtime = 59.0;	// To make sure we don't exceed a minute
	
	// Initialize puzzle
	Puzzle init(nRows, nColumns, minVal, maxVal);
	Puzzle best = SimulatedAnnealing(init);

	while (timer.GetElapsedTime() < maxtime) {
		Puzzle n(nRows, nColumns, minVal, maxVal);
		Puzzle p = SimulatedAnnealing(n);
		if (p.GetValue() > best.GetValue()) {
			best = p;
		}
	}

	return best;
}

Puzzle PuzzleGenerator::SimulatedAnnealing(Puzzle puzzle) {
	Puzzle p = puzzle;

	for (double t = INITIAL_TEMP; t > EPSILON; t *= ALPHA) { 
		Puzzle successor = p.GetRandomSuccessor();
		if (successor.GetValue() > p.GetValue()) {
			p = successor;
		}
		else {
			int delta = successor.GetValue() - p.GetValue();
			double prob = exp(delta / t);
			double r = (((double) rand()) / RAND_MAX);

			if (r < prob) {
				p = successor;
			}
		}
	}

	return p;
}