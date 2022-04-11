#include "Table.h"
#define tr(X) cerr<< X << endl;
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;
#include <typeinfo>

Table::Table(){}

Table::Table(string name, string address){
	this->name=name;
	this->address = address;
	this->loadFile();
}

// Table::Table(string name,vector<Column *> columns){
// 	this->name=name;
// 	this->columns=columns;
// 	for(auto column:columns){
// 		this->columnNames.insert
// 	}
// }
// Table::Table(string name,vector<Column *> columns, Column * primaryKey){
// 	this->name=name;
// 	this->columns=columns;
// 	this->primaryKey=primaryKey;
// }

Table::~Table(){
	while(!this->columns.empty()){
        // tr(this->columns.back());
		delete this->columns.back();
		this->columns.pop_back();
	}
    // delete this->ColumnRecords.back();
    while(!this->ColumnRecords.empty()){
        // tr(this->ColumnRecords.back());
        delete this->ColumnRecords.back();
		this->ColumnRecords.pop_back();
    }
	delete this->primaryKey;
    // fn();
}

void Table::loadFile(){
	string curAddress = this->address+'/'+this->name+".tb";
	string folderAddress = this->address+'/'+this->name;
	FILE* fptr = fopen(&curAddress[0], "r");
	while(1){
	    ColumnRecord* ptr = new ColumnRecord();
		int sz=fread(ptr, sizeof(ColumnRecord), 1, fptr);
        if(sz==0)break;

		this->columnNames.insert(ptr->getColName());
		Column* col=new Column(ptr->getColName(),folderAddress,ptr->getColType());
		this->columns.push_back(col);
		this->ColumnRecords.push_back(ptr);
		if(ptr->getIsPrimary()) this->primaryKey=this->columns.back();
	}
	this->flag.assign(this->ColumnRecords.size(), 0);
	fclose(fptr);
}

void Table::writeFile(){
	string curAddress = this->address+'/'+this->name+".tb";
	FILE* fptr = fopen(&(curAddress)[0], "w");
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] != NULL && this->flag[i] == 0) 
            fwrite(this->ColumnRecords[i],sizeof(ColumnRecord),1,fptr);
	}
	fclose(fptr);
}


void Table::addColumn(string columnName, string type){
	if(columnName.size() && this->columnNames.find(columnName)==this->columnNames.end()){
        this->columnNames.insert(columnName);
		Column* col=new Column(columnName,this->address + "/" + this->name,type);
		
		this->columns.push_back(col);
		this->ColumnRecords.push_back(new ColumnRecord(columnName,type,0));
		string columnAddress = this->address+'/'+this->name+'/'+columnName+".col";
		FILE* fptr = fopen(&columnAddress[0], "w");
		fclose(fptr);
	}
    else{
        cerr << "Column Already Exists!" << endl;
    }
}

void Table::dropColumn(string columnName){
	if(this->columnNames.find(columnName)!=this->columnNames.end()){
		for(int i=0;i<this->columns.size();i++){
			if(this->columns[i]->getName()==columnName){
				this->columns[i]=NULL;
				this->ColumnRecords[i]=NULL;
				break;
			}
		}
		this->columnNames.erase(columnName);
	}
}

void Table::alterColumn(string oldName, string newName){ /*only for renaming*/
	if(this->columnNames.find(oldName)==this->columnNames.end() || this->columnNames.find(newName)!=this->columnNames.end()) return;
	string oldAddress = this->address+'/'+this->name+'/'+oldName+".col";
	string newAddress = this->address+'/'+this->name+'/'+newName+".col";
	int f=rename(&oldAddress[0],&newAddress[0]);
	if(f!=0) return;
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getColName()==oldName){
			this->ColumnRecords[i]->setColName(newName);
			this->columns[i]->setName(newName);
			this->columnNames.erase(oldName);
			this->columnNames.insert(newName);
			break;
		}
	}
} 

void Table::showTable(){
    // fn();
    // tr(this->columns.size());
	if(this->columns.size() == 0) return ;
	for(auto column: this->columns) {
        cout << "Printing Column " << column->getName() << ": DataType " << column->getType() << endl;

        column->showColumn(); 
    }
}

/*
void Table::setName(string newName){
	string oldAddress = this->address+'/'+this->name;
	string newAddress = this->address+'/'+newName;
	int f = rename(&oldAddress[0],&newAddress[0]);
	oldAddress+=".tb";
	newAddress+=".tb";
	f = rename(&oldAddress[0],&newAddress[0]);
	if(f==0) this->name = newName;
}
*/

void Table::setPrimaryKey(string columnName){
	if(columnName.size() && this->columnNames.find(columnName)==this->columnNames.end()) return;

	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getIsPrimary()){
			this->ColumnRecords[i]->togIsPrimary();
			break;
		}
	}
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getColName()==columnName){
			this->ColumnRecords[i]->togIsPrimary();
			this->primaryKey = this->columns[i];
			break;
		}
	}
}

Column * Table::getPrimaryKey(){
	return this->primaryKey;
}

string Table::getName(){
	return this->name;
}

vector<Column *> Table::getColumns(){
	return this->columns;
}

void Table::insertRow(Row *row){
    if(row->getRow().size()!=this->columns.size()){
		return;
	}
	for(int i=0;i<row->getRow().size();i++){
		if(row->getRow()[i]->getType()!=this->columns[i]->getType()){
			return;
		}
	}
	this->flag.push_back(0);
	for(int i=0;i<row->getRow().size();i++) {
		if(this->columns[i]->getType()=="int"){
			this->columns[i]->insertValue(row->getRow()[i]->getColumn().back()->getInt());
		}
		else if(this->columns[i]->getType()=="float"){
			this->columns[i]->insertValue(row->getRow()[i]->getColumn().back()->getFloat());
		}
		else if(this->columns[i]->getType()=="string"){
			this->columns[i]->insertValue(row->getRow()[i]->getColumn().back()->getString());
		}
	}
}

void Table::close() {
    writeFile();
	if(this->columns.size() == 0) return ;
    for(auto column: this->columns) {
        column->close();
    }
}
// template <typename T1,typename T2>
// void Table::updateRow(string columnName,T1 newValue, string comparisionColumn, T2 comparisionValue){

// }

void Table::deleteRow(string columnName, int primaryKeyValue) {
	if(columnNames.find(columnName) == columnNames.end()) {
		cerr << "[-]Error: Column Does not exists." << endl;
		return ;
	}
	if(primaryKeyValue > (int)(this->flag.size())) {
		cerr << "[-]Error: Invalid Primary key." << endl;
		return ; 
	}
	this->flag[primaryKeyValue] = 1;
}
