#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector> 
#include "castle.h"
using namespace std;

void PrintInfo(Room *room)
{
	cout << "Welcome come to the " << room->roomname << ".";
	if (room->ExitNum == 0)
		cout << "There is no exit.";//actually it is impossible
	else {
		cout << "There are " << room->ExitNum << " exits: ";
		string name[4];
		int i = 0;
		if (room->EastExit) name[i++] = "east";
		if (room->WestExit) name[i++] = "west";
		if (room->UpExit) name[i++] = "up";
		if (room->DownExit) name[i++] = "down";
		for (i = 0; i < room->ExitNum; i++)
		{
			cout << name[i];
			if (i == room->ExitNum - 2) cout << " and ";
			else if (i == room->ExitNum - 1) cout << "." << endl;
			else cout << ", ";
		}
	}
	cout << "Enter your command:";
}

Castle::Castle()
{

}

Castle::~Castle() {

	while (!castle.empty()) {
		vector<Room*>::iterator it = castle.end();
		castle.pop_back();
		delete (*it);
	}
}

void Castle::GetMap()
{
	string name;
	ifstream file("MyCastle.txt", ios::in);//data of a 9*9 castle map
	if (!file)//test if the file is opened successfully
	{
		cout << "Error opening file." << endl;
		return;
	}
	for (int i = 0; i < 49; i++)
	{
		Room *room = new Room;
		file >> room->roomname >> room->ExitNum;
		room->EastExit = room->WestExit = room->UpExit = room->DownExit = false;
		room->Monster = room->Princess = false;//initialize
		string direction;
		for (int i = 0; i < room->ExitNum; i++)
		{
			file >> direction;
			if (direction == "east") room->EastExit = true;
			if (direction == "west") room->WestExit = true;
			if (direction == "up") room->UpExit = true;
			if (direction == "down") room->DownExit = true;
		}
		castle.push_back(room);
	}
	file.close();//close the file
}

void Castle::RandPosition()
{
	//a 7*7 castle
	int princess = rand() % 49;
	int monster = rand() % 49;//0-48
	while (princess == monster || princess == 45 || monster == 45) {
		//princess and monster not in the lobby and not the same room
		princess = rand() % 49;
		monster = rand() % 49;
	}
	castle[princess]->Princess = true;
	castle[monster]->Monster = true;
}

void Castle::Run()
{
	//a 7*7 castle
	//initial
	Room *current = castle[45];//lobby:map[3][6]
	int position = 45;

	string go, direct;
	while (1) {
		PrintInfo(current);
		cin >> go >> direct;
		//move
		if (direct == "east") {
			if (!current->EastExit) {
				cout << "The exit doesn't exist!" << endl;
				continue;
			}
			else {
				position++;
				current = castle[position];
			}
		}
		else if (direct == "west") {
			if (!current->WestExit) {
				cout << "The exit doesn't exist!" << endl;
				continue;
			}
			else {
				position--;
				current = castle[position];
			}
		}
		else if (direct == "up") {
			if (!current->UpExit) {
				cout << "The exit doesn't exist!" << endl;
				continue;
			}
			else {
				position -= 7;
				current = castle[position];
			}
		}
		else if (direct == "down") {
			if (!current->DownExit) {
				cout << "The exit doesn't exist!" << endl;
				continue;
			}
			else {
				position += 7;
				current = castle[position];
			}
		}
		//judge
		if (current->Monster) {
			cout << "You are eaten by the monster! Game over!" << endl;
			return;//dead
		}
		if (current->Princess) {
			if (!getPrincess)
				getPrincess = true;
			cout << "You get the princess,run out of the castle quickly!" << endl;
		}
		if (getPrincess && position == 45) {
			cout << "Successfully save the princess! " << "You win!" << endl;
			return;//win
		}
	}
}