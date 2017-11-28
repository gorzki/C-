#include "rcstring.h"

int main()
{
	rcstring a,b,c;
	a="10";
	b="ALA ma kota XxXxX KoTeCzEk xDdD";
	cout << a << " " << b << endl; 
	c=a+b;
	cout << c<<endl; 
	c=a+rcstring(" ")+b;
	cout << c << endl; 
	rcstring d("a");
	cout << d <<endl; 
	d+="ula";
	cout << d << endl; 
	d+="15";
	cout << d << endl; 
	cout << d[3]<<endl; 
	d[3]='b';
	cout << d << endl; 
	d[2]=d[1]=d[0];
	cout << d << endl;
	cout<< b.atoi() << endl;
	cout<< b <<endl;
	try {
		b.toLower();
	}
	catch(string w){
		cout<<"Wyjatek"<<w;
	}

	rcstring v = b;
	cout<< b <<endl;
  cout<< b.Left(5) <<endl;
	cout<< b <<endl <<endl;
	cout<< v <<endl <<endl;
	return 0;
}
