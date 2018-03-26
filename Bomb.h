#pragma once
#include "GameObjects.h"
#include "Special.h"

class Bomb : public Special {
	int bla = 0;
public:

	//ctor
	Bomb() : Special() {
		body.setPoint((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP, true, getSerialObj(), Sign::B);
	}

	//draw
	void draw(char ch = '#')const override;
	
	// move
	bool move(Board &boardGame, char keyPressed = DEFAULT) override;


};