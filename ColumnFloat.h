#pragma once
#include <bits/stdc++.h>
#include "Column.h"
#include "Data.h"

using namespace std;

class ColumnFloat: public Column{
	private:
		vector<Data<float> *> column;
	public:
		ColumnFloat();
		ColumnFloat(string name);
		~ColumnFloat();

		void writeFile();
		void loadFile();

		void insertValue(float value);
		void deleteValue(int index);
		void alterValue(int index, float newValue);
		vector<Data<float> *> getColumn(); // overload function
};