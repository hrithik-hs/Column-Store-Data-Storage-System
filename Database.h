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
    void loadFile();

		void insertRow(string tableName,Row * row);
		void selectRows(string tableName, vector<string> cols, vector<pair<string,Data*>> conditions);
		void deleteRows(string tableName, vector<pair<string,Data*>> conditions);
		
		template <typename T1,typename T2>
		void updateRow(string tableName,string columnName,T1 newValue, string comparisionColumn, T2 comparisionValue);
		
		template <typename T>
		void deleteRow(string tableName,string comparisionColumn,T comparisionValue);
        void close();
        void show();

};