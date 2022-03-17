#pragma once
#include <bits/stdc++.h>
#include "Column.h"
#include "Data.h"

using namespace std;

class ColumnString: public Column{
	private:
		vector<Data<string> *> column;
	public:
		ColumnString();
		ColumnString(string name);
		~ColumnString();

		void writeFile();
		void loadFile();

		void insertValue(string value);
		void deleteValue(int index);
		void alterValue(int index, string newValue);
		vector<Data<string> * > getColumn(); // overload function
};