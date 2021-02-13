#include "stdafx.h"
#include "fraction.h"

int Fraction::gcd(int a, int b)
{
	return (b == 0) ? a : gcd(b, a % b);
}

void Fraction::Simplify()
{
	int tmp = abs(gcd(numerator, denominator));
	if (numerator * denominator > 0) //positive
		numerator = abs(numerator / tmp);
	else //negative
		numerator = -abs(numerator / tmp);
	denominator /= tmp;
	denominator = abs(denominator);
}

Fraction::Fraction(const Fraction & p)
{
	numerator = p.numerator;
	denominator = p.denominator;
}

string Fraction::to_string() const
{
	return std::to_string(numerator) + '/' + std::to_string(denominator);
}

double Fraction::to_double() const
{
	return double(numerator) / denominator;
}

Fraction::Fraction(char *str)
{
	Fraction f;
	f.strFrac(str);
	numerator = f.numerator;
	denominator = f.denominator;
}

bool Fraction::strFrac(char * str)
{
	char num[20] = { 0 }, den[20] = { 0 };//number before and after the decimal point

	char op = '.'; //decimal point
	int sign = 1; //record the sign of the fraction

	if (strlen(str) > 31) //too long!
	{
		cout << "The decimal string is too long!" << endl;
		return false;
	}

	op = getFirstChar(str); //check the decimal point
	if (op == '\0')
		op = '.'; //integer
	if (op != '.')
	{
		cout << "Input an illegal character '" << op << "'!" << endl;
		return false;
	}

	getStrBeforeChar(str, op, num);
	getStrAfterChar(str, op, den);

	if (!checkErr(num)) return false;
	if (!checkErr(den)) return false;

	if (strlen(den) > 15)
	{
		cout << "The integral part is too long!" << endl;
		return false;
	}
	if (strlen(num) > 15)
	{
		cout << "The decimal part is too long£¡" << endl;
		return false;
	}

	if (num[0] == '-') sign = -1; //negative
	if (den[0] == '-' || den[0] == '+')
	{
		cout << "Illegal character '+'/'-¡¯after the decimal point£¡" << endl;
		return false;
	}

	denominator = 1;
	for (int i = 0; i < int(strlen(den)); i++)
		denominator *= 10;
	numerator = sign*(abs(atoi(num))*denominator + atoi(den));

	Simplify();

	return true;
}

char Fraction::getFirstChar(char * str)
{
	for (int i = 0; i < int(strlen(str)); i++) {
		if (!isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return str[i];
	}
	return '\0';
}

void Fraction::getStrBeforeChar(char *str, char c, char *substr)
{
	int i;
	if (!substr) return;
	for (i = 0; i < int(strlen(str)); i++) {
		if (str[i] != c)
			substr[i] = str[i];
		else
			break;
	}
	substr[i] = '\0';
}

void Fraction::getStrAfterChar(char *str, char c, char *substr)
{
	int i, j;
	for (i = 0; i < int(strlen(str)) && str[i] != c; i++);
	for (j = i + 1; j < int(strlen(str)); j++)
		substr[j - i - 1] = str[j];
	substr[j - i - 1] = '\0';
}


bool Fraction::checkErr(char *str)
{
	int num = 0;//number of '+' and '-'
	for (int i = 0; i < int(strlen(str)); i++)
	{
		if (!isdigit(str[i])) //if not digit, may be '+'/'-'/'.' or other illegal characters
		{
			if (str[i] == '-' || str[i] == '+')  //check '+'/'-'
			{
				num++;
				if (num > 1)
				{
					cout << "There are more than one '+' or '-'!" << endl;
					return false;
				}
				if (i > 0)
				{
					cout << "¡®+¡¯or¡®-¡¯is at illegal position£¡" << endl;
					return false;
				}
			}
			else if (str[i] == '.') //check decimal point
			{
				cout << "There are more than one decimal point '.'£¡" << endl;
				return false;
			}
			else
			{
				cout << "Input an illegal character '" << str[i] << "¡¯!" << endl;
				return false;
			}
		}
	}
	return true;
}

const Fraction operator+(const Fraction & x, const Fraction & y)
{
	return Fraction(x.numerator*y.denominator + y.numerator*x.denominator, x.denominator*y.denominator);
}

const Fraction operator-(const Fraction & x, const Fraction & y)
{
	return Fraction(x.numerator*y.denominator - y.numerator*x.denominator, x.denominator*y.denominator);
}

const Fraction operator*(const Fraction & x, const Fraction & y)
{
	return Fraction(x.numerator*y.numerator, x.denominator*y.denominator);
}

const Fraction operator/(const Fraction & x, const Fraction & y)
{
	if (y.numerator == 0)
		throw exception("Denominator should not be zero!");
	return Fraction(x.numerator*y.denominator, x.denominator*y.numerator);
}

bool operator<(const Fraction & x, const Fraction & y)
{
	if (x.numerator*y.denominator - y.numerator*x.denominator < 0)
		return true;
	else
		return false;
}

bool operator<=(const Fraction & x, const Fraction & y)
{
	if (x.numerator*y.denominator - y.numerator*x.denominator <= 0)
		return true;
	else
		return false;
}

bool operator==(const Fraction & x, const Fraction & y)
{
	if (x.numerator*y.denominator - y.numerator*x.denominator == 0)
		return true;
	else
		return false;
}

bool operator!=(const Fraction & x, const Fraction & y)
{
	if (x.numerator*y.denominator - y.numerator*x.denominator != 0)
		return true;
	else
		return false;
}

bool operator>=(const Fraction & x, const Fraction & y)
{
	if (x.numerator*y.denominator - y.numerator*x.denominator >= 0)
		return true;
	else
		return false;
}

bool operator>(const Fraction & x, const Fraction & y)
{
	if (x.numerator*y.denominator - y.numerator*x.denominator > 0)
		return true;
	else
		return false;
}

istream & operator >> (istream & is, Fraction & obj)
{
	int nu, de;
	char c;
	is >> nu >> c >> de;
	if (c == '/')
		obj = Fraction(nu, de);
	else cout << "Error!" << endl;
	return is;
}

ostream & operator<<(ostream & os, const Fraction & obj)
{
	if (obj.numerator == 0)
		return os << "0";
	else if (obj.denominator == obj.numerator)
		return os << "1";
	else if (obj.denominator == 1)
		return os << obj.numerator;
	os << obj.numerator << "/" << obj.denominator;
	return os;
}