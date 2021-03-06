#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack::stack()
{
	this->top=0;
	this->dane = (int*) malloc(sizeof(int));
}

stack::~stack()
{
	free(this->dane);
}

void stack::clear()
{
	this->top=0;
}

void stack::push(int a)
{
	this->dane = (int*)realloc(this->dane, this->top+1 * sizeof(int));
	assert(this->dane);
	this->dane[this->top++]=a;
}

int stack::pop()
{
	assert(this->top>0);
	return this->dane[--this->top];
}
