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
	string address = this->address + "/" + tableName + ".db";
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

void Database::addColumn(string tableName, string columnName, string datatype) {
	int len = this->tables.size();
	for(int i = 0; i < len; i ++) {
		if(this->tables[i]->getName() == tableName) {
			this->tables[i]->addColumn(columnName, datatype);
			break;
		}
	}
}

void Database::dropColumn(string tableName, string columnName) {
	int len = this->tables.size();
	for(int i = 0; i < len; i ++) {
		if(this->tables[i]->getName() == tableName) {
			this->tables[i]->dropColumn(columnName);
			break;
		}
	}
}

void Database::alterColumn(string tableName, string columnName, string newName) {
	int len = this->tables.size();
	for(int i = 0; i < len; i ++) {
		if(this->tables[i]->getName() == tableName) {
			this->tables[i]->alterColumn(columnName, newName);
			break;
		}
	}
}

void Database::setPrimaryKey(string tableName, string columnName) {
	int len = this->tables.size();
	for(int i = 0; i < len; i ++) {
		if(this->tables[i]->getName() == tableName) {
			this->tables[i]->setPrimaryKey(columnName);
			break;
		}
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

void Database::insertRow(string  tableName,Row * row){

}

template <typename T1,typename T2>
void Database::updateRow(string tableName,string columnName,T1 newValue, string comparisionColumn, T2 comparisionValue){
	
}

template <typename T>
void Database::deleteRow(string tableName,string comparisionColumn,T comparisionValue){

}

void Database::writeFile() {
	string address = this->address + "/" + this->name + ".db";
	FILE* fptr = fopen(&address[0], "w");
	for(int i=0; i<this->tableRecords.size(); i++){
		if(this->tableRecords[i] != NULL) fwrite(this->tableRecords[i],sizeof(tableRecords),1,fptr);
}