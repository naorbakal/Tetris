#pragma once

#include "GameObjects.h"

class Special : public GameObjects {
protected:
	//data member
	Point body;
public:

	Special(int _serial) : GameObjects(_serial) {};
	//empty ctor
	Special() : GameObjects() {};

	//draw - Pure virtual
	void draw(char ch = '#') const override = 0;

	//move 
	bool move(Board &boardGame, char keyPressed = DEFAULT) override = 0;

	//update shape
	virtual void updateShape(char direction) {
		return;
	}

};