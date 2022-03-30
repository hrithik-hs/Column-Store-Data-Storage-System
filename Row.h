#pragma once
#include <bits/stdc++.h>
#include "Column.h"

using namespace std;

class Row{
	private:
		vector<Column * >row;
		//code
	public:
		Row();
		Row(vector<Column*>row);
		// Row(const Row &row); //copy constuctor (if needed)
		~Row();

		// void addElement(Column * element);
		template <typename T>
		void addElement(string type, T value);

		void setRow(vector<Column *> row);
		vector<Column *> getRow();

		//code
};