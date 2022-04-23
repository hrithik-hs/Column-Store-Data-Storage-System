// #include <bits/stdc++.h>
#include <set>
#include <vector>
#include <iostream>

#include "Database.h"
#include "Row.h"
#include "Query.h"

#define tr(X) cerr << X << endl;
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;

using namespace std;

int main(int argc, char *argv[]){
    Query *q = new Query(argv[1], argv[2]);

    if(argv[2] == "insert") {
        vector<DatabaseInsert> vecObject = q->parseInsertQuery();
        for(auto dbInsert : vecObject) {
            string databaseName = dbInsert.dbName;
            Database* database = new Database(databaseName, "./File");
            for(auto tbInsert : dbInsert.tableInserts) {
                Row* row = new Row();
                vector<string> colName = tbInsert.columnName;
                vector<string> colValue = tbInsert.columnValue;
                int len = colName.size();
                Row *row = new Row();
                for(int i = 0; i < len; i ++) {
                    string type = database->getColumnType(tbInsert.tableName, colName[i]);
                    if(type == "int") {
                        int value = stoi(colValue[i]);
                        row->addElement(value);
                    }
                    else if(type == "float") {
                        float value = stof(colValue[i]);
                        row->addElement(value);
                    }
                    else {
                        string value = colValue[i];
                        row->addElement(value);
                    }
                }
                database->insertRow(tbInsert.tableName, row);
            }
        }
    }
    return 0;
}