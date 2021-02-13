#include "stdafx.h" 
#include "Diary.h"

int main()
{
	vector<Diary> my_diary;
	string date;

	//read from file to memory
	read_to_memory("diary.txt", my_diary);

	FILE *stream;
	freopen_s(&stream, "pdremove_test.txt", "r", stdin);
	getline(cin, date);
	fclose(stdin);
	cin.clear();
	freopen_s(&stream, "pdremove_test.txt", "w", stdout);
	int flag = 0;
	for (int i = 0; i < my_diary.size(); i++)
	{
		if (my_diary[i].GetDate() == date)//remove it
		{
			for (int j = i; j < my_diary.size() - 1; j++)
				my_diary[j] = my_diary[j + 1];
			my_diary.pop_back();

			flag = 1;
			cout << "Success!";//success
			fclose(stdout);
			write_to_file("diary.txt", my_diary);
		}
	}
	if (flag == 0)
	{
		cout << "Fail! There is no diary of " << date << "." << endl;//fail
		fclose(stdout);
		return -1;
	}

    return 0;
}

