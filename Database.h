#pragma once
#include <bits/stdc++.h>
#include "Table.h"
#include "TableRecord.h"
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

class Database{
	private:
		string name;
		string address;
		vector<Table * > tables;
		vector<TableRecord*> tableRecords;
	public:
		Database();
		Database(string name, string address);
		Database(string name, vector<Table *> & tables);
		~Database();

		void createTable(string tableName);
		void dropTable(string tableName);
		void addColumn(string tableName, string columnName, string columnDataType);
		void dropColumn(string tableName, string columnName);
		void alterColumn(string tableName, string columnName, string newName);
		void setPrimaryKey(string tableName, string columnName);
		
		void setName(string name);
		string getName();
		vector<Table*> getTables();
		void writeFile();
};