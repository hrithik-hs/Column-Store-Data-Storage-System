#pragma once
#include <bits/stdc++.h>
#include "Column.h"
#include "ColumnInteger.h"
#include "ColumnFloat.h"
#include "ColumnString.h"
#include "ColumnRecord.h"

using namespace std;

class Table{
	private:
		string name, address;
		vector<Column * > columns;
		Column * primaryKey;
		unordered_set<string >columnNames;
		vector<ColumnRecord*> ColumnRecords;
		// vector<pair<Column *,pair<Table *, Column *>>> foreignKey; 
	public:
		Table();
		Table(string name, string address);
		// Table(string name,vector<Column *> columns);
		// Table(string name,vector<Column *> columns, Column * primaryKey);
		~Table();

		void loadFile();
		void writeFile();

		void dropTable();
		void addColumn(string columnName, string type);
		void dropColumn(string columnName);
		void alterColumn(string oldName, string newName); 
		void showTable(vector<Column *>& columns/*, Filters */);

		// void setName(string newName);
		void setPrimaryKey(string columnName);

		Column * getPrimaryKey();
		string getName();
		vector<Column *> getColumns();    
};
