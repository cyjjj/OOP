#include "stdafx.h" 
#include "Diary.h"
int between(string date, string begin_date, string end_date)
{
	if (date.compare(end_date) <= 0 && date.compare(begin_date) >= 0)
		return 1;
	else
		return 0;
}
int main()
{
	vector<Diary> my_diary;
	string begin_date, end_date;

	//read from file to memory
	read_to_memory("diary.txt", my_diary);
	//sort and write back
	write_to_file("diary.txt", my_diary);

	FILE *stream;
	freopen_s(&stream, "pdlist_test.txt", "r", stdin);
	getline(cin, begin_date);
	getline(cin, end_date);
	fclose(stdin);
	cin.clear();
	if (begin_date.empty() && end_date.empty())
	{
		write_to_file("pdlist_test.txt", my_diary);
		return 0;
	}
	freopen_s(&stream, "pdlist_test.txt", "w", stdout);
	cout << "Diaries from " << begin_date << " to " << end_date << endl;
	int count = 0;
	for (int i = 0; i < my_diary.size(); i++)
	{
		if (between(my_diary[i].GetDate(), begin_date, end_date))
		{
			cout << my_diary[i].GetDate() << endl;
			for (int j = 0; j < my_diary[i].Size(); j++)
			{
				cout << my_diary[i].GetText(j) << endl;
			}
			cout << "." << endl;
			count++;
		}
	}
	if (count == 0)
		cout << "None.";
	fclose(stdout);

	return 0;
}

