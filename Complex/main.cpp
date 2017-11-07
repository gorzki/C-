#include <iostream>
using namespace std;
#include "complex.h"


int main()
{
  Complex a(0.0,15),b(1,13),c, d(1,-2);
  c = 10;
  cout << c <<endl;
  c = -a;
  cout << c <<endl;  
  c = a + b;
 	cout << "ww" << c <<endl;
  c = c - Complex(10);
  cout << "aa" << c <<endl;  
  c = 10 - a;
	cout << "xx:" << c <<endl;
  (c +=b) +=10;
	b/=d;
  cout << "zz:" << c <<endl; 
	cout << d.abs() << endl;
	cout << d.conj() << endl;
	cout << d.phase() << endl;
}
