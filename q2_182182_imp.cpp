#include "rectangle.h"

void rectangle::setLength(int l)
{
	if (l >= 0) // length can not be negative
		length = l;
}

void rectangle::setWidth(int w)
{
	if (w >= 0) // as above
		width = w;
}

int rectangle::getLength() const // using const to restric function to modify values
{
	return length;
}

int rectangle::getWidth() const // as above
{
	return width;
}

int rectangle::getArea() const // as above 
{
	return length * width;
}

void rectangle::rotateRectangle()
{
	// swapping algorithm
	length = length + width;
	width = length - width;
	length = length - width;
}

void rectangle::draw() const // as above
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
			cout << "*";
		cout << endl;
	}
}