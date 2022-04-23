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
	public:
		Table();
		Table(string name, string address);
		~Table();

		int loadFile();
		int writeFile();

		void addColumn(string columnName, string type);
		void dropColumn(string columnName);
		void alterColumn(string oldName, string newName); 
		void showTable();

		// void setName(string newName);
		void setPrimaryKey(string columnName);

		Column * getPrimaryKey();
		string getName();
		vector<Column *> getColumns();

		int insertRow(Row *row);
		int selectRows(vector<string> columnNames, vector<pair<string,Data*>> conditions);
		int deleteRows(vector<pair<string,Data*>> conditions);

		void setIsNotNullConstraint(string columnName, bool value);
		void setIsUniqueConstraint(string columnName, bool value);
        int close();
};
