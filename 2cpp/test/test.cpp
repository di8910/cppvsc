

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <list>

unsigned int g = 0;

#define WIDGET_BASE		0

struct Widget
{
	int type;
};

typedef struct Widget Widget;

void Widget_init(Widget* w)
{
	w->type = WIDGET_BASE;
}

void Widget_draw(Widget* w)
{
	g ++;
	g += 2;
}

int main()
{
	unsigned long long start;
	unsigned long long start2;
	unsigned long long start3;
	long long passed;
	long long passed2;
	long long passed3;
	int i;
	
	std::list<Widget> list;

	// Push test
	start = GetTickCount64();
	for(i=0; i<1000*1000*10; i++)
	{
		Widget w0;
		Widget_init(&w0);
		list.push_back(w0);
	}
	passed = GetTickCount64() - start;

	// Iterate and call test
	start2 = GetTickCount64();
	for(auto wit=list.begin(); wit!=list.end(); wit++)
	{
		Widget_draw((Widget*)&*wit);
	}
	passed2 = GetTickCount64() - start2;

	//Pop test
	start3 = GetTickCount64();
	while(1)
	{
		if(list.size() > 0)
			list.erase( list.begin() );
		else
			break;
		
		if(list.size() > 0)
			list.erase( --list.end() );
		else
			break;
	}
	passed3 = GetTickCount64() - start3;

	printf("CPP g=%d passed push,iterate+call,pop in %lld,%lld,%lld ms\r\n", g, passed, passed2, passed3);
	system("pause");

	return 0;
}
