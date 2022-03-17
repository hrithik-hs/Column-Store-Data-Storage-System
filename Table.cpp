#include "Table.h"

Table::Table(){}

Table::Table(string name){
	this->name=name;
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
		delete this->columns.back();
		this->columns.pop_back();
	}
	delete this->primaryKey;
}

void Table::dropTable(){}

void Table::addColumn(Column * column){
	if(column && this->columnNames.find(column.getName())==this->columnNames.end()){
		this->columns.push_back(column);
	}
}
void Table::dropColumn(string columnName){
	if(this->columnNames.find(columnName)!=this->columnNames.end()){
		for(auto &column:this->columns){
			if(column.getName()==columnName)column=NULL;
		}
	}
}
void Table::alterColumn(/*Old column new column new datatype*/){
	
} 
void Table::showTable(vector<Column *>& columns/*, Filters */){
	
}

void Table::setName(string name){
	
}
void Table::setPrimaryKey(Column * column){
	
}

Column * Table::getPrimaryKey(){
	
}
string Table::getName(){
	
}
vector<Column *> Table::getColumns(){
	
}