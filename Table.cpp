#include "Table.h"

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
	writeFile();
	while(!this->columns.empty()){
		delete this->columns.back();
		delete this->ColumnRecords.back();
		this->columns.pop_back();
		this->ColumnRecords.pop_back();
	}
	delete this->primaryKey;
}

void Table::loadFile(){
	string curAddress = this->address+'/'+this->name+".tb";
	FILE* fptr = fopen(&curAddress[0], "r");
	ColumnRecord* tr;
	while(!feof(fptr)){
		fread(tr, sizeof(ColumnRecord), 1, fptr);
		this->columnNames.insert(tr->getColName());
		Column* col;
		if(tr->getColType() == "int"){
			col = new ColumnInteger(tr->getColName(),this->address);
			// this->columns.push_back(col);
		}
		else if(tr->getColType() == "float"){
			col = new ColumnFloat(tr->getColName(),this->address);
			// this->columns.push_back(col);
		}
		else if(tr->getColType() == "string"){
			col = new ColumnString(tr->getColName(),this->address);
			// this->columns.push_back(col);
		}
		this->columns.push_back(col);
		this->ColumnRecords.push_back(tr);
		if(tr->getIsPrimary()) this->primaryKey=this->columns.back();
	}
}

void Table::writeFile(){
	FILE* fptr = fopen(&(this->address)[0], "w");
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] != NULL) fwrite(this->ColumnRecords[i],sizeof(ColumnRecord),1,fptr);
	}
	fclose(fptr);
}

void Table::dropTable(){}

void Table::addColumn(string columnName, string type){
	if(columnName.size() && this->columnNames.find(columnName)==this->columnNames.end()){
		this->columnNames.insert(columnName);
		Column* col;
		if(type == "int"){
			col = new ColumnInteger(columnName,this->address);
		}
		else if(type == "float"){
			col = new ColumnFloat(columnName,this->address);
		}
		else if(type == "string"){
			col = new ColumnString(columnName,this->address);
		}
		this->columns.push_back(col);
		this->ColumnRecords.push_back(new ColumnRecord(columnName,type,0));
		string columnAddress = this->address+'/'+this->name+'/'+columnName+".col";
		FILE* fptr = fopen(&columnAddress[0], "w");
		fclose(fptr);
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

void Table::showTable(vector<Column *>& columns/*, Filters */){
	
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
    
}

template <typename T1,typename T2>
void Table::updateRow(string columnName,T1 newValue, string comparisionColumn, T2 comparisionValue){

}

template <typename T>
void Table::deleteRow(string comparisionColumn,T comparisionValue){
    
}
