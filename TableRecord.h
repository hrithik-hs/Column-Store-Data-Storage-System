#pragma once
#include <bits/stdc++.h>

using namespace std;

class TableRecord{
	private:
		string name;
	public:
		TableRecord();
		TableRecord(string name);
		~TableRecord();

        void setName(string name);
        string getName(string name);
};