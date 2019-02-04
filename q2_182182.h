#include<iostream>
using namespace std;

class rectangle
{
private:
	int length;
	int width;

public:
	void setLength(int l);
	void setWidth(int w);
	int getLength() const;
	int getWidth() const;
	int getArea() const;
	void rotateRectangle();
	void draw() const;
};