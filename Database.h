#pragma once
#include <bits/stdc++.h>
#include "Table.h"

using namespace std;

class Database{
	private:
		string name;
		vector<Table * > tables;
	public:
		Database();
		Database(string name);
		Database(string name, vector<Table *> & tables);
		~Database();

		void createTable(Table * table);
		void dropTable(Table * table);
		
		void setName();
		string getName();
		string getTables();
};