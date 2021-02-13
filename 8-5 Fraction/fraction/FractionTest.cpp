#include "stdafx.h"
#include "fraction.h"

int main()
{
	//default ctor
	Fraction a;
	cout << "-------default ctor-------" << endl;
	cout << "a = " << a << endl;
	//ctor takes two integers as parameters
	cout << "-------ctor takes two integers as parameters-------" << endl;
	cout << "Input two integers as parameters:";
	int m, n;
	cin >> m >> n;
	Fraction b(m, n);
	cout << "b = " << b << endl;
	//copy ctor
	cout << "-------copy ctor b to c-------" << endl;
	Fraction c(b);
	cout << "c = " << c << endl;

	//inserter and extractor for streams
	cout << "-------inserter and extractor for streams-------" << endl;
	Fraction x, y;
	cout << "Input two fractions x, y (example:1/3):" << endl;
	cout << "Nonminimalist fractions will be automatically simplified." << endl;
	cin >> x >> y;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;

	//arithmetical operators: + - * /
	cout << "-------arithmetical operators-------" << endl;
	cout << "x + y = " << x + y << endl;
	cout << "x - y = " << x - y << endl;
	cout << "x * y = " << x * y << endl;
	cout << "x / y = " << x / y << endl;

	//relational operators : < <= == != >= >
	cout << "-------relational operators-------" << endl;
	cout << "x < y is " << (x < y) << endl;
	cout << "x <= y is " << (x <= y) << endl;
	cout << "x == y is " << (x == y) << endl;
	cout << "x != y is " << (x != y) << endl;
	cout << "x >= y is " << (x >= y) << endl;
	cout << "x > y is " << (x > y) << endl;

	//type cast to double
	cout << "-------type cast to double-------" << endl;
	double p = x.to_double();
	cout << "x type cast to double p." << endl << "p = " << p << endl;
	//type cast to string
	cout << "-------type cast to string-------" << endl;
	string q = x.to_string();
	cout << "x type cast to string q." << endl << "q = " << q << endl;

	//conversion from a finite decimal string like : 1.414
	cout << "-------conversion from a finite decimal string-------" << endl;
	cout << "Input a finite decimal string like 1.414:" << endl;
	string str;
	cin >> str;
	Fraction d((char*)str.c_str());
	cout << "d = " << d << endl;

	system("pause");
	return 0;
}