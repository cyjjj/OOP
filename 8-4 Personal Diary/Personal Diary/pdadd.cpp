#include "stdafx.h" 
#include "Diary.h"

int main()
{
	vector<Diary> my_diary;
	Diary diary;
	string date;
	string str;

	//read from file to memory
	read_to_memory("diary.txt", my_diary);

	//read in the new diary
	FILE *stream;
	freopen_s(&stream, "pdadd_test.txt", "r", stdin);
	getline(cin, date);
	if (date.empty())
	{
		printf("The new diary is empty!");
		return 0;
	}
	diary.SetDate(date);
	diary.Reset();
	getline(cin, str);
	while (str != ".")
	{
		diary.AddLine(str);
		getline(cin, str);
	}

	int i;
	for (i = 0; i < my_diary.size(); i++)
		if (my_diary[i].GetDate() == date) break;
	if (i == my_diary.size())//no entity of the same date
		my_diary.push_back(diary);
	else
		my_diary[i] = diary;

	fclose(stdin);
	cin.clear();

	write_to_file("diary.txt", my_diary);
	return 0;
}