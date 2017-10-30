#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack::stack()
{
	this->top=0;
}

stack::~stack()
{
}

void stack::clear()
{
	this->top=0;
}

void stack::push(int a)
{
	assert(this->top<STACKSIZE);
	this->dane[this->top++]=a;
}

int stack::pop()
{
	assert(this->top>0);
	return this->dane[--this->top];
}
