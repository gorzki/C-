#include <stdlib.h>
#define STACKSIZE 20
class stack
{
public:
	int * dane = (int*) malloc (sizeof(int)*STACKSIZE);
	void push(int a);
	int pop();
	void clear();
	stack();
	~stack();
private:
	int top;
};
