#include "rectangle.h"

void main()
{
	rectangle rect;
	int len = 0, wid = 0;
	cout << "Enter length ----> ";
	cin >> len;
	cout << "Enter width ----> ";
	cin >> wid;

	rect.setLength(len);
	rect.setWidth(wid);
	// printing all attributes of the rectangle using all functions
	cout << "Length of rectangle is = " << rect.getLength() << endl;
	cout << "Width of rectangle is = " << rect.getWidth() << endl;
	cout << "Area of rectangle is = " << rect.getArea() << endl;
	cout << "Rectangle is as follow:" << endl;
	rect.draw();
	
	rect.rotateRectangle(); // rectangle rotated
	cout << endl << endl << "Rectangle after rotation is as follow:" << endl << endl;
	cout << "Length of rectangle is = " << rect.getLength() << endl;
	cout << "Width of rectangle is = " << rect.getWidth() << endl;
	cout << "Area of rectangle is = " << rect.getArea() << endl;
	cout << "Rectangle is as follow:" << endl;
	rect.draw();
}