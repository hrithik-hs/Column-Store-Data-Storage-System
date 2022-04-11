#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

class ColumnRecord{
	private:
		char columnName[100];
        char columnType[100];
        bool isPrimary;
        bool unique, notNull;
	public:
		ColumnRecord();
		ColumnRecord(string name, string address,bool primary, bool unique, bool notNull);
		~ColumnRecord();

        void setColName(string name);

        string getColName();
        string getColType();
        int getIsPrimary();
        void togIsPrimary();

        bool getPrimary();
        bool getUnique();
        bool getNotNull();
};