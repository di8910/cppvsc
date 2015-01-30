

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

unsigned int g = 0;

#define WIDGET_BASE		0
#define WIDGET_1		1
#define WIDGET_2		2
#define WIDGET_3		3

struct Widget
{
	int type;
};

typedef struct Widget Widget;

void Widget_base_init(Widget* w)
{
	w->type = WIDGET_BASE;
}
void Widget_1_init(Widget* w)
{
	Widget_base_init(w);
	w->type = WIDGET_1;
}
void Widget_2_init(Widget* w)
{
	Widget_base_init(w);
	w->type = WIDGET_2;
}
void Widget_3_init(Widget* w)
{
	Widget_base_init(w);
	w->type = WIDGET_3;
}

struct Widget1
{
	Widget base;
};

struct Widget2
{
	Widget base;
};

struct Widget3
{
	Widget base;
};

typedef struct Widget1 Widget1;
typedef struct Widget2 Widget2;
typedef struct Widget3 Widget3;

void Widget_draw_base(Widget* w)
{
	g ++;
	g += 2;
}

void Widget_draw_1(Widget1* w)
{
	g ++;
	g += 3;
}

void Widget_draw_2(Widget2* w)
{
	g ++;
	g += 4;
}

void Widget_draw_3(Widget3* w)
{
	g ++;
	g += 5;
}

void Widget_draw(Widget* w)
{
	if(w->type == WIDGET_BASE)
	{
		Widget_draw_base((Widget*)w);
	}
	else if(w->type == WIDGET_1)
	{
		Widget_draw_1((Widget1*)w);
	}
	else if(w->type == WIDGET_2)
	{
		Widget_draw_2((Widget2*)w);
	}
	else if(w->type == WIDGET_3)
	{
		Widget_draw_3((Widget3*)w);
	}
}


int main()
{
	unsigned long long start;
	long long passed;
	int i;

	Widget* w0;
	Widget1* w1;
	Widget2* w2;
	Widget3* w3;

	start = GetTickCount64();
	
	w0 = (Widget*)malloc(sizeof(Widget));
	w1 = (Widget1*)malloc(sizeof(Widget1));
	w2 = (Widget2*)malloc(sizeof(Widget2));
	w3 = (Widget3*)malloc(sizeof(Widget3));
	
	Widget_base_init((Widget*)w0);
	Widget_1_init((Widget*)w1);
	Widget_2_init((Widget*)w2);
	Widget_3_init((Widget*)w3);

	for(i=0; i<1000*1000*1000; i++)
	{
		Widget_draw((Widget*)w0);
		Widget_draw((Widget*)w1);
		Widget_draw((Widget*)w2);
		Widget_draw((Widget*)w3);
	}

	free(w0);
	free(w1);
	free(w2);
	free(w3);

	passed = GetTickCount64() - start;

	printf("C90 g=%d passed in %lld ms\r\n", g, passed);
	system("pause");

	return 0;
}
