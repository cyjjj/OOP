#include <fstream>
#include <iostream>
#include <cstring> 
#include <cstdlib>
using namespace std;

int main()
{
	int TESTSIZE, PICKSIZE;
	int tIndex, tSize;
	int type;
	string stype;
	string filename;
	cout << "Input # for quit." << endl;
	while(1)
	{
		cout << "Input the filename: ";
	    cin >> filename;
	    if(!strcmp(filename.c_str(), "#")) break;
	    cout << "Input the number of vectors to be created: ";
	    cin >> TESTSIZE;
	    cout << "Input the number of vectors to be resized: ";
	    cin >> PICKSIZE;

	    ofstream fout(filename.c_str(), ios::out);
	    if (!fout)//test if the file is opened successfully
	    {
		    cout << "Error opening file." << endl;
		    return 0;
	    }
	    fout << TESTSIZE << endl;
	    for (int i = 0; i < TESTSIZE; i++)
	    {
		    tSize = (int)((float)rand() / (float)RAND_MAX * 10000);
		    type = (int)((float)rand() / (float)RAND_MAX * 4) + 1;
		    switch (type)
		    {
		    case 1: stype = "int"; break;
		    case 2: stype = "float"; break;
		    case 3: stype = "double"; break;
		    case 4: stype = "class"; break;
		    default: break;
		    }
		    fout << tSize << " " << stype << endl;
	    }
	    for (int i = 0; i < PICKSIZE; i++)
	    {
	    	tIndex = (int)((float)rand() / (float)RAND_MAX * 10000);
		    tSize = (int)((float)rand() / (float)RAND_MAX * 10000);
		    if(i == PICKSIZE - 1) fout << tIndex << " " << tSize;
		    else fout << tIndex << " " << tSize << endl;
	    }
	    fout.close();
	    cout << "Finish successfully!" << endl;
	}
	system("pause");
	return 0;
}
