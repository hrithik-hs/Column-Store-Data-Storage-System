#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <rapidxml.hpp>
#include <fstream>

using namespace std;
using namespace rapidxml;

struct TableInsert{
    string tableName;
    vector<string>columnName;
    vector<string>columnValue;
};
struct DatabaseInsert{
    string dbName;
    vector<TableInsert> tableInserts;
};

struct ColumnCreate{
    string columnName;
    string columnType;
    string constraint;
};

struct TableCreate{
    string TableName;
    vector<ColumnCreate>columns;
};

struct DatabaseCreate{
    string DatabasaeName;
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

};