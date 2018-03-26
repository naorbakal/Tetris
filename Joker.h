#pragma once

#include "GameObjects.h"
#include "Special.h"

class Joker : public Special {
private:
	Point prevJ;
public:

	//ctor
	Joker();

	//draw 
	void draw(char ch = '#')const override;

	//move
	bool move(Board &boardGame, char keyPressed = DEFAULT) override;

};