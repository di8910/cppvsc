

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

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

struct ListLink
{
	struct ListLink* next;
	struct ListLink* prev;
	char data[0];
};

typedef struct ListLink ListLink;

struct List
{
	int size;
	ListLink* head;
	ListLink* tail;
};

typedef struct List List;

void List_init(List* l)
{
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
}

void List_free(List* l)
{
	ListLink* it;
	ListLink* next;

	for(it=l->head; it; it=next)
	{
		next = it->next;
		free(it->data);
		free(it);
	}

	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
}

void List_pushback(List* l, int size)
{
	ListLink* link = (ListLink*)malloc(sizeof(ListLink)+size);
	link->next = NULL;
	link->prev = l->tail;

	if(!l->head)
		l->head = link;
	
	if(l->tail)
		l->tail->next = link;

	l->tail = link;

	++l->size;
}

void List_erase(List* l, ListLink* link)
{
	if(!link->prev)
		l->head = link->next;
	else
		link->prev->next = link->next;

	if(!link->next)
		l->tail = link->prev;
	else
		link->next->prev = link->prev;

	free(link);

	--l->size;
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

	//Widget* w0;
	List list;
	ListLink* link;

	// Push test
	start = GetTickCount64();
	List_init(&list);
	for(i=0; i<1000*1000*10; i++)
	{
		List_pushback(&list, sizeof(Widget));
		Widget_init((Widget*)list.tail->data);
	}
	passed = GetTickCount64() - start;

	// Iterate and call test
	start2 = GetTickCount64();
	for(link=list.head; link; link=link->next)
	{
		Widget_draw((Widget*)link->data);
	}
	passed2 = GetTickCount64() - start2;

	//Pop test
	start3 = GetTickCount64();
	while(1)
	{
		if(list.head)
			List_erase(&list, list.head);
		else
			break;

		if(list.tail)
			List_erase(&list, list.tail);
		else
			break;
	}
	passed3 = GetTickCount64() - start3;

	printf("C90 with zero-length arrays g=%d passed push,iterate+call,pop in %lld,%lld,%lld ms\r\n", g, passed, passed2, passed3);
	system("pause");

	return 0;
}
