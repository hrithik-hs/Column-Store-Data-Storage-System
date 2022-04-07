#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
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
		// template <typename T>
		void addElement(string type, int value);

		void setRow(vector<Column *> row);
		vector<Column *> getRow();

		//code
};