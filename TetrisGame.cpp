#include "TetrisGame.h"
#include "Joker.h"
#include "Board.h"
#include "Line.h"
#include "Square.h"
#include "Bomb.h"
#include "Plus.h"
#include "Zshape.h"
#include "Lshape.h"


enum {RAND = 7};

enum Type{Single,SQ,R,P,L,Z};

enum Speed { Fast = 130,Normal = 200 };

enum MenuKeys {START = '1', PAUSE = '2', FAST_SPEED = '3', NORMAL_SPEED = '4', EXIT = '9'};

int static serialNumber = 0;


//           <<<RUN>>>
void TetrisGame::run() {

	GameObjects * object;
	int gameSpeed = Normal;
	char keyPressed = 0;
	int type = -1;
	bool gameOver = false, exitGame = false;
	int bestScore = 0;
	int score = 0;


	while (keyPressed != EXIT && !exitGame)
	{
		hideCursor();
		gameSpeed = Speed::Normal;
		if (_kbhit()) // checks if there is anything in the buffer
		{
			keyPressed = _getch();
			if (keyPressed == START)
			{
				if (gameOver) {
					gameOver = false;
					boardGame.cleanGameOver();
				}
				if (exitGame == EXIT)
					break;
				while (true)
				{
					while (!gameOver && !exitGame)
					{

						if (!checkGameOver(type))
						{
							gameOver = true;
							break;
						}

						serialNumber++;
						object = createNewObject(type);


						while (object->move(this->boardGame))
						{
							char keyPressed;
							if (_kbhit()) // checks if there is anything in the buffer
							{
								keyPressed = _getch(); // take the head of the buffer
								if (keyPressed == EXIT) {
									exitGame = true;
									break;
								}
								else if (keyPressed == NORMAL_SPEED)
									gameSpeed = Speed::Normal;
								else if (keyPressed == FAST_SPEED)
									gameSpeed = Speed::Fast;

								if (keyPressed == PAUSE)
								{
									while (true)
									{
										if (_kbhit()) {

											keyPressed = _getch();
											if (keyPressed == PAUSE)
												break;
										}
									}
								}
								if (!(object->move(this->boardGame, keyPressed)))
									break;
							}
							Sleep(gameSpeed);

						}
						delete object;



					}
					if (gameOver)
					{
						score = boardGame.getScore();
						if (score > bestScore) {
							bestScore = score;
							gotoxy(Board::LEFT_F, Board::BOTTOM_F + 5);
							HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(color, 4);
							cout << "~~NEW RECORD~~";
							SetConsoleTextAttribute(color, 7);
							boardGame.updateRecord(bestScore);
						}
						gotoxy(Board::LEFT_F + 2, Board::BOTTOM_F + 1);
						cout << "GAME OVER" << endl;
						gotoxy(Board::LEFT_F - 2, Board::BOTTOM_F + 3);
						cout << "YOUR SCORE IS : " << score << endl;
						resetGame();
						break;
					}
					if (exitGame) {
						gotoxy(Board::LEFT_F + 2, Board::BOTTOM_F + 5);
						cout << "BYE BYE" << endl;
					}
					break;
				}
			}
		}
	}
}


// Create new Object Game
GameObjects * TetrisGame::createNewObject(int & type)
{
	GameObjects * res;
	int randObj = rand() % RAND;

	switch (randObj)
	{
	case 0:
		res = new Bomb();
		updateStartBoard(B);
		type = B;
		break;
	case 1:
		res = new Joker();
		updateStartBoard(J);
		type = J;
		break;
	case 2:
		res = new Square();
		updateStartBoard(SQ);
		type = SQ;
		break;
	case 3:
		res = new Line();
		updateStartBoard(R);
		type = R;

		break;
	case 4:
		res = new Plus();
		updateStartBoard(P);
		type = P;
		break;
	case 5:
		res = new Zshape();
		updateStartBoard(Z);
		type = Z;
		break;
	case 6:
		res = new Lshape();
		updateStartBoard(L);
		type = L;
		break;

	default:
		res = new Line();
		updateStartBoard(R);
		type = R;
		break;
	}

	res->setSerialNumber(serialNumber);
	return res;
}

// check GAMEOVER
bool TetrisGame::checkGameOver(int typeShape)
{
	switch (typeShape)
	{
	case B:

		if (!(boardGame.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP)))
			return false;
		break;
	case J:
		if (!(boardGame.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP)))
			return false;
		break;
	case Type::SQ:
		if (!(boardGame.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP)) ||
			(!(boardGame.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 + 1, Board::GameZone::TOP))) ||
			(!(boardGame.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP + 1))) ||
				(!(boardGame.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 + 1, Board::GameZone::TOP + 1))))
				return false;
		break;
	case Type::R:
		for (int i = 0; i < 4; i++)
			if (!(boardGame.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 - 1 + i, Board::GameZone::TOP)))
				return false;
		break;
	case Type::P:
		if ( !(boardGame.isValid(X_SQ - 1, Y_SQ + 1)) || (!(boardGame.isValid(X_SQ, Y_SQ)) ||
			(!(boardGame.isValid(X_SQ, Y_SQ + 1)) || (!(boardGame.isValid(X_SQ + 1, Y_SQ + 1))))))
			return false;
		break;
	case Type::Z:
		if (!(boardGame.isValid(X_SQ, Y_SQ)) || (!(boardGame.isValid(X_SQ + 1, Y_SQ)) ||
			(!(boardGame.isValid(X_SQ + 1, Y_SQ)) || (!(boardGame.isValid(X_SQ + 2, Y_SQ + 1))))))
			return false;
		break;
	case Type::L:
		if (!(boardGame.isValid(X_SQ - 1, Y_SQ)) || (!(boardGame.isValid(X_SQ - 1, Y_SQ + 1)) ||
			(!(boardGame.isValid(X_SQ, Y_SQ + 1)) || (!(boardGame.isValid(X_SQ + 1, Y_SQ + 1))))))
			return false;
		break;
	default:
		break;
	}
	return true;
}

// Update Start Board
void TetrisGame::updateStartBoard(int typeShape)
{
	switch (typeShape)
	{
	case Type::Single:
		boardGame.turnOnPoint((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP, serialNumber);
	
		break;
	case Type::SQ:
		boardGame.turnOnPoint((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP,serialNumber);
		boardGame.turnOnPoint((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 + 1, Board::GameZone::TOP,serialNumber);
		boardGame.turnOnPoint((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP + 1,serialNumber);
		boardGame.turnOnPoint((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 + 1, Board::GameZone::TOP + 1,serialNumber);
		break;
	case Type::R:
		for(int i=0; i<4;i++)
			boardGame.turnOnPoint((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 - 1 + i , Board::GameZone::TOP,serialNumber);
		break;
	case Type::P:
		boardGame.turnOnPoint(X_SQ - 1, Y_SQ + 1, serialNumber);
		boardGame.turnOnPoint(X_SQ, Y_SQ, serialNumber);
		boardGame.turnOnPoint(X_SQ, Y_SQ + 1, serialNumber);
		boardGame.turnOnPoint(X_SQ + 1, Y_SQ + 1, serialNumber);
		break;
	case Type::L:
		boardGame.turnOnPoint(X_SQ - 1, Y_SQ, serialNumber);
		boardGame.turnOnPoint(X_SQ - 1, Y_SQ + 1, serialNumber);
		boardGame.turnOnPoint(X_SQ, Y_SQ + 1, serialNumber);
		boardGame.turnOnPoint(X_SQ + 1, Y_SQ + 1, serialNumber);
		break;
	case Type::Z:
		boardGame.turnOnPoint(X_SQ, Y_SQ, serialNumber);
		boardGame.turnOnPoint(X_SQ + 1, Y_SQ, serialNumber);
		boardGame.turnOnPoint(X_SQ + 1, Y_SQ + 1, serialNumber);
		boardGame.turnOnPoint(X_SQ + 2, Y_SQ + 1, serialNumber);
		break;
	default:
		break;
		
	}
	Sleep(120);
}

//Hide Cursor
void TetrisGame::hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);
}
