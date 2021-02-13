#pragma once
#ifndef FRACTION_H
#define FRACTION_H

#include "stdafx.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Fraction
{
private:
	int numerator;//fenzi
	int denominator;//fenmu
public:
	Fraction(void) :numerator(0), denominator(1) {}; //default ctor
	Fraction(int a, int b) :numerator(a), denominator(b) //ctor takes two integers as parameters
	{
		if (denominator == 0)
		{
			throw exception("Denominator should not be zero");
		}
		Simplify();
	}
	static int gcd(int a, int b); //greatest common divisor 
	void Simplify();
	Fraction(const Fraction &p); //copy ctor
	~Fraction() {};

	//arithmetical operators : + - * /
	friend const Fraction operator+(const Fraction &x, const Fraction &y);
	friend const Fraction operator-(const Fraction &x, const Fraction &y);
	friend const Fraction operator*(const Fraction &x, const Fraction &y);
	friend const Fraction operator/(const Fraction &x, const Fraction &y);

	//relational operators : < <= == != >= >
	friend bool operator<(const Fraction &x, const Fraction &y);
	friend bool operator<=(const Fraction &x, const Fraction &y);
	friend bool operator==(const Fraction &x, const Fraction &y);
	friend bool operator!=(const Fraction &x, const Fraction &y);
	friend bool operator>=(const Fraction &x, const Fraction &y);
	friend bool operator>(const Fraction &x, const Fraction &y);

	//type cast to string
	string to_string() const;
	//type cast to double
	double to_double() const;

	//inserter and extractor for streams
	friend istream& operator >> (istream& is, Fraction& obj);
	friend ostream& operator<<(ostream& os, const Fraction& obj);

	//conversion from a finite decimal string like : 1.414
	Fraction(char *str);
	bool strFrac(char *str);
	char getFirstChar(char *str); //return the first non-numeric character in the string
	void getStrBeforeChar(char *str, char c, char *substr); //get the string before the decimal point
	void getStrAfterChar(char *str, char c, char *substr); //get the string after the decimal point
	bool checkErr(char *str); //check if the string contains non-numeric characters
};

#endif // !FRACTION_H

