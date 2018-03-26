#pragma once
#include "GameObjects.h"
#include "Shape.h"


class Plus : public Shape {
public:

	//ctor
	Plus();

	//move
	bool move(Board &boardGame, char keyPressed = DEFAULT) override;

	//rotate
	void rotate() override;

};