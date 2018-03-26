#pragma once
#include "Point.h"
#include "Board.h"

class RowShape
{
	enum startVal { X = (Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 - 1, Y = Board::GameZone::TOP };
	enum adjust { HORIZON = 0, VERTICAL };
	enum { SIZE = 4 };
	Point body[SIZE];
	bool adjust = HORIZON;

public:
	RowShape()
	{
		for (int i = 0; i < SIZE; i++)
			body[i].setPoint(X + i,Y, true);
		drawRow();
	}

	void drawRow();

	void move(Board &boardGame, char keyPressed=DEFAULT);

	void updateRowShape(char direction);
};