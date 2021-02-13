#pragma once

#ifndef STUDENT2_H
#define STUDENT2_H

class Student {
private:
	string name;//student name
	struct Course {
		string name;
		int score;//-1 means not taken
	};//name and score for each course
	vector<Course> courses;//all course chosen
	int coursenum;//number of courses taken
	double average;//average score of all courses

public:
	vector<Student> read();//read in the data from the file
	void StuAverage(vector<Student> Stu);//calculate average score of a student
	void CourAMM(vector<Student> Stu);//calculate average,max,min score of a course
	void output(vector<Student> Stu);//output the table
};

#endif