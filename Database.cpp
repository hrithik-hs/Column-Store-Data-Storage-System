#include "Database.h"
#define tr(X) cerr<< X << endl;
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;

Database::Database(){}

Database::Database(string name, string address){
	this->name = name;
	this->address = address;
    int fl = this->loadFile();
	if(fl) cout << "[ D+ ] [ Constructor ] Database open successfull." << endl;
	else cout << "[ D- ] [ Constructor ] Database open failed." << endl;
}

Database::Database(string name, vector<Table *> & tables){
	this->name = name;
	this->tables = tables;
    int fl = this->loadFile();
	if(fl) cout << "[ D+ ] [ Constructor ] Database open successfull." << endl;
	else cout << "[ D- ] [ Constructor ] Database open failed." << endl;
}

Database::~Database(){
	for(int i = 0; i < this->tables.size(); i ++) {
		delete this->tables[i];
	}
	for(int i = 0; i < this->tableRecords.size(); i ++) {
		delete this->tableRecords[i];
	}
	cout << "[ D+ ] [ Destructor ] Database close successfull." << endl;
}

void Database::createTable(string tableName){
    for(auto table: this->tables) {
        if(table->getName() == tableName) {
            cout << "[ D! Warning ] [ Create table ] Table already exists with given name: " << tableName << endl;
            return;
        }
    }
	this->tableNames[tableName]=this->tableNames.size();

	string address = this->address + "/" +this->name+"/"+ tableName + ".tb";
    string folderAddress = this->address+'/'+this->name+"/"+ tableName;
	fs::create_directories(folderAddress);
	ofstream outfile(address);

	string flagAddress = folderAddress + "/" + tableName + ".flag";
	FILE* fptr1 = fopen(&flagAddress[0], "w");
	if(!fptr1) {
        cout << "[ D- ] [ Create table ] Cannot create the flag file for " << tableName << " table." << endl;
        return;
    }
	fclose(fptr1);

	string delAddress = folderAddress + "/" + tableName + ".del";
	FILE* fptr2 = fopen(&delAddress[0], "w");
	if(!fptr2) {
        cout << "[ D- ] [ Create table ] Cannot create the delete file for " << tableName << " table." << endl;
        return;
    }
	fclose(fptr2);
    
	Table* table = new Table(tableName, this->address+'/'+this->name);
	this->tables.push_back(table);
	tableRecords.push_back(new TableRecord(tableName));

	cout << "[ D+ ] [ Create table ] Table creation successfull. Name: "<< tableName << endl;
}

void Database::dropTable(string tableName){
	if(this->tableNames.find(tableName)==this->tableNames.end()){
		cout << "[ D! Warning ]  [ Drop table ] Table doesn't exists with given name: " << tableName << endl;
		return;
	}
	int toDelete=this->tableNames[tableName];

	if(toDelete != -1) {
		vector<Column*> column = this->tables[toDelete]->getColumns();
		for(auto col : column) {
			this->tables[toDelete]->dropColumn(col->getName());
		}
		this->tables.erase(this->tables.begin() + toDelete);
		this->tableRecords.erase(this->tableRecords.begin() + toDelete);
		cout << "[ D+ ] [ Drop table ] Table drop successfull. Name: "<< tableName << endl;
	}
}

void Database::addColumn(string tableName, string columnName, string datatype) {
	if(this->tableNames.find(tableName)==this->tableNames.end()){
		cout << "[ D! Warning ]  [ Add column ] Table doesn't exists with given name: " << tableName << endl;
		return;
	}
	this->tables[this->tableNames[tableName]]->addColumn(columnName, datatype);
}

void Database::dropColumn(string tableName, string columnName) {
	if(this->tableNames.find(tableName)==this->tableNames.end()){
		cout << "[ D! Warning ]  [ Drop column ] Table doesn't exists with given name: " << tableName << endl;
		return;
	}
	this->tables[this->tableNames[tableName]]->dropColumn(columnName);
}

void Database::alterColumn(string tableName, string columnName, string newName) {
	if(this->tableNames.find(tableName)==this->tableNames.end()){
		cout << "[ D! Warning ]  [ Alter column ] Table doesn't exists with given name: " << tableName << endl;
		return;
	}
	this->tables[this->tableNames[tableName]]->alterColumn(columnName, newName);
}

void Database::setPrimaryKey(string tableName, string columnName) {
	if(this->tableNames.find(tableName)==this->tableNames.end()){
		cout << "[ D! Warning ]  [ Set primary ] Table doesn't exists with given name: " << tableName << endl;
		return;
	}
	this->tables[this->tableNames[tableName]]->setPrimaryKey(columnName);
}

void Database::setName(string name){
	this->name = name;
	cout << "[ D+ ] Set name successfull " << endl;
}

void Database::setIsUniqueConstraint(string tableName, string columnName, bool value) {
	if(this->tableNames.find(tableName)==this->tableNames.end()){
		cout << "[ D! Warning ]  [ Set unique ] Table doesn't exists with given name: " << tableName << endl;
		return;
	}
	this->tables[this->tableNames[tableName]]->setIsUniqueConstraint(columnName, value);
}

string Database::getName(){
	return this->name;
}

vector<Table*> Database::getTables(){
	return this->tables;
}

int Database::insertRow(string  tableName,Row * row){
	if(this->tableNames.find(tableName)==this->tableNames.end()){
		cout << "[ D! Warning ]  [ Insert row ] Table doesn't exists with given name: " << tableName << endl;
		return 0;
	}
	int fl = this->tables[this->tableNames[tableName]]->insertRow(row);
	if(fl) cout << "[ D+ ]  [ Insert row ] Insert row successfull" << endl;
	else cout << "[ D- ]  [ Insert row ] Insert row failed" << endl;
	return fl;
}

int Database::selectRows(string tableName, vector<string> cols, vector<pair<string,Data*>> conditions){
	if(this->tableNames.find(tableName)==this->tableNames.end()){
		cout << "[ D! Warning ]  [ Select row ] Table doesn't exists with given name: " << tableName << endl;
		return 0;
	}
	int fl = this->tables[this->tableNames[tableName]]->selectRows(cols,conditions);
	if(fl) cout << "[ D+ ]  [ Select row ] Select row successfull" << endl;
	else cout << "[ D- ]  [ Select row ] Select row failed" << endl;
	return fl;
}

int Database::deleteRows(string tableName, vector<pair<string,Data*>> conditions){
	if(this->tableNames.find(tableName)==this->tableNames.end()){
		cout << "[ D! Warning ]  [ Delete row ] Table doesn't exists with given name: " << tableName << endl;
		return 0;
	}
	int fl = this->tables[this->tableNames[tableName]]->deleteRows(conditions);
	if(fl) cout << "[ D+ ]  [ Delete row ] Delete row successfull" << endl;
	else cout << "[ D- ]  [ Delete row ] Delete row failed" << endl;
	return fl;
}

int Database::loadFile() {
    string curAddress = this->address+'/'+this->name+".db";
	string folderAddress = this->address+'/'+this->name;
	FILE* fptr = fopen(&curAddress[0], "rb");
	if(!fptr) {
        cout << "[ D- ] [ Load database ] Cannot open table record file for " << this->name << " database." << endl;
        return 0;
    }
	int ind=0;
	while(1){
	    TableRecord *ptr = new TableRecord();
        int sz=fread(ptr, sizeof(TableRecord), 1, fptr);
        if(sz == 0) break;
		this->tableNames[(ptr->getName())]=ind;
		ind++;
        this->tableRecords.push_back(ptr);
        Table* newTable = new Table(ptr->getName(), folderAddress);
		this->tables.push_back(newTable);
	}
	fclose(fptr);
	return 1;
}

int Database::writeFile() {
	string address = this->address + "/" + this->name + ".db";
	FILE* fptr = fopen(&address[0], "wb");
	if(!fptr) {
        cout << "[ D- ] [ Write database ] Cannot open table record file for " << this->name << " database." << endl;
        return 0;
    }
	for(int i=0; i<this->tableRecords.size(); i++){
		if(this->tableRecords[i] != NULL){
			int sz = fwrite(this->tableRecords[i],sizeof(TableRecord),1,fptr);
		}
	}
	fclose(fptr);
	return 1;
}

void Database::close() {
    int fl = writeFile();
	if(!fl){
		cout << "[ D- ] [ Close database ] Close failed for " << this->name << " database." << endl;
        return;
	}
    for(auto table: this->tables) {
        fl = table->close();
		if(!fl) break;
    }
	if(!fl) cout << "[ D- ] [ Close database ] Close failed for " << this->name << " database." << endl;
	else cout << "[ D+ ] [ Close database ] Close successfull for " << this->name << " database." << endl;
}

void Database::show() {
	cout<<endl;
    for(auto table : this->tables) {
        cout << "Printing " << table->getName() << endl;
        table->showTable();
		cout<<endl;
    }
}