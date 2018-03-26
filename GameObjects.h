#pragma once
#include <iostream>
#include <conio.h>
#include "Board.h"
#include "Point.h"


class GameObjects {

protected:
	int serial;

public:
	
	GameObjects(int _serial) {
		serial = _serial;
	}

	//empty ctr
	GameObjects() {};

	int getSerialObj() const{ return serial; };

	virtual void draw(char ch = '#')const = 0;

	virtual bool move(Board &boardGame, char keyPressed = DEFAULT) = 0;

	virtual void updateShape(char direction) = 0;

	void setSerialNumber(int _serial) {
		serial = _serial;
	}

};