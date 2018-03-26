#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Square : public Shape {
public:
	Square(); // ctor

	//move
	bool move(Board &boardGame, char keyPressed = DEFAULT) override;

	//rotate
	void rotate() override { 
		return;
	}

};