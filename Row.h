#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>

#include "Data.h"
#include "DataInteger.h"
#include "DataFloat.h"
#include "DataString.h"

using namespace std;
#define endl "\n"

class Row{
	private:
		vector<Data * >row;
		//code
	public:
		Row();
		Row(vector<Data*>row);
		// Row(const Row &row); //copy constuctor (if needed)
		~Row();

		void addElement(int value);
		void addElement(float value);
		void addElement(string value);


		void setRow(vector<Data *> row);
		vector<Data *> getRow();

		//code
};