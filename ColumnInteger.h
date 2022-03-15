#pragma once
#include <bits/stdc++.h>
#include "Column.h"

using namespace std;

class ColumnInteger: public Column{
	private:
		vector<int> column;
	public:
		ColumnInteger();
		ColumnInteger(string name);
		~ColumnInteger();

		void writeFile();
		void loadFile();

		void insertValue(int value);
		void deleteValue(int index);
		void alterValue(int index, int newValue);
		void showValue(); // overload functions for differnt types


		// vector<int> filter(less,greater,equal)
};