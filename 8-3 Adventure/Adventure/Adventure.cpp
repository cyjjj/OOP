// Adventure.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector> 
#include "castle.h"
using namespace std;

Castle cas;
int main()
{
	cas.GetMap();
	cas.RandPosition();
	cas.Run();
	int i;
	cin >> i;//pause
    return 0;
}

