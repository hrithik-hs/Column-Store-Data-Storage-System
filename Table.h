#pragma once
#include <bits/stdc++.h>
#include "Column.h"

using namespace std;

class Table{
	private:
		string name;
		vector<Column * > columns;
		Column * primaryKey;
		unordered_set<string >columnNames;
		// vector<pair<Column *,pair<Table *, Column *>>> foreignKey; 
	public:
		Table();
		Table(string name);
		// Table(string name,vector<Column *> columns);
		// Table(string name,vector<Column *> columns, Column * primaryKey);
		~Table();

		void dropTable();
		void addColumn(Column * column);
		void dropColumn(string columnName);
		void alterColumn(/*Old column new column new datatype*/); 
		void showTable(vector<Column *>& columns/*, Filters */);

		void setName(string name);
		void setPrimaryKey(Column * column);

		Column * getPrimaryKey();
		string getName();
		vector<Column *> getColumns();    
};