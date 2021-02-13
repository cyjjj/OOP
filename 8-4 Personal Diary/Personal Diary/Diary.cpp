#include "stdafx.h" 
#include "Diary.h"

void Diary::Reset()
{
	text.clear();
}

void Diary::SetText()
{
	string str;
	getline(cin, str);
	while (str != ".")
	{
		text.push_back(str);
		getline(cin, str);
	}
}

void Diary::SetDate(string d)
{
	date = d;
}

void Diary::AddLine(string Line)
{
	text.push_back(Line);
}

string Diary::GetText(VStringSize i)
{
	return text[i];
}

string Diary::GetDate()
{
	return date;
}

VStringSize Diary::Size()
{
	return text.size();
}

//read diaries from file to memory
void read_to_memory(string filename, vector<Diary>& my_diary)
{
	Diary diary;
	string str;
	FILE *stream;
	freopen_s(&stream, filename.c_str(), "r", stdin);
	while (getline(cin, str))
	{
		diary.SetDate(str);
		diary.Reset();
		getline(cin, str);
		while (str != ".")
		{
			diary.AddLine(str);
			getline(cin, str);
		}
		my_diary.push_back(diary);
	}
	fclose(stdin);
	cin.clear();
}

//store diaries from memory to file
void write_to_file(string filename, vector<Diary>& my_diary)
{
	sort(my_diary.begin(), my_diary.end(), date_sort);
	FILE *stream;
	freopen_s(&stream, filename.c_str(), "w", stdout);
	for (int i = 0; i < my_diary.size(); i++)
	{
		cout << my_diary[i].GetDate() << endl;
		for (int j = 0; j < my_diary[i].Size(); j++)
		{
			cout << my_diary[i].GetText(j) << endl;
		}
		cout << "." << endl;
	}
	fclose(stdout);
}

bool date_sort(const Diary &a1, const Diary &a2)
{
	Diary a = a1, b = a2;
	string date1 = a.GetDate();
	string date2 = b.GetDate();
	if(date1.compare(date2) >= 0)//date1>=date2
		return false;
	else return true;
}