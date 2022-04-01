#include "ColumnRecord.h"

ColumnRecord::ColumnRecord(){}
ColumnRecord::~ColumnRecord(){}

ColumnRecord::ColumnRecord(string columnName, string columnType, int key){
	this->columnName=columnName;
	this->columnType = columnType;
    this->isPrimary = key;
}

void ColumnRecord::setColName(string name){
    this->columnName = name;
}

string ColumnRecord::getColName(){
    return this->columnName;
}

string ColumnRecord::getColType(){
    return  this->columnType;
}

int ColumnRecord::getIsPrimary(){
    return this->isPrimary;
}

void ColumnRecord::togIsPrimary(){
    this->isPrimary = !this->isPrimary;
}
