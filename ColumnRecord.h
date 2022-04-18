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
        int isPrimary;
        bool isEnum;
        int difVal;
        char encoding[10][100];
	public:
		ColumnRecord();
		ColumnRecord(string name, string address, int key);
		~ColumnRecord();

        void setColName(string name);

        string getColName();
        string getColType();
        int getIsPrimary();
        vector<string> getEncoding();
        void setEncoding(vector<string> _encoding);
        void togIsPrimary();
};