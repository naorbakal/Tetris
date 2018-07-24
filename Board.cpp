#include "Board.h"
#include <conio.h>
#include <Windows.h>

Board::Board()
{
	topB = new TopBoard();
	setBoard();
}

void Board::printFrame()
{
	for (int i = 1;i <= COLS; i++) // print frame top & bottom 
	{
		gotoxy(GameFrame::LEFT_F + i, GameFrame::TOP_F);
		cout << "*" << endl;
		gotoxy(GameFrame::LEFT_F + i, GameFrame::BOTTOM_F);
		cout << "*" << endl;
	}

	for (int i = 0;i <= ROWS+1; i++) // print frame left & right
	{
		gotoxy(GameFrame::LEFT_F, GameFrame::TOP_F + i);
		cout << "|" << endl;
		gotoxy(GameFrame::RIGHT_F, GameFrame::TOP_F + i);
		cout << "|" << endl;
	}


}

void Board::setBoard()
{
	printMenu();
	printFrame();
	topB->printTopBoard();
	
	for (int i =0; i < ROWS; i++) 
	{
		for (int j = 0; j < COLS; j++)
		{

			if (i < 2) {
				boardGame[i][j].setPoint(j, i, false, -2, ' ');
				turnOffPoint(j + GameZone::LEFT, i + GameZone::TOP);
			}
			else {
				boardGame[i][j].setPoint(j + GameZone::LEFT, i + GameZone::TOP, false, -1, ' ');
				turnOffPoint(j + GameZone::LEFT, i + GameZone::TOP);
			}
		}
	}

}

void Board::cleanGameOver()
{
	gotoxy(Board::LEFT_F + 2, Board::BOTTOM_F + 1);
	cout << "              " << endl;
	gotoxy(Board::LEFT_F - 2, Board::BOTTOM_F + 3);
	cout << "                                " << endl;
	gotoxy(Board::LEFT_F - 2, Board::BOTTOM_F + 5);
	cout << "                                " << endl;
	topB->resetTopBoard();
	

}

int Board::getScore() {
return topB->getScore();	
}

//check if the line is full
bool Board::isFullLine (int curLine , bool & isJokerInLine)
{
	isJokerInLine = false;

	//check FULL line
	for (const Point&p : boardGame[curLine - Board::TOP + 3])
	{
		if (p.getSign() == Sign::J)
			isJokerInLine = true;
		if (!(p.isBusy()))
			return false;
	}
	// marker the line before crush
	for (Point&p : boardGame[curLine - Board::TOP + 3])
	{
		turnOnPoint(p.getx(), p.gety(),-3,'x');
		Sleep(20);
	}

	// turn OFF line
	for (Point&p : boardGame[curLine - Board::TOP + 3])
	{
		turnOffPoint(p.getx(), p.gety());
	}

	return true;
}

bool Board::isEmptyLine(int curLine)
{
	for (const Point&p : boardGame[curLine - Board::TOP + 3])
	{
		if ((p.isBusy()))
			return false;
	}
	return true;
}

// clean all the full lines
bool Board::cleanLines(int startLine)
{
	int inARow = 0;
	bool res = false;
	bool checkJ;
	for (int i = 0; i < 6 && (startLine - i) >= 5; i++)
	{
		bool fullLine = isFullLine(startLine - i, checkJ);

		if ( fullLine == true && checkJ == false)
		{
			res = true;
			inARow++;
			Sleep(200);
		}
		else if (fullLine == true && checkJ == true)
		{
			topB->updateScore(SCORE::JOKER_LINE);
			res = true;
			inARow = 0;
			Sleep(200);
		}
		else if (inARow != 0)
		{
			if (inARow == 1)
				topB->updateScore(SCORE::SINGLE_LINE);
			else if (inARow == 2)
				topB->updateScore(SCORE::DOUBLE_LINE);
			else
				topB->updateScore(SCORE::TRIPLE_LINE);

			inARow = 0;
		}
				
	}
	return res;
}

//BOMB explode
int Board::blowUpSquare(int x, int y)
{
	int scoreCounter = 0;
	for (int i = 0; i < 3; i++) //blow up 3x3 square.
	{
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 12);

		// count score
		if ((!(*this).isValid(x - 1 + i, y - 1)) && checkInGameZone(x - 1 + i, y - 1))
		{
			turnOnPoint(x - 1 + i, y - 1, -3, '*');
			scoreCounter -= 50;
		}
		if ((!(*this).isValid(x - 1 + i, y)) && checkInGameZone(x - 1 + i, y))
		{
			turnOnPoint(x - 1 + i, y, -3, '*');
			scoreCounter -= 50;
		}
		if ((!(*this).isValid(x - 1 + i, y + 1)) && checkInGameZone(x - 1 + i, y + 1))
		{
			turnOnPoint(x - 1 + i, y +1, -3, '*');
			scoreCounter -= 50;
		}

		Sleep(150);
	
		// turn OFF points relevant
		(*this).turnOffPoint(x - 1 + i, y-1);
		(*this).turnOffPoint(x - 1 + i, y);
		(*this).turnOffPoint(x - 1 + i, y+1);

		


	}

	return scoreCounter; // return the score to be reduced
	
}

bool Board::updateBoard()
{
	Point temp[4];
	int tempSize;
	int row = Board::BOTTOM - 1;
	bool endClean = true;
	while (row != Board::TOP )
	{
		for (Point&p : boardGame[row - Board::TOP + 3])
		{
			if (p.isBusy() == true && isValid(p.getx(), p.gety() + 1))
			{
				createSerialShape(p.getSerialNumber(), row, tempSize, temp);
				moveShape(temp, tempSize);
			}
		}
		row--;
	}

	return endClean;
}

void Board::updateScoreBoard(int addScore)
{
	topB->updateScore(addScore);
	topB->printTopBoard();
}

void Board::updateNumOfShapesBoard()
{
	topB->updateNumOfShapes();
	topB->printTopBoard();
}

Point * Board::createSerialShape(int serial, int row, int & shapeSize, Point * res)
{
	shapeSize = 0;
	for (int i = 0; i<4; i++)
	{
		for (Point&p : boardGame[row - i - Board::TOP + 3])
		{
			if (serial == p.getSerialNumber())
			{
				res[shapeSize].setPoint(p.getx(),p.gety(),true,p.getSerialNumber(),p.getSign());
				shapeSize++;
			}
		}
	}
	return res;

}

void Board::moveShape(Point * arr, int size)
{
	bool flag = false;
	bool flag1 = true;
	for (int i = 0;i < size; i++)
	{
		if (isValid(arr[i].getx(), arr[i].gety() + 1) && arr[i].gety()+1 <= BOTTOM)
			flag = true;
		else
		{
			flag1 = false;
			for (int j = 0; j < size; j++)
			{
				if (j != i)
				{
					if ((arr[i].getx() == arr[j].getx()) && ((arr[i].gety() + 1) == arr[j].gety()))
						flag1 = true;
				}
	
			}

			if (flag1 == false)
				break;
		}
	}

	if (flag==true && flag1==true)
	{
		hardDownShape(arr, size);
		for (int i = 0; i < size; i++)
			arr[i].setPoint(arr[i].getx(), arr[i].gety() + 1, true, arr[i].getSerialNumber(), arr[i].getSign());

		moveShape(arr, size);
	}
}

void Board::hardDownShape(Point * arr , int size)
{
	for (int i = 0; i < size; i++)
	{
		turnOffPoint(arr[i].getx(), arr[i].gety());
		turnOnPoint(arr[i].getx(), arr[i].gety() + 1, arr[i].getSerialNumber(), arr[i].getSign());
	}
}

void Board::printMenu()
{
	gotoxy(Board::RIGHT_F + 5, (Board::BOTTOM_F + Board::TOP_F) / 2 - 5);
	cout << "Your highest score is :";
	gotoxy(Board::RIGHT_F + 5, (Board::BOTTOM_F + Board::TOP_F) / 2);
	cout << "Press (1) to START" << endl;
	gotoxy(Board::RIGHT_F + 5, ((Board::BOTTOM_F + Board::TOP_F) / 2) + 1);
	cout << "Press (2) to PAUSE/RESUME" << endl;
	gotoxy(Board::RIGHT_F + 5, ((Board::BOTTOM_F + Board::TOP_F) / 2) + 2);
	cout << "Press (3) to FAST SPEED" << endl;
	gotoxy(Board::RIGHT_F + 5, ((Board::BOTTOM_F + Board::TOP_F) / 2) + 3);
	cout << "Press (4) to NORMAL SPEED" << endl;
	gotoxy(Board::RIGHT_F + 5, ((Board::BOTTOM_F + Board::TOP_F) / 2) + 4);
	cout << "Press (9) to EXIT" << endl;
}

