#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "Column.h"
#include "ColumnRecord.h"
#include "Row.h"

using namespace std;

class Table{
	private:
		string name, address;
		vector<Column * > columns;
		Column * primaryKey;
		map<string,int> columnNames;
		vector<ColumnRecord*> ColumnRecords;
		vector<bool> flag;
		// vector<pair<Column *,pair<Table *, Column *>>> foreignKey; 
	public:
		Table();
		Table(string name, string address);
		// Table(string name,vector<Column *> columns);
		// Table(string name,vector<Column *> columns, Column * primaryKey);
		~Table();

		void loadFile();
		void writeFile();

		void addColumn(string columnName, string type);
		void dropColumn(string columnName);
		void alterColumn(string oldName, string newName); 
		void showTable();

		// void setName(string newName);
		void setPrimaryKey(string columnName);

		Column * getPrimaryKey();
		string getName();
		vector<Column *> getColumns();

		void insertRow(Row *row);
		void selectRows(vector<string> columnNames, vector<pair<string,Data*>> conditions);
		void deleteRows(vector<pair<string,Data*>> conditions);

        template <typename T1,typename T2>
		void updateRow(string columnName,T1 newValue, string comparisionColumn, T2 comparisionValue);
		
		void deleteRow(string columnName, int primaryKeyValue);
        void close();
};
