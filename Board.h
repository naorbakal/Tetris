#pragma once
#include "TopBoard.h"
#include "Point.h"

enum Sign { J = 'O', B = '@' }; // signs on the board of BOMB & JOKER
enum {ROWS = 15, COLS = 10};

class TopBoard;

class Board {

	Point boardGame[ROWS][COLS];
	TopBoard * topB;

public:
	
	Board(); // ctr 
	~Board() { delete topB; }; // dctr
	enum GameZone { LEFT = 10, RIGHT = 19, TOP = 5, BOTTOM = 16 }; //  only the game zone area
	enum GameFrame { LEFT_F = GameZone::LEFT-1, RIGHT_F = GameZone::RIGHT+1, TOP_F = GameZone::TOP-4, BOTTOM_F = GameZone::BOTTOM+1 }; // the frame of all the board (include menu)
	void printFrame();
	void setBoard();

	void cleanGameOver();

	int getScore();

	bool isFullLine (int curLine, bool & isJokerInLine);

	bool isEmptyLine(int curLine);

	bool cleanLines(int startLine);

	int blowUpSquare(int x, int y);

	bool checkInGameZone(int x, int y)
	{
		return (x >= GameZone::LEFT && x <= GameZone::RIGHT && y >= GameZone::TOP && y <= GameZone::BOTTOM);
	}

	char getSign(int x, int y)
	{
		return boardGame[y - GameZone::TOP + 3][x - GameZone::LEFT].getSign();
	}

	int getSerial(int x, int y)
	{
		return (boardGame[y - GameZone::TOP + 3][x - GameZone::LEFT].getSerialNumber());
	}

	bool isValid(int x, int y)
	{
		return (!(boardGame[y - GameZone::TOP + 3][x - GameZone::LEFT].isBusy()) &&
			(x >= GameZone::LEFT && x <= GameZone::RIGHT && y >= GameZone::TOP && y <= GameZone::BOTTOM) && (boardGame[y - GameZone::TOP + 3][x - GameZone::LEFT].getSerialNumber() != -2));
	}

	void turnOnPoint(int x, int y,int serial=0, char ch = '#')
	{
		boardGame[y - GameZone::TOP + 3][x - GameZone::LEFT].setPoint(x, y, true,serial,ch);
		boardGame[y - GameZone::TOP + 3][x - GameZone::LEFT].draw(ch);
	}
	void turnOffPoint(int x, int y)
	{
		if (x >= GameZone::LEFT && x <= GameZone::RIGHT && y >= GameZone::TOP && y <= GameZone::BOTTOM) {
			boardGame[y - GameZone::TOP + 3][x - GameZone::LEFT].setPoint(x, y, false);
			boardGame[y - GameZone::TOP + 3][x - GameZone::LEFT].draw(' ');
		}
	}

	bool updateBoard();

	void updateScoreBoard(int addScore);

	void updateNumOfShapesBoard();

	// get serial Number and build the shape from the start
	Point * createSerialShape(int serial, int row, int & shapeSize, Point * res);

	void moveShape(Point * arr, int size);

	void hardDownShape(Point * arr, int size);

	void updateRecord(int newRecord)
	{
		gotoxy(Board::RIGHT_F + 5, (Board::BOTTOM_F + Board::TOP_F) / 2 - 3);
		cout << newRecord;
	}

	void printMenu();
};