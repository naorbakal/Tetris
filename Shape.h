#pragma once

#include "GameObjects.h"

enum adjust { HORIZON = 0, VERTICAL = 1, UPSIDE_DOWN = 2, UPSIDE_LEFT = 3};

enum startVal {
	X_SQ = ((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2), Y_SQ = Board::GameZone::TOP,
	X_ROW = (Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 - 1, Y_ROW = Board::GameZone::TOP
};

class Shape : public GameObjects {
protected:
	enum { SIZE = 4 };
	Point body[SIZE];
	int adjust = HORIZON;
public:

	//ctor
	Shape(int _serial) : GameObjects(_serial) {};

	Shape() : GameObjects() {} ; //empty ctor

	virtual void draw(char ch = '#')const;

	//Pure Virtual
	virtual bool move(Board &boardGame, char keyPressed = DEFAULT) = 0;

	virtual void updateShape(char direction);

	//Pure Virtual
	virtual void rotate() = 0;


};