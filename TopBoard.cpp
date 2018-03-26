#include "TopBoard.h"
#include <Windows.h>

void TopBoard::printTopBoard()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 15);
	gotoxy(Board::LEFT_F + 1, Board::TOP_F + 1);
	cout << "          " << endl;
	gotoxy(Board::LEFT_F + 1, Board::TOP_F + 1);
	cout << "Shapes:" << numOfShapes << endl;
	gotoxy(Board::LEFT_F + 1, Board::TOP_F + 2);
	for (int i = 0; i < 10; i++)
		cout << " ";
	cout << endl;
	gotoxy(Board::LEFT_F + 1, Board::TOP_F + 2);
	cout << "       " << endl;
	gotoxy(Board::LEFT_F + 1, Board::TOP_F + 2);
	cout << "S:" << score << endl;
	gotoxy(Board::LEFT_F + 1, Board::TOP_F + 3);
	for (int i = 0; i < 10; i++)
		cout << "_";
	cout << endl;

}
