#include "ColumnRecord.h"

ColumnRecord::ColumnRecord(){}
ColumnRecord::~ColumnRecord(){}

ColumnRecord::ColumnRecord(string columnName, string columnType,bool primary=0, bool unique=0, bool notNull=0){
	strcpy(this->columnName, columnName.c_str());
	strcpy(this->columnType, columnType.c_str());
    this->isPrimary = primary;
    this->unique=unique;
    this->notNull=notNull;
    if(primary){
        this->unique=1;
        this->notNull=1;
    }
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

void ColumnRecord::togIsPrimary(){
    this->isPrimary = !this->isPrimary;
}

bool ColumnRecord::getPrimary(){
    return this->isPrimary;
}
bool ColumnRecord::getUnique(){
    return this->unique;
}
bool ColumnRecord::getNotNull(){
    return this->notNull;
}
