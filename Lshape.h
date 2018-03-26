#pragma once
#include "Shape.h"

class Lshape : public Shape {
public:
	//ctor
	Lshape();

	//move
	bool move(Board &boardGame, char keyPressed = DEFAULT) override;
	
	//rotate
	void rotate() override;
};