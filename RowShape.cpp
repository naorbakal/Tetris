#include "RowShape.h"
#include "Board.h"
void RowShape::drawRow()
{
	for (Point&p : body)
		p.draw();
}

void RowShape::move(Board &boardGame, char keyPressed)
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
					flag = false;
			}
			if (flag)
			{
				for (int i = 0; i < SIZE; i++)
				{
					boardGame.turnOffPoint(body[i].getx(), body[i].gety());
					boardGame.turnOnPoint(body[i].getx(), body[i].gety() + 1);
				}
				updateRowShape(keyPressed);
			}
			break;
		case eKEYS::LEFT:
			if (boardGame.isValid(body[0].getx() - 1, body[0].gety()))
			{
				boardGame.turnOffPoint(body[3].getx(), body[3].gety());
				boardGame.turnOnPoint(body[0].getx() - 1, body[0].gety());
				updateRowShape(keyPressed);
			}
			break;
		case eKEYS::RIGHT:
			if (boardGame.isValid(body[3].getx() + 1, body[3].gety()))
			{
				boardGame.turnOffPoint(body[0].getx(), body[0].gety());
				boardGame.turnOnPoint(body[3].getx() + 1, body[3].gety());
				updateRowShape(keyPressed);
			}
			break;
		case eKEYS::ROUTE: /*           *
							  **** -> --*-
										*
										*    */

			if (boardGame.isValid(body[2].getx(), body[2].gety() - 1)
				&& boardGame.isValid(body[2].getx(), body[2].gety() - 2)
				&& boardGame.isValid(body[2].getx(), body[2].gety() + 1))
			{
				// TURN OFF
				boardGame.turnOffPoint(body[0].getx(), body[0].gety());
				boardGame.turnOffPoint(body[1].getx(), body[1].gety());
				boardGame.turnOffPoint(body[3].getx(), body[3].gety());

				// TURN ON
				boardGame.turnOnPoint(body[2].getx(), body[2].gety() - 2);
				boardGame.turnOnPoint(body[2].getx(), body[2].gety() - 1);
				boardGame.turnOnPoint(body[2].getx(), body[2].gety() + 1);

				updateRowShape(keyPressed);
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
				boardGame.turnOnPoint(body[3].getx(), body[3].gety() + 1);
				updateRowShape(keyPressed);
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
					boardGame.turnOnPoint(body[i].getx() - 1, body[i].gety());
				}
				updateRowShape(keyPressed);
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
					boardGame.turnOnPoint(body[i].getx() + 1, body[i].gety());
				}
				updateRowShape(keyPressed);
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
				boardGame.turnOnPoint(body[2].getx() - 2, body[2].gety());
				boardGame.turnOnPoint(body[2].getx() - 1, body[2].gety());
				boardGame.turnOnPoint(body[2].getx() + 1, body[2].gety());

				updateRowShape(keyPressed);
			}


		}
	}
}

void RowShape::updateRowShape(char direction)
{
	switch (direction)
	{
	case eKEYS::DEFAULT:
		for (Point&p : body)
			p.setPoint(p.getx(), p.gety() + 1, true);
		break;
	case eKEYS::LEFT:
		for (Point&p : body)
			p.setPoint((p.getx()) - 1, p.gety(), true);
		break;
	case eKEYS::RIGHT:
		for (Point&p : body)
			p.setPoint((p.getx()) + 1, p.gety(), true);
		break;
	case eKEYS::ROUTE:
		if (adjust == HORIZON)
		{
			body[0].setPoint(body[2].getx(), body[2].gety() - 2, true);
			body[1].setPoint(body[2].getx(), body[2].gety() - 1, true);
			body[3].setPoint(body[2].getx(), body[2].gety() + 1, true);
			this->adjust = VERTICAL;
		}
		else
		{
			body[0].setPoint(body[2].getx() - 2, body[2].gety(), true);
			body[1].setPoint(body[2].getx() - 1, body[2].gety(), true);
			body[3].setPoint(body[2].getx() + 1, body[2].gety(), true);
			this->adjust = HORIZON;
		}
		break;
	}
}

