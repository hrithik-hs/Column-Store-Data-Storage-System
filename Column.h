#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <stdio.h>
#include <unistd.h>

#include "Data.h"
#include "DataInteger.h"
#include "DataFloat.h"
#include "DataString.h"
using namespace std;

#define blockSize 2


class Column{
	private:
		string name;
        string address;
		string type;
		bool isUnique;
	public:
		Column();
		Column(string name);
        Column(string name,string address);
        Column(string name,string address,string type);
		~Column();

		void writeFile();
		void loadFile();
		

		void insertValue(float value, int index);
		void insertValue(int value, int index);
		void insertValue(string value, int index);
		void insertValue(string value, int index, vector<string> encoding);

		bool checkConstraints(Data* data);
		bool checkIsUniqueConstraint(int value);
		bool checkIsUniqueConstraint(float value);
		bool checkIsUniqueConstraint(string value);

		string getType();
		string getName();
		string getAddress();
		
		void setName(string name);
		void setType(string type);
		void setAddress(string address);
		void setIsNotNullConstraint(bool value);
		void setIsUniqueConstraint(bool value);
        void close();

		vector<int> selectRows(int block,int value, vector<int> index);
		vector<int> selectRows(int block,float value, vector<int> index);
		vector<int> selectRows(int block,string value, vector<int> index);
		vector<int> selectRows(int block, string value, vector<int> index, vector<string> encoding);
		vector<Data*> selectRows(int block, vector<int> index);
		vector<Data*> selectRows(int block, vector<int> index, vector<string> encoding);
};