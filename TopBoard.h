#pragma once
#include "Point.h"
#include "Board.h"

enum SCORE{SOFT_DROP = 1, HARD_DROP = 2,JOKER_LINE = 50, SINGLE_LINE= 100, DOUBLE_LINE = 300, TRIPLE_LINE = 500, BOMB_EXPLODE = -50};

class TopBoard {
	 //Data members
	int numOfShapes;
	int score;

public:

	void resetTopBoard() {
		numOfShapes = 0; score = 0; printTopBoard();
	}

	int getScore() { return score; }

	TopBoard() : numOfShapes(0), score(0) {
		printTopBoard();
	};

	void updateScore(int addScore) {
		score += addScore;
		printTopBoard();
	}

	void printTopBoard();

	void updateNumOfShapes() { numOfShapes++; }

};

