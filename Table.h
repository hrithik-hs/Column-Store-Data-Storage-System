#pragma once
#include <bits/stdc++.h>
#include "Column.h"

using namespace std;

class Table{
	private:
		string name;
		vector<Column * > columns;
		Column * primaryKey;
		// vector<pair<Column *,pair<Table *, Column *>>> foreignKey; 
	public:
		Table();
		Table(string name);
		Table(string column,vector<Column *> & columns);
		Table(string column,vector<Column *> & columns, Column * primaryKey);
		~Table();

		void dropTable();
		void addColumn(Column * column);
		void dropColumn(Column * column);
		void alterColumn(/*Old column new column new datatype*/); 
		void showTable(vector<Column *>& columns/*, Filters */);

		void setName(string name);
		void setPrimaryKey(Column * column);

		Column * getPrimaryKey();
		string getName();
		vector<Column *> getColumns();    
};