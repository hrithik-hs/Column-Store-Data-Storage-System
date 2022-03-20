#pragma once
#include <bits/stdc++.h>
#include "Table.h"
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

class Database{
	private:
		string name;
		string address;
		vector<Table * > tables;
	public:
		Database();
		Database(string name, string address);
		Database(string name, vector<Table *> & tables);
		~Database();

		void createTable(string tableName);
		void dropTable(string tableName);
		
		void setName(string name);
		string getName();
		vector<Table*> getTables();
};