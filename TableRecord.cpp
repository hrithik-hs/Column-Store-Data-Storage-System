#include "TableRecord.h"

TableRecord::TableRecord(){}

TableRecord::TableRecord(string columnName, string columnType, int key){
	this->columnName=columnName;
	this->columnType = columnType;
    this->isPrimary = key;
}

void TableRecord::setColName(string name){
    this->columnName = name;
}

string TableRecord::getColName(){
    return this->columnName;
}

string TableRecord::getColType(){
    return  this->columnType;
}

int TableRecord::getIsPrimary(){
    return this->isPrimary;
}

void TableRecord::togIsPrimary(){
    this->isPrimary = !this->isPrimary;
}
