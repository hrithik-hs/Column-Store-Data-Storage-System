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
	FILE* fptr = fopen(curAddress, "r");
	ColumnRecord* tr;
	while(!feof(repo_handle->pds_ndx_fp)){
		fread(tr, sizeof(ColumnRecord), 1, fptr);
		this->columnNames.insert(tr->getColName());
		if(tr->getColType() == "int"){
			ColumnInteger* col = new ColumnInteger(tr->getColName(),this->address);
			this->columns.push_back(col);
		}
		else if(tr->getColType() == "float"){
			ColumnFloat* col = new ColumnInteger(tr->getColName(),this->address);
			this->columns.push_back(col);
		}
		else if(tr->getColType() == "string"){
			ColumnString* col = new ColumnInteger(tr->getColName(),this->address);
			this->columns.push_back(col);
		}
		this->ColumnRecords.push_back(tr);
		if(tr->getIsPrimary()) this->primaryKey=this->columns.back();
	}
}

void Table::writeFile(){
	FILE* fptr = fopen(this->address, "w");
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] != NULL) fwrite(this->ColumnRecords[i],sizeof(ColumnRecord),1,fptr);
	}
}

void Table::dropTable(){}

void Table::addColumn(Column * column, string type){
	if(column && this->columnNames.find(column.getName())==this->columnNames.end()){
		this->columns.push_back(column);
		ColumnRecords.push_back(new ColumnRecord(column.getName(),type,0));
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

void Table::alterColumn(string oldName, string newName){
	if(this->columnNames.find(oldName)==this->columnNames.end() || this->columnNames.find(newName)!=this->columnNames.end()) return;
	string oldAddress = this->address+'/'+this->name+'/'+oldName+".col";
	string newAddress = this->address+'/'+this->name+'/'+newName+".col";
	int f=rename(oldAddress,newAddress);
	if(f!=0) return;
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getColName()==oldName){
			this->ColumnRecords[i]->setColName(newName);
			this->columns->setName(newName);
			this->columnNames.erase(oldName);
			this->columnNames.insert(newName);
			break;
		}
	}
} 

void Table::showTable(vector<Column *>& columns/*, Filters */){
	
}

void Table::setName(string newName){
	string oldAddress = this->address+'/'+this->name;
	string newAddress = this->address+'/'+newName;
	int f = rename(oldAddress,newAddress);
	oldAddress+=".tb";
	newAddress+=".tb";
	f = rename(oldAddress,newAddress);
	if(f==0) this->name = newName;
}

void Table::setPrimaryKey(Column * column){
	if(column && this->columnNames.find(column.getName())==this->columnNames.end()) return
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getIsPrimary()){
			this->ColumnRecords[i]->togIsPrimary();
			break;
		}
	}
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getColName()==column.getName()){
			this->ColumnRecords[i]->togIsPrimary();
			break;
		}
	}
	this->primaryKey = column;
}

Column * Table::getPrimaryKey(){
	return this->primaryKey;
}

string Table::getName(){
	return this->name;
}

vector<Column *> Table::getColumns(){
	
}
