#pragma once
#include <bits/stdc++.h>
#include "Column.h"

using namespace std;


class ColumnFloat: public Column{
	private:
		vector<float> column;
	public:
		ColumnFloat();
		ColumnFloat(string name);
		~ColumnFloat();

		void writeFile();
		void loadFile();

		void insertValue(float value);
		void deleteValue(int index);
		void alterValue(int index, float newValue);
		void showValue(); // overload function
};