#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>

#include "Data.h"
#include "DataInteger.h"
#include "DataFloat.h"
#include "DataString.h"
using namespace std;


class Column{
	private:
		string name;
        string address;
		string type;
		vector<Data *> column;
        bool primary, unique, notNull; 
	public:
		Column();
		Column(string name);
        Column(string name,string address);
        // Column(string name,string address,string type);
        Column(string name,string address,string type,bool primary, bool unique, bool notNull);
		~Column();

		void writeFile();
		void loadFile();
		

		void insertValue(float value);
		void insertValue(int value);
		void insertValue(string value);

		void deleteValue(int index);

		void alterValue(int index, int newValue);
		void alterValue(int index, float newValue);
		void alterValue(int index, string newValue);

        bool checkConstraint(Data * data,vector<bool>flag);

		vector<Data *> getColumn();
		string getType();
		string getName();
		string getAddress();
		
		void setName(string name);
		void setType(string type);
		void setAddress(string address);
        void close();
        void showColumn();
};