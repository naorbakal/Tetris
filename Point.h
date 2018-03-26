#pragma once
#include "gotoxy.h"
#include <iostream>
#include <Windows.h>
using namespace std;

enum eKEYS {LEFT = 'a', RIGHT = 'd', HARD_DOWN = 'x', ROUTE = 'w', JSTOP = 's', DEFAULT = ' ', ESC = 27};

class Point
{
	//Date members
	int x;
	int y;
	bool busy;
	char ch;
	int serialNumber;

public:
	
	//ctor 
	Point(int _x, int _y, bool _busy = false, char _ch = '#') : x(_x) ,y(_y), busy(_busy), ch(_ch) {};

	Point() {}; // empty constructor

	
	void setPoint(int _x, int _y, bool _busy = false, int _serialNumber = 0, char _ch = '#') { x = _x; y = _y; busy = _busy; serialNumber = _serialNumber; ch = _ch; }

	void setSerialNumber(int _serialNumber) { serialNumber = _serialNumber; }

	 char getSign() const{ return ch; };

	 //draw
	 void draw(char ch = '#')const;

	// get data members of the class
	int getx() 	{ return x; }

	int gety() 	{ return y; }
	
	bool isBusy() const { return busy; }

	int getSerialNumber()const { return serialNumber; }

	
};