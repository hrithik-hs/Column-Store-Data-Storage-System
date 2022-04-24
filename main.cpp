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

set<string> databaseNames;

void loadRoot(){
    string file_source="./File/root";
    FILE* readptr = fopen(&file_source[0], "r");
    if(!readptr) {
        cout << "[ M- ] [ Load root ] Cannot open root file." << endl;
    }
    while(1){
        char readData[100];
		int sz = fread(&readData, sizeof(readData), 1, readptr);
        if(!sz) break;
        databaseNames.insert(string(readData));
    }
    fclose(readptr);
}

void writeRoot(){
    string file_source="./File/root";
    FILE* writeptr = fopen(&file_source[0], "w");
    if(!writeptr) {
        cout << "[ M- ] [ Write root ] Cannot open root file." << endl;
    }
    for(auto st:databaseNames){
        char writeData[100];
        strcpy(writeData,st.c_str());
        fwrite(&writeData,sizeof(writeData),1,writeptr);
    }
    fclose(writeptr);
}

int main(int argc, char *argv[]){
    loadRoot();

    Query *q = new Query(argv[1], argv[2]);
    
    if(string(argv[2]) == "create") {
        vector<DatabaseCreate> vecObject = q->getDatabaseCreates();        for(auto dbCreate: vecObject){
            string databaseName = dbCreate.databaseName;
            if(databaseNames.find(databaseName)==databaseNames.end()){
                string address = "./File/"+databaseName+".db";
                string folderAddress = "./File/"+databaseName;
                fs::create_directories(folderAddress);
                ofstream outfile(address);
                databaseNames.insert(databaseName);
            }
            Database* database = new Database(databaseName, "./File");
            for(auto tbCreate: dbCreate.tables){
                string tableName = tbCreate.tableName;
                database->createTable(tbCreate.tableName);
                for(auto colCreate: tbCreate.columns){
                    database->addColumn(tableName,colCreate.columnName,colCreate.columnType);
                    if(colCreate.isPrimaryConstraint) database->setPrimaryKey(tableName,colCreate.columnName);
                    else if(colCreate.isUniqueConstraint) database->setIsUniqueConstraint(tableName,colCreate.columnName,true);
                }
            }
            database->close();
        }
    }
    
    else if(string(argv[2]) == "insert") {
        vector<DatabaseInsert> vecObject = q->getDatabaseInserts();
        for(auto dbInsert : vecObject) {
            string databaseName = dbInsert.databaseName;
            if(databaseNames.find(databaseName)==databaseNames.end()) continue;
            Database* database = new Database(databaseName, "./File");
            for(auto tbInsert : dbInsert.tableInserts) {
                vector<string> colName = tbInsert.columnNames;
                vector<string> colValue = tbInsert.columnValues;
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

    else if(string(argv[2]) == "select") {
        vector<DatabaseSelect> vecObject = q->getDatabaseSelects();
        for(auto dbSelect : vecObject) {
            string databaseName = dbSelect.databaseName;
            if(databaseNames.find(databaseName)==databaseNames.end()) continue;
            Database* database = new Database(databaseName, "./File");
            for(auto tbSelect : dbSelect.tables) {
                string tableName = tbSelect.tableName;
                vector<string> colName = tbSelect.columnNames;
                vector<Condition> conditions = tbSelect.conditions;
                vector<pair<string,Data*>> inpCond;
                for(auto cond:conditions){
                    string type = database->getColumnType(tableName,cond.columnName);
                    if(type == "int"){
                        DataInteger* data = new DataInteger(stoi(cond.value));
                        inpCond.push_back(make_pair(cond.columnName,data));
                    }
                    else if(type == "float"){
                        DataFloat* data = new DataFloat(stof(cond.value));
                        inpCond.push_back(make_pair(cond.columnName,data));
                    }
                    else{
                        DataString* data = new DataString(cond.value);
                        inpCond.push_back(make_pair(cond.columnName,data));
                    }
                }
                database->selectRows(tableName,colName,inpCond);
            }
        }
    }

    else if(string(argv[2]) == "delete") {
        vector<DatabaseDelete> vecObject = q->getDatabaseDeletes();
        for(auto dbDelete : vecObject) {
            string databaseName = dbDelete.databaseName;
            if(databaseNames.find(databaseName)==databaseNames.end()) continue;
            Database* database = new Database(databaseName, "./File");
            for(auto tbDelete : dbDelete.tables) {
                string tableName = tbDelete.tableName;
                vector<Condition> conditions = tbDelete.conditions;
                vector<pair<string,Data*>> inpCond;
                for(auto cond:conditions){
                    string type = database->getColumnType(tableName,cond.columnName);
                    if(type == "int"){
                        DataInteger* data = new DataInteger(stoi(cond.value));
                        inpCond.push_back(make_pair(cond.columnName,data));
                    }
                    else if(type == "float"){
                        DataFloat* data = new DataFloat(stof(cond.value));
                        inpCond.push_back(make_pair(cond.columnName,data));
                    }
                    else{
                        DataString* data = new DataString(cond.value);
                        inpCond.push_back(make_pair(cond.columnName,data));
                    }
                }
                database->deleteRows(tableName,inpCond);
            }
        }
    }

    writeRoot();
    return 0;
}