#pragma once
#include "Board.h"
#include "GameObjects.h"
#include "Point.h"
#include <Windows.h>
#include <conio.h>

class TetrisGame {
	
	Board boardGame;
public:

	void resetGame(){
		boardGame.setBoard();
	}
	// <<<RUN>>>
	void run();

	bool checkGameOver(int typeShapea);

	void updateStartBoard(int typeShape);


	void hideCursor();


	GameObjects * createNewObject(int & type);

};