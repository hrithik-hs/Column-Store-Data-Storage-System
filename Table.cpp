#include "Table.h"

Table::Table(){
	
}
Table::Table(string name){
	
}
Table::Table(string column,vector<Column *> & columns){
	
}
Table::Table(string column,vector<Column *> & columns, Column * primaryKey){
	
}
Table::~Table(){
	
}

void Table::dropTable(){
	
}
void Table::addColumn(Column * column){
	
}
void Table::dropColumn(Column * column){
	
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