#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <cstring>


using namespace std;

class TableRecord{
	private:
		char name[100];
        int size;
	public:
		TableRecord();
		TableRecord(string name,int size);
		~TableRecord();

        void setName(string name);
        string getName();
        int getSize();
        void setSize(int size);

};