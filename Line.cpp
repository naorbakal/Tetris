#include "Line.h"


//ctor
Line::Line() : Shape()
{
	for (int i = 0; i < SIZE; i++)
		body[i].setPoint(X_ROW + i, Y_ROW, true, getSerialObj());
}

//move Line
bool Line::move(Board & boardGame, char keyPressed)
{
	bool flag = true;

	switch (adjust)
	{
	case HORIZON: // ------------------------------------- HORIZONTAL -------------------------------------
		switch (keyPressed)
		{
		case eKEYS::DEFAULT:
			for (int i = 0; i < SIZE; i++)
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
			for (int i = 0; i < SIZE; i++)
			{
				boardGame.turnOffPoint(body[i].getx(), body[i].gety());
				boardGame.turnOnPoint(body[i].getx(), body[i].gety() + 1,getSerialObj());
			}
			updateShape(keyPressed);

			break;
		case eKEYS::LEFT:
			if (boardGame.isValid(body[0].getx() - 1, body[0].gety()))
			{
				boardGame.turnOffPoint(body[3].getx(), body[3].gety());
				boardGame.turnOnPoint(body[0].getx() - 1, body[0].gety(), getSerialObj());
				updateShape(keyPressed);
			}
			break;
		case eKEYS::RIGHT:
			if (boardGame.isValid(body[3].getx() + 1, body[3].gety()))
			{
				boardGame.turnOffPoint(body[0].getx(), body[0].gety());
				boardGame.turnOnPoint(body[3].getx() + 1, body[3].gety(), getSerialObj());
				updateShape(keyPressed);
			}
			break;
		case eKEYS::ROUTE:


			if (boardGame.isValid(body[2].getx(), body[2].gety() - 1)
				&& boardGame.isValid(body[2].getx(), body[2].gety() - 2)
				&& boardGame.isValid(body[2].getx(), body[2].gety() + 1))
			{
				// TURN OFF
				boardGame.turnOffPoint(body[0].getx(), body[0].gety());
				boardGame.turnOffPoint(body[1].getx(), body[1].gety());
				boardGame.turnOffPoint(body[3].getx(), body[3].gety());

				// TURN ON
				boardGame.turnOnPoint(body[2].getx(), body[2].gety() - 2, getSerialObj());
				boardGame.turnOnPoint(body[2].getx(), body[2].gety() - 1, getSerialObj());
				boardGame.turnOnPoint(body[2].getx(), body[2].gety() + 1, getSerialObj());

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
		break;
	case VERTICAL: // --------------------------------------- VERTICAL -----------------------------------------
		switch (keyPressed)
		{
		case eKEYS::DEFAULT:
			if (boardGame.isValid(body[3].getx(), body[3].gety() + 1))
			{
				boardGame.turnOffPoint(body[0].getx(), body[0].gety());
				boardGame.turnOnPoint(body[3].getx(), body[3].gety() + 1, getSerialObj());
				updateShape(keyPressed);
			}
			else {
				while (boardGame.cleanLines(body[3].gety() + 1))
				{
					boardGame.updateBoard();
				}
				return false;
			}
			break;
		case eKEYS::LEFT:
			for (int i = 0; i < SIZE; i++)
			{
				if (boardGame.isValid(body[i].getx() - 1, body[i].gety()) == false)
					flag = false;
			}
			if (flag)
			{
				for (int i = 0; i < SIZE; i++)
				{
					boardGame.turnOffPoint(body[i].getx(), body[i].gety());
					boardGame.turnOnPoint(body[i].getx() - 1, body[i].gety(), getSerialObj());
				}
				updateShape(keyPressed);
			}
			break;

		case eKEYS::RIGHT:
			for (int i = 0; i < SIZE; i++)
			{
				if (boardGame.isValid(body[i].getx() + 1, body[i].gety()) == false)
					flag = false;
			}
			if (flag)
			{
				for (int i = 0; i < SIZE; i++)
				{
					boardGame.turnOffPoint(body[i].getx(), body[i].gety());
					boardGame.turnOnPoint(body[i].getx() + 1, body[i].gety(), getSerialObj());
				}
				updateShape(keyPressed);
			}
			break;
		case eKEYS::ROUTE:
			if (boardGame.isValid(body[2].getx() - 2, body[2].gety())
				&& boardGame.isValid(body[2].getx() - 1, body[2].gety())
				&& boardGame.isValid(body[2].getx() + 1, body[2].gety()))

			{
				// TURN OFF
				boardGame.turnOffPoint(body[0].getx(), body[0].gety());
				boardGame.turnOffPoint(body[1].getx(), body[1].gety());
				boardGame.turnOffPoint(body[3].getx(), body[3].gety());

				// TURN ON
				boardGame.turnOnPoint(body[2].getx() - 2, body[2].gety(), getSerialObj());
				boardGame.turnOnPoint(body[2].getx() - 1, body[2].gety(), getSerialObj());
				boardGame.turnOnPoint(body[2].getx() + 1, body[2].gety(), getSerialObj());

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

	default:
		break;
	}
	return true;
}


//rotate Line
void Line::rotate()
{
	if (adjust == HORIZON)
	{
		body[0].setPoint(body[2].getx(), body[2].gety() - 2, true, getSerialObj());
		body[1].setPoint(body[2].getx(), body[2].gety() - 1, true, getSerialObj());
		body[3].setPoint(body[2].getx(), body[2].gety() + 1, true, getSerialObj());
		this->adjust = VERTICAL;
	}
	else
	{
		body[0].setPoint(body[2].getx() - 2, body[2].gety(), true, getSerialObj());
		body[1].setPoint(body[2].getx() - 1, body[2].gety(), true, getSerialObj());
		body[3].setPoint(body[2].getx() + 1, body[2].gety(), true, getSerialObj());
		this->adjust = HORIZON;
	}
}

