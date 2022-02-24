#pragma once
#include <bits/stdc++.h>

using namespace std;


class Column{
	private:
		string name;
		vector<string> column;
		int type;
	public:
		Column();
		Column(string name, int type);
		~Column();

		void insertValue(string value);
		void deleteValue(int index);
		void alterValue(int index, string newValue);
		void showValue(); // overload function

		string getName();
		int getType();

		void setName(string name);
		void setType(int type);

};