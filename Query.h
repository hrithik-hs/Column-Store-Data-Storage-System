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

struct Condition{
    string columnName;
    string value;
};

struct TableSelect{
    string tableName;
    vector<string>columnNames;
    vector<Condition>conditions;
};

struct DatabaseSelect{
    string databaseName;
    vector<TableSelect>tables;
};

struct TableDelete{
    string tableName;
    vector<Condition>conditions;
};

struct DatabaseDelete{
    string databaseName;
    vector<TableDelete>tables;
};


class Query{
	private:
		string fileName;
        string type; // insert create
        vector<DatabaseInsert> databaseInserts;
        vector<DatabaseCreate> databaseCreates;
        vector<DatabaseSelect> databaseSelects;
        vector<DatabaseDelete> databaseDeletes;

	public:
		Query();
		Query(string fileName,string type);
		~Query();

		// code
        void parseInsertQuery();
        void parseCreateQuery();
        void parseSelectQuery();
        void parseDeleteQuery();

        void parseQuery();

		void setFileName(string fileName);
        void setType(string Type);

		string getFileName();
        string getType();

        vector<DatabaseInsert> getDatabaseInserts();
        vector<DatabaseCreate> getDatabaseCreates();
        vector<DatabaseSelect> getDatabaseSelects();
        vector<DatabaseDelete> getDatabaseDeletes();

};