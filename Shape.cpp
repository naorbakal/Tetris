#include "Shape.h"

void Shape::draw(char ch)const
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color,getSerialObj() % 4 + 10);
	for (const Point&p : body)
		p.draw();
}

void Shape::updateShape(char direction)
{
	switch (direction)
	{
	case eKEYS::DEFAULT:
		for (Point&p : body)
			p.setPoint(p.getx(), p.gety() + 1, true, p.getSerialNumber());
		break;
	case eKEYS::LEFT:
		for (Point&p : body)
			p.setPoint(p.getx() - 1, p.gety(), true, p.getSerialNumber());
		break;
	case eKEYS::RIGHT:
		for (Point&p : body)
			p.setPoint(p.getx() + 1, p.gety(), true, p.getSerialNumber());
		break;
	case eKEYS::ROUTE:
		rotate();
		break;
	default:
		break;
	}

}
