#include "stdafx.h"
#include "vector.h"
#include <string>
using namespace std;

int main()
{
	int capacity;
	cout << "Input the capacity of vector:";
	cin >> capacity;

	cout << "--------Test for Vector<int>---------" << endl;
	Vector<int> x1;
	Vector<int> x2(capacity);
	Vector<int> x3 = x2;
	int element;
	int val;
	cout << "Size of x1 = " << x1.size() << endl;
	cout << "Size of x2 = " << x2.size() << endl;
	cout << "Size of x3 = " << x3.size() << endl;
	cout << "x2 is empty? " << x2.empty() << endl;
	cout << "Push an element into x2:";
	cin >> element;
	x2.push_back(element);
	cout << "x2 is empty? " << x2.empty() << endl;
	cout << "Size of x2 = " << x2.size() << endl;

	cout << "x2[0] = " << x2[0] << endl;
	try {
		cout << "x2.at(0) = " << x2.at(0);
	}
	catch (std::out_of_range & exc)
	{
		std::cerr << exc.what();
	}
	cout << endl;

	cout << "x2[1] = " << x2[1] << endl;
	try {
		cout << "x2.at(1) = " << x2.at(1);
	}
	catch (std::out_of_range & exc)
	{
		std::cerr << exc.what();
	}
	cout << endl;

	x2.clear();
	cout << "Clear x2!" << endl;
	cout << "x2 is empty? " << x2.empty() << endl;

	cout << "--------Test for Vector<char>---------" << endl;
	Vector<char> y1;
	Vector<char> y2(capacity);
	Vector<char> y3 = y2;
	char element2;
	char val2;
	cout << "Size of y1 = " << y1.size() << endl;
	cout << "Size of y2 = " << y2.size() << endl;
	cout << "Size of y3 = " << y3.size() << endl;
	cout << "y2 is empty? " << y2.empty() << endl;
	cout << "Push an element into y2:";
	cin >> element2;
	y2.push_back(element2);
	cout << "y2 is empty? " << y2.empty() << endl;
	cout << "Size of y2 = " << y2.size() << endl;

	cout << "y2[0] = " << y2[0] << endl;
	try {
		cout << "y2.at(0) = " << y2.at(0);
	}
	catch (std::out_of_range & exc)
	{
		std::cerr << exc.what();
	}
	cout << endl;

	cout << "y2[1] = " << y2[1] << endl;
	try {
		cout << "y2.at(1) = " << y2.at(1);
	}
	catch (std::out_of_range & exc)
	{
		std::cerr << exc.what();
	}
	cout << endl;

	y2.clear();
	cout << "Clear y2!" << endl;
	cout << "y2 is empty? " << y2.empty() << endl;

	system("pause");
	return 0;
}