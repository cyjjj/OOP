// Student1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAXNUM = 10;//max number of students
const int COUNUM = 3;//number of courses
struct Student {
	string name;
	int scores[COUNUM];
};

int main()
{
	int i = 0, stunum = 0;
	Student stu[MAXNUM];

	//read in data from the file
	ifstream file("Text.txt", ios::in);
	if (!file)
	{
		cout << "Error opening file." << endl;
		return 0;
	}//test if the file is opened successfully
	while (!file.eof())
	{
		file >> stu[i].name >> stu[i].scores[0] >> stu[i].scores[1] >> stu[i].scores[2];
		i++;
		stunum++;
	}
	file.close();//close the file

	//calculate max, min and average scores
	double average[MAXNUM], caverage[COUNUM];//average scores of each student and each course
	int min[COUNUM], max[COUNUM];//min and max score of each course
	int csum[COUNUM], sum = 0;//sum of each course and each student
	int j;
	for (i = 0; i < MAXNUM; i++)
		average[i] = 0.0;
	for (i = 0; i < COUNUM; i++)
	{
		min[i] = 100;
		max[i] = 0;
		csum[i] = 0.0;
	}//initial

	for (i = 0; i < stunum; i++)
	{
		sum = 0;
		for (j = 0; j < COUNUM; j++)
		{
			sum += stu[i].scores[j];
			csum[j] += stu[i].scores[j];
			if (stu[i].scores[j] > max[j])
				max[j] = stu[i].scores[j];
			if (stu[i].scores[j] < min[j])
				min[j] = stu[i].scores[j];
		}
		average[i] = (double)sum / COUNUM;
	}
	for (j = 0; j < COUNUM; j++)
		caverage[j] = (double)csum[j] / stunum;

	//output the table
	cout << "no\t" << "name\t" << "score1\t" << "score2\t" << "score3\t" << "average\t" << endl;
	for (i = 0; i < stunum; i++)
	{
		cout << i + 1 << "\t";
		cout << stu[i].name << "\t";
		for (j = 0; j < COUNUM; j++)
			cout << stu[i].scores[j] << "\t";
		cout << setprecision(6) << average[i] << endl;
	}

	cout << "\t" << "average\t";
	for (j = 0; j < COUNUM; j++)
		cout << setprecision(2) << caverage[j] << "\t";
	cout << endl;

	cout << "\t" << "min\t";
	for (j = 0; j < COUNUM; j++)
		cout << min[j] << "\t";
	cout << endl;

	cout << "\t" << "max\t";
	for (j = 0; j < COUNUM; j++)
		cout << max[j] << "\t";
	cout << endl;

	int k;
	cin >> k;
	return 0;
}

