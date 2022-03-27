#pragma once
#include <bits/stdc++.h>

using namespace std;

class ColumnRecord{
	private:
		string columnName, columnType;
        int isPrimary;
	public:
		ColumnRecord();
		ColumnRecord(string name, string address, int key);
		~ColumnRecord();

        void setColName(string name);

        string getColName();
        string getColType();
        int getIsPrimary();
        void togIsPrimary();
};