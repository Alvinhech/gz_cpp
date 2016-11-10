#include<stdio.h>
#include<stdlib.h>

typedef struct CharNode{
	char * data;
	struct CharNode * next;
}Node_Char, *CharList;

void pushback_ch(CharList * node, char * data){
	CharList p = (CharList)malloc(sizeof(Node_Char));
	CharList r;
	p->data = data;
	p->next = NULL;
	if (*(node) == NULL)
	{
		*(node) = p;
	}
	else{
		r = *node;
		while (r->next != NULL)
			r = r->next;
		r->next = p;
	}
}

int size_ch(CharList node){
	CharList p = node;
	int n = 0;
	while (p != NULL){
		n++;
		p = p->next;
	}
	return n;
}

char * front_ch(CharList list){
	return list->data;
}

void pop_front_ch(CharList *list){
	CharList p = *list;
	*list = (*list)->next;
	free (p);
}