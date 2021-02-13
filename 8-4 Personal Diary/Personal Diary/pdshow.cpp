#include "stdafx.h" 
#include "Diary.h"

int main()
{
	vector<Diary> my_diary;
	string date;

	//read from file to memory
	read_to_memory("diary.txt", my_diary);
	sort(my_diary.begin(), my_diary.end(), date_sort);

	FILE *stream;
	freopen_s(&stream, "pdshow_test.txt", "r", stdin);
	getline(cin, date);
	fclose(stdin);
	cin.clear();
	freopen_s(&stream, "pdshow_test.txt", "w", stdout);
	int flag = 0;
	for (int i = 0; i < my_diary.size(); i++)
	{
		if (my_diary[i].GetDate() == date)//show the diary
		{
			cout << my_diary[i].GetDate() << endl;
			for (int j = 0; j < my_diary[i].Size(); j++)
			{
				cout << my_diary[i].GetText(j) << endl;
			}
			cout << "." << endl;
			flag = 1;
		}
	}
	if (flag == 0)
	{
		cout << "Fail! There is no diary of " << date << "." << endl;
	}
	fclose(stdout);
	return 0;
}