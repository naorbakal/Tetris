#include "Square.h"


// ctor 
Square::Square() : Shape()
{
	body[0].setPoint(X_SQ, Y_SQ, true, getSerialObj());
	body[1].setPoint(X_SQ + 1, Y_SQ, true, getSerialObj());
	body[2].setPoint(X_SQ, Y_SQ + 1, true, getSerialObj());
	body[3].setPoint(X_SQ + 1, Y_SQ + 1, true, getSerialObj());
}

// move
bool Square::move(Board & boardGame, char keyPressed)
{
	bool flag = true;
	switch (keyPressed)
	{
	case eKEYS::DEFAULT:
		for (int i = 2; i < 4; i++)
		{
			if (boardGame.isValid(body[i].getx(), body[i].gety() + 1) == false)
			{
				while (boardGame.cleanLines(body[i].gety() + 1))
				{
					boardGame.updateBoard();
				}
				return false;
			}
		}

		for (int i = 0; i < 2; i++)
			boardGame.turnOffPoint(body[i].getx(), body[i].gety());
		for (int i = 2; i < 4; i++)
			boardGame.turnOnPoint(body[i].getx(), body[i].gety() + 1, getSerialObj());

		updateShape(keyPressed);
		break;
	case eKEYS::LEFT:
		if (boardGame.isValid(body[0].getx() - 1, body[0].gety()) &&
			boardGame.isValid(body[2].getx() - 1, body[2].gety()))
		{
			// TURN OFF
			boardGame.turnOffPoint(body[1].getx(), body[1].gety());
			boardGame.turnOffPoint(body[3].getx(), body[3].gety());

			// TURN ON
			boardGame.turnOnPoint(body[0].getx() - 1, body[0].gety(), getSerialObj());
			boardGame.turnOnPoint(body[2].getx() - 1, body[2].gety(), getSerialObj());

			updateShape(keyPressed);
		}

		break;
	case eKEYS::RIGHT:
		if (boardGame.isValid(body[1].getx() + 1, body[1].gety()) &&
			boardGame.isValid(body[3].getx() + 1, body[3].gety()))
		{
			// TURN OFF
			boardGame.turnOffPoint(body[0].getx(), body[0].gety());
			boardGame.turnOffPoint(body[2].getx(), body[2].gety());


			// TURN ON
			boardGame.turnOnPoint(body[1].getx() + 1, body[1].gety(), getSerialObj());
			boardGame.turnOnPoint(body[3].getx() + 1, body[3].gety(), getSerialObj());

			updateShape(keyPressed);
		}
		break;
	case eKEYS::HARD_DOWN:
		while (true)
		{
			if (!(move(boardGame, DEFAULT)))
				break;
			boardGame.updateScoreBoard(2); // hard_drop x2 Distance 
		}
		break;

	}

	return true;
}

