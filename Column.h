#pragma once
#include <bits/stdc++.h>
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
	public:
		Column();
		Column(string name);
        Column(string name,string address);
        Column(string name,string address,string type);
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

		vector<Data *> getColumn();
		string getType();
		string getName();
		string getAddress();
		
		void setName(string name);
		void setType(string type);
		void setAddress(string address);
};