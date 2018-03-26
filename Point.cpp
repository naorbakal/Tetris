#include "Point.h"

using namespace std;

void Point::draw(char ch) const
{
	int colorShape = getSerialNumber() % 6 + 1;
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, colorShape);
	gotoxy(x, y);
	cout << ch << endl;
}
