#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <cstring>

using namespace std;

class TableRecord{
	private:
		char name[100];
	public:
		TableRecord();
		TableRecord(string name);
		~TableRecord();

        void setName(string name);
        string getName();
        
};