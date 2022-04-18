#include "Database.h"
#define tr(X) cerr<< X << endl;
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;

Database::Database(){}

Database::Database(string name, string address){
	this->name = name;
	this->address = address;
    this->loadFile();
}
Database::Database(string name, vector<Table *> & tables){
	this->name = name;
	this->tables = tables;
    this->loadFile();
}
Database::~Database(){
    // fn();
	for(int i = 0; i < this->tables.size(); i ++) {
		delete this->tables[i];
	}
	for(int i = 0; i < this->tableRecords.size(); i ++) {
		delete this->tableRecords[i];
	}
}

void Database::createTable(string tableName){
    for(auto table: this->tables) {
        if(table->getName() == tableName) {
            cerr << "Table Already Exists!" << endl;
            return;
        }
    }
	string address = this->address + "/" +this->name+"/"+ tableName + ".tb";
    string folderAddress = this->address+'/'+this->name+"/"+ tableName;
	fs::create_directories(folderAddress);
	ofstream outfile(address);

	string flagAddress = folderAddress + "/" + tableName + ".flag";
	FILE* fptr1 = fopen(&flagAddress[0], "w");
	fclose(fptr1);

	string delAddress = folderAddress + "/" + tableName + ".del";
	FILE* fptr2 = fopen(&delAddress[0], "w");
	fclose(fptr2);
    
	Table* table = new Table(tableName, this->address+'/'+this->name);
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
	int len = this->tables.size();
	for(int i = 0; i < len; i ++) {
		if(this->tables[i]->getName() == tableName) {
			this->tables[i]->insertRow(row);
			break;
		}
	}
}

void Database::selectRows(string tableName, vector<string> cols, vector<pair<string,Data*>> conditions){
	int len = this->tables.size();
	for(int i = 0; i < len; i ++) {
		if(this->tables[i]->getName() == tableName) {
			this->tables[i]->selectRows(cols,conditions);
			break;
		}
	}
}

void Database::deleteRows(string tableName, vector<pair<string,Data*>> conditions){
	int len = this->tables.size();
	for(int i = 0; i < len; i ++) {
		if(this->tables[i]->getName() == tableName) {
			this->tables[i]->deleteRows(conditions);
			break;
		}
	}
}

template <typename T1,typename T2>
void Database::updateRow(string tableName,string columnName,T1 newValue, string comparisionColumn, T2 comparisionValue){
	int len = this->tables.size();
	for(int i = 0; i < len; i ++) {
		if(this->tables[i]->getName() == tableName) {
			// this->tables[i]->updateRow<T1,T2>(string columnName,T1 newValue, string comparisionColumn, T2 comparisionValue);
			break;
		}
	}
}

template <typename T>
void Database::deleteRow(string tableName,string comparisionColumn,T comparisionValue){
	int len = this->tables.size();
	for(int i = 0; i < len; i ++) {
		if(this->tables[i]->getName() == tableName) {
			// this->tables[i]->deleteRow<T>(string comparisionColumn,T comparisionValue);
			break;
		}
	}
}

void Database::loadFile() {
    string curAddress = this->address+'/'+this->name+".db";
	string folderAddress = this->address+'/'+this->name;
	FILE* fptr = fopen(&curAddress[0], "rb");
	while(1){
	    TableRecord *ptr = new TableRecord();
        int sz=fread(ptr, sizeof(TableRecord), 1, fptr);
        if(sz == 0) break;
        // cerr << (ptr->getName()) << endl;
        this->tableRecords.push_back(ptr);
        Table* newTable = new Table(ptr->getName(), folderAddress);
		this->tables.push_back(newTable);
	}
	fclose(fptr);
}

void Database::writeFile() {
	string address = this->address + "/" + this->name + ".db";
	FILE* fptr = fopen(&address[0], "wb");
	for(int i=0; i<this->tableRecords.size(); i++){
		cerr << this->tableRecords[i]->getName() << endl;
		if(this->tableRecords[i] != NULL){

			int sz = fwrite(this->tableRecords[i],sizeof(TableRecord),1,fptr);
			cerr << sz << endl;
		}
	}
	fclose(fptr);
}

void Database::close() {
    writeFile();
    for(auto table: this->tables) {
        table->close();
    }
}

void Database::show() {
    for(auto table : this->tables) {
        cout << "Printing " << table->getName() << endl;
        table->showTable();
    }
}