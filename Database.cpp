#include "Database.h"


Database::Database(){
	
}
Database::Database(string name, string address){
    this->name = name;
    this->address = address;
}
Database::Database(string name, vector<Table *> & tables){
	this->name = name;
    this->tables = tables;
}
Database::~Database(){
	writeFile();
}

void Database::createTable(string tableName){
    string address = this->address + "/" + name + ".db";
    fs::create_directories(address);
    ofstream outfile(address);
    Table* table = new Table(tableName, this->address);
    this->tables.push_back(table);
    tableRecords.push_back(new TableRecord(tableName));
}
void Database::dropTable(string tableName){
    int len = this->tables.size(), toDelete = -1;
	for(int i = 0; i < len; i ++) {
        if(this->tables[i]->getName() == tableName) {
            toDelete = i;
            break;
        }
    }
    if(toDelete != -1) {
        vector<Column*> column = this->tables[toDelete]->getColumns();
        for(auto col : column) {
            this->tables[toDelete]->dropColumn(col->getName());
        }
        this->tables.erase(this->tables.begin() + toDelete);
    }
}

void Database::setName(string name){
	this->name = name;
}
string Database::getName(){
	return this->name;
}
vector<Table*> Database::getTables(){
	return this->tables;
}

void Database::writeFile() {
    string address = this->address + "/" + this->name + ".db";
    FILE* fptr = fopen(&address[0], "w");
	for(int i=0; i<this->tableRecords.size(); i++){
		if(this->tableRecords[i] != NULL) fwrite(this->tableRecords[i],sizeof(tableRecords),1,fptr);
}