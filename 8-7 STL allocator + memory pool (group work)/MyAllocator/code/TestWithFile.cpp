// testallocator.cpp : 定义控制台应用程序的入口点。
//

#include "myallocator.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>

#define INT 1
#define FLOAT 2
#define DOUBLE 3
#define CLASS  4

using namespace std;

class vecWrapper
{
public:
	vecWrapper() {
		m_pVec = NULL;
		m_type = INT;
	}
	virtual ~vecWrapper() {
	}
public:
	void setPointer(int type, void *pVec) { m_type = type; m_pVec = pVec; }
	virtual void visit(int index) = 0;
	virtual int size() = 0;
	virtual void resize(int size) = 0;
	virtual bool checkElement(int index, void *value) = 0;
	virtual void setElement(int idex, void *value) = 0;
protected:
	int m_type;
	void *m_pVec;
};

template<class T>
class vecWrapperT : public vecWrapper
{
public:
	vecWrapperT(int type, std::vector<T, MyAllocate<T> > *pVec)
	{
		m_type = type;
		m_pVec = pVec;
	}
	virtual ~vecWrapperT() {
		if (m_pVec)
			delete ((std::vector<T, MyAllocate<T> > *)m_pVec);
	}
public:
	virtual void visit(int index)
	{
		T temp = (*(std::vector<T, MyAllocate<T> > *)m_pVec)[index];
	}
	virtual int size()
	{
		return ((std::vector<T, MyAllocate<T> > *)m_pVec)->size();
	}
	virtual void resize(int size)
	{
		((std::vector<T, MyAllocate<T> > *)m_pVec)->resize(size);
	}
	virtual bool checkElement(int index, void *pValue)
	{
		T temp = (*(std::vector<T, MyAllocate<T> > *)m_pVec)[index];
		if (temp == (*((T *)pValue)))
			return true;
		else
			return false;
	}

	virtual void setElement(int index, void *value)
	{
		(*(std::vector<T, MyAllocate<T> > *)m_pVec)[index] = *((T *)value);
	}
};

class myObject
{
public:
	myObject() : m_X(0), m_Y(0) {}
	myObject(int t1, int t2) :m_X(t1), m_Y(t2) {}
	myObject(const myObject &rhs) { m_X = rhs.m_X; m_Y = rhs.m_Y; }
	~myObject() { /*std::cout << "my object destructor called" << std::endl;*/ }
	bool operator == (const myObject &rhs)
	{
		if ((rhs.m_X == m_X) && (rhs.m_Y == m_Y))
			return true;
		else
			return false;
	}
protected:
	int m_X;
	int m_Y;
};

int main()
{
	int TESTSIZE;
	string filename;
	cout << "Input the filename: ";
	cin >> filename;
	ifstream file(filename, ios::in);
	if (!file)//test if the file is opened successfully
	{
		cout << "Error opening file." << endl;
		return 0;
	}
	file >> TESTSIZE;

	vecWrapper **testVec;
	testVec = new vecWrapper*[TESTSIZE];
	clock_t start, stop;//the start and end of the runtime
	double runtime = 0.0;

	int tIndex, tSize;
	string type;

	//test allocator
	for (int i = 0; i < TESTSIZE; i++)
	{
		file >> tSize >> type;
		if ((!strcmp(type.c_str(), "int")) || (!strcmp(type.c_str(), "Int")))
		{
			start = clock();
			vecWrapperT<int> *pNewVec = new vecWrapperT<int>(INT, new std::vector<int, MyAllocate<int>>(tSize));
			testVec[i] = (vecWrapper *)pNewVec;
			stop = clock();
			runtime += (double)(stop - start) / CLOCKS_PER_SEC;
		}
		else if ((!strcmp(type.c_str(), "float")) || (!strcmp(type.c_str(), "Float")))
		{
			start = clock();
			vecWrapperT<float> *pNewVec = new vecWrapperT<float>(INT, new std::vector<float, MyAllocate<float>>(tSize));
			testVec[i] = (vecWrapper *)pNewVec;
			stop = clock();
			runtime += (double)(stop - start) / CLOCKS_PER_SEC;
		}
		else if ((!strcmp(type.c_str(), "double")) || (!strcmp(type.c_str(), "Double")))
		{
			start = clock();
			vecWrapperT<double> *pNewVec = new vecWrapperT<double>(INT, new std::vector<double, MyAllocate<double>>(tSize));
			testVec[i] = (vecWrapper *)pNewVec;
			stop = clock();
			runtime += (double)(stop - start) / CLOCKS_PER_SEC;
		}
		else if ((!strcmp(type.c_str(), "class")) || (!strcmp(type.c_str(), "Class")))
		{
			start = clock();
			vecWrapperT<myObject> *pNewVec = new vecWrapperT<myObject>(CLASS, new std::vector<myObject, MyAllocate<myObject>>(tSize));
			testVec[i] = (vecWrapper *)pNewVec;
			stop = clock();
			runtime += (double)(stop - start) / CLOCKS_PER_SEC;
		}
	}
	std::cout << "The runtime of " << TESTSIZE << " allocate operations is " << runtime << " s" << endl;

	//test resize
	double runtime2 = 0.0;
	int count = 0;
	while (!file.eof())
	{
		file >> tIndex >> tSize;
		if (tSize == 0) break;
		start = clock();
		testVec[tIndex]->resize(tSize);
		stop = clock();
		runtime2 += (double)(stop - start) / CLOCKS_PER_SEC;
		count++;
	}
	std::cout << "The runtime of " << count << " resize operations is " << runtime2 << " s" << endl;

	file.close();//close the file

	double runtime3 = 0.0;
	for (int i = 0; i < TESTSIZE; i++)
		delete testVec[i];
	std::cout << "circle delete OK!" << endl;
	delete[]testVec;

	std::cout << "delete OK!" << endl;
	stop = clock();
	runtime3 += (double)(stop - start) / CLOCKS_PER_SEC;
	std::cout << "The runtime of delete operations is " << runtime3 << " s" << endl;

	system("pause");
	return 0;
}

