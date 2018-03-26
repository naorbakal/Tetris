#pragma once

#include "GameObjects.h"
#include "Shape.h"

class Line : public Shape {
public:

	//ctor
	Line();

	//move
	bool move(Board &boardGame, char keyPressed = DEFAULT) override;

	//rotate
	void rotate() override;

};


