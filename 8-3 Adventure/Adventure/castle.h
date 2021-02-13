#pragma once
#ifndef CASTLE_H
#define CASTLE_H
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector> 
using namespace std;

struct Room {
	string roomname;
	int ExitNum;//number of exits
	bool EastExit, WestExit, UpExit, DownExit;//exists
	bool Monster = false;
	bool Princess = false;
};
void PrintInfo(Room *room);

class Castle {
private:
	vector<Room*> castle;
	bool getPrincess = false;
public:
	Castle();
	~Castle();
	void GetMap();
	void RandPosition();
	void Run();
};
#endif // !CASTLE_H

