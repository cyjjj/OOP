#include "Student2.h"
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;


int main()
{
	vector<Student> Stu = Stu.read();//read in the data from the file
	Student.StuAverage(Stu);//calculate average score of a student
	CourAMM(Stu);//calculate average,max,min score of a course
	output(Stu);//output the table
	int i;
	cin >> i;//pause
	return 0;
}