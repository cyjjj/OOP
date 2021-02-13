// Student2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

struct Course {
		string name;
		int score;//-1 means not taken
};
struct Student {
	string name;//student name
	vector<Course> courses;//all course chosen
	int coursenum;//number of courses taken
	double average;//average score of all courses
};
class Students {
private:
	vector<Student> Stu;
	int CNUM;//course numbers in total
	vector<int> MAX, MIN;
	vector<double> AVE;
public:
	void read();//read in the data from the file
	void StuAverage();//calculate average score of a student
	void CourAMM();//calculate average,max,min score of a course
	void output();//output the table
};

void Students::read()//read in the data from the file
{
	Student student;
	int num = 0;

	ifstream file("Text.txt", ios::in);
	if (!file)//test if the file is opened successfully
	{
		cout << "Error opening file." << endl;
		return;
	}
	file >> CNUM;
	while (!file.eof())
	{
		num = 0;
		file >> student.name;
		vector<Course> cour;
		for (int i = 0; i < CNUM; i++)
		{
			Course c;
			file >> c.name >> c.score;
			if (c.score != -1)  num++;//-1 means not taken
			cour.push_back(c);
		}
		student.courses = cour;
		student.coursenum = num;
		Stu.push_back(student);
	}
	file.close();//close the file
}
void Students::StuAverage()//calculate average score of a student
{
	int sum;
	for (size_t i = 0; i < Stu.size(); i++)
	{
		if (i >= Stu.size() || i < 0) break;
		sum = 0;
		for (int j = 0; j < CNUM; j++)
		{
			if (Stu[i].courses[j].score != -1)//-1 means not taken
				sum += Stu[i].courses[j].score;
		}
		Stu[i].average = (double)sum / Stu[i].coursenum;
	}
}
void Students::CourAMM()//calculate average,max,min score of a course
{
	int sum, num, max, min;
	for (int i = 0; i < CNUM; i++)
	{
		sum = 0;//sum of scores of all students taken the course
		num = 0;//number of  students taken the course
		max = 0;
		min = 10000;
		for (size_t j = 0; j < Stu.size(); j++)
		{
			if (j >= Stu.size() || j < 0) break;
			if (Stu[j].courses[i].score != -1)//-1 means not taken
			{
				sum += Stu[j].courses[i].score;
				num++;
				if (Stu[j].courses[i].score > max)
					max = Stu[j].courses[i].score;
				if (Stu[j].courses[i].score < min)
					min = Stu[j].courses[i].score;
			}
		}
		double ave = (double)sum / num;
		MAX.push_back(max);
		MIN.push_back(min);
		AVE.push_back(ave);
	}
}
void Students::output()//output the table
{
	//title of the table
	cout << "no\t" << "name\t";
	for (int j = 0; j < CNUM; j++)
	{
		cout << Stu[0].courses[j].name << "\t";
	}
	cout << "average\t" << endl;
	//data of students
	for (size_t i = 0; i < Stu.size(); i++)
	{
		if (i >= Stu.size() || i < 0) break;
		cout << i + 1 << "\t";
		cout << Stu[i].name << "\t";
		for (int j = 0; j < CNUM; j++)
		{
			if (Stu[i].courses[j].score == -1)
				cout << "NULL\t";
			else cout << Stu[i].courses[j].score << "\t";
		}
		cout << setprecision(6) << Stu[i].average << endl;
	}
	//data of courses
	cout << "\t" << "average\t";
	for (int i = 0; i < CNUM; i++)
		cout << setprecision(2) << AVE[i] << "\t";
	cout << endl;
	cout << "\t" << "min\t";
	for (int i = 0; i < CNUM; i++)
		cout << MIN[i] << "\t";
	cout << endl;
	cout << "\t" << "max\t";
	for (int i = 0; i < CNUM; i++)
		cout << MAX[i] << "\t";
	cout << endl;
}

Students S;
int main()
{
	S.read();
	S.StuAverage();
	S.CourAMM();
	S.output();
	int i;
	cin >> i;//pause
	return 0;
}

