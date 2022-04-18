#include "ColumnRecord.h"

ColumnRecord::ColumnRecord(){}
ColumnRecord::~ColumnRecord(){}

ColumnRecord::ColumnRecord(string columnName, string columnType, int key){
	strcpy(this->columnName, columnName.c_str());
	strcpy(this->columnType, columnType.c_str());
    if("enum" == columnType) {
        this->isEnum = true;
    }
    else {
        this->isEnum = false;
    }
    this->isPrimary = key;
}

void ColumnRecord::setColName(string name){
   strcpy(this->columnName, name.c_str());
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

vector<string> ColumnRecord::getEncoding() {
    return this->encoding;
}

void ColumnRecord::setEncoding(vector<string> _encoding) {
    this->encoding = _encoding;
}

void ColumnRecord::togIsPrimary(){
    this->isPrimary = !this->isPrimary;
}
