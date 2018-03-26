#include "Bomb.h"

void Bomb::draw(char ch) const
{
	body.draw('@');
}

bool Bomb::move(Board & boardGame, char keyPressed)
{
	int addScore;

	switch (keyPressed)
	{
	case eKEYS::DEFAULT:
		if (boardGame.isValid(body.getx(), body.gety() + 1))
		{
			boardGame.turnOffPoint(body.getx(), body.gety());
			boardGame.turnOnPoint(body.getx(), body.gety() + 1, 0, Sign::B);
			body.setPoint(body.getx(), body.gety() + 1, true);
		}
		else if (!(boardGame.checkInGameZone(body.getx(), body.gety() + 1)) && Board::GameZone::BOTTOM >= body.gety() + 1)
			return true;
		else // explode 
		{
			boardGame.turnOffPoint(body.getx(), body.gety());
			addScore = boardGame.blowUpSquare(body.getx(), body.gety() + 1);
			boardGame.updateScoreBoard(addScore);
			boardGame.updateBoard();
			if (boardGame.cleanLines(Board::BOTTOM))
				boardGame.updateBoard();
			return false;
		}
		break;
	case eKEYS::LEFT:
		if (boardGame.isValid(body.getx() - 1, body.gety()))
		{
			boardGame.turnOffPoint(body.getx(), body.gety());
			boardGame.turnOnPoint(body.getx() - 1, body.gety(), 0, Sign::B);
			body.setPoint(body.getx() - 1, body.gety(), true);
		}
		else if (!(boardGame.checkInGameZone(body.getx() - 1, body.gety())) && Board::GameZone::BOTTOM >= body.gety())
			return true;
		else // explode 
		{
			addScore = boardGame.blowUpSquare(body.getx() - 1, body.gety() + 1);
			boardGame.turnOffPoint(body.getx(), body.gety());
			boardGame.updateScoreBoard(addScore);
			boardGame.updateBoard();
			if (boardGame.cleanLines(Board::BOTTOM))
				boardGame.updateBoard();
			return false;
		}
		break;
	case eKEYS::RIGHT:
		if (boardGame.isValid(body.getx() + 1, body.gety()))
		{
			boardGame.turnOffPoint(body.getx(), body.gety());
			boardGame.turnOnPoint(body.getx() + 1, body.gety(), 0, Sign::B);
			body.setPoint(body.getx() + 1, body.gety(), true);
		}
		else if (!(boardGame.checkInGameZone(body.getx() + 1, body.gety())) && Board::GameZone::BOTTOM >= body.gety())
			return true;
		else // explode 
		{
			boardGame.turnOffPoint(body.getx(), body.gety());
			addScore = boardGame.blowUpSquare(body.getx() + 1, body.gety());
			boardGame.updateScoreBoard(addScore);
			boardGame.updateBoard();
			if (boardGame.cleanLines(Board::BOTTOM))
				boardGame.updateBoard();
			return false;
		}
		break;
	default:
		break;
	}

}
