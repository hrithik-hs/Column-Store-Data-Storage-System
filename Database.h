#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <set>
#include <fstream>
#include "Table.h"
#include "TableRecord.h"
#include "Row.h"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

using namespace std;

class Database{
	private:
		string name;
		string address;
		vector<Table * > tables;
		vector<TableRecord*> tableRecords;
		map<string,int> tableNames;
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
		void setIsUniqueConstraint(string tableName, string columnName, bool value);

		void setName(string name);
		string getName();
		string getColumnType(string tableName, string columnName);
		vector<Table*> getTables();
		int writeFile();
    	int loadFile();

		int insertRow(string tableName,Row * row);
		int selectRows(string tableName, vector<string> cols, vector<pair<string,Data*>> conditions);
		int deleteRows(string tableName, vector<pair<string,Data*>> conditions);
		
        void close();
        void show();

};