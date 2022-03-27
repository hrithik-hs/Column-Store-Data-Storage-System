#pragma once
#include <bits/stdc++.h>
#include "Column.h"
#include "Data.h"

using namespace std;

class ColumnInteger: public Column{
	private:
		vector<Data<int> *> column;
	public:
		ColumnInteger();
		ColumnInteger(string name);
        ColumnInteger(string name,string address);
		~ColumnInteger();

		void writeFile(string file_source);
		void loadFile(string file_source);

		void insertValue(int value);
		void deleteValue(int index);
		void alterValue(int index, int newValue);
		vector<Data<int> *> getColumn(); // overload functions for differnt types


		// vector<int> filter(less,greater,equal)
};
