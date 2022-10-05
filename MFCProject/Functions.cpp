#include "Functions.h"

char *copystring(const char * string)
{
	int length = stringLength(string);
	char * temp = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		temp[i] = string[i];
	}
	temp[length] = '\0';
	return temp;
}

int stringLength(const char* string)
{
	int count = 0;
	while (*string != '\0')
	{
		count++;
		string++;
	}
	return count;
}

#include "Square.h"
std::ostream & operator<<(ostream & o, Figure2D & d)
{
	static int i = 0;

	Square a;
	if (typeid(d).hash_code() == typeid(a).hash_code() && i < 3) {
		i++;
		Square *copy = (Square*)&d;
		Point Center = copy->SquareCenter();
		o << "Square " << copy->getName() << " with center (" << Center.getX() << ", " << Center.getY() << ") and side = " << copy->GetSide() << endl;
	}
	else {
		o << d.getName() << ": x=" << d.getX() << ", y=" << d.getY() << ", length=" << d.getLength() << ", height=" << d.getHeight();
	}
	return o;
}
