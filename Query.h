#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include "rapidxml.hpp"
#include <fstream>

using namespace std;
using namespace rapidxml;

struct TableInsert{
    string tableName;
    vector<string>columnNames;
    vector<string>columnValues;
};
struct DatabaseInsert{
    string databaseName;
    vector<TableInsert> tableInserts;
};

struct ColumnCreate{
    string columnName;
    string columnType;
    bool isUniqueConstraint;
    bool isPrimaryConstraint;
};

struct TableCreate{
    string tableName;
    vector<ColumnCreate>columns;
};

struct DatabaseCreate{
    string databaseName;
    vector<TableCreate>tables;
};


class Query{
	private:
		string fileName;
        string type; // insert create
        vector<DatabaseInsert> databaseInserts;
        vector<DatabaseCreate> databaseCreates;

	public:
		Query();
		Query(string fileName,string type);
		~Query();

		// code
        void parseInsertQuery();
        void parseCreateQuery();

        void parseQuery();

		void setFileName(string fileName);
        void setType(string Type);

		string getFileName();
        string getType();

        vector<DatabaseInsert> getDatabaseInserts();
        vector<DatabaseCreate> getDatabaseCreates();
};