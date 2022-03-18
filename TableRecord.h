#pragma once
#include <bits/stdc++.h>

using namespace std;

class TableRecord{
	private:
		string columnName, columnType;
        int isPrimary;
	public:
		TableRecord();
		TableRecord(string name, string address, int key);
		~TableRecord();

        void setColName(string name);

        string getColName();
        string getColType();
        int getIsPrimary();
        void togIsPrimary();
};