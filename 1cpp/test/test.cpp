

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
using namespace std;

unsigned int g = 0;

class Widget
{
public:
	virtual void draw()
	{
		g ++;
		g += 2;
	};
};

class Widget1 : public Widget
{
public:
	virtual void draw()
	{
		g ++;
		g += 3;
	};
};
class Widget2 : public Widget
{
public:
	virtual void draw()
	{
		g ++;
		g += 4;
	};
};
class Widget3 : public Widget
{
public:
	virtual void draw()
	{
		g ++;
		g += 5;
	};
};


int main()
{
	unsigned long long start = GetTickCount64();
	
	Widget* w0 = new Widget;
	Widget* w1 = new Widget1;
	Widget* w2 = new Widget2;
	Widget* w3 = new Widget3;

	for(int i=0; i<1000*1000*1000; i++)
	{
		w0->draw();
		w1->draw();
		w2->draw();
		w3->draw();
	}
	
	delete w0;
	delete w1;
	delete w2;
	delete w3;

	long long passed = GetTickCount64() - start;

	printf("CPP g=%d passed in %lld ms\r\n", g, passed);
	system("pause");

	return 0;
}
