#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Zshape : public Shape {
public:

	//ctor
	Zshape();

	//move
	bool move(Board &boardGame, char keyPressed = DEFAULT) override;

	//rotate
	void rotate() override;
};