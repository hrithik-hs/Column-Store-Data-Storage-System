#include "ColumnRecord.h"

ColumnRecord::ColumnRecord(){}
ColumnRecord::~ColumnRecord(){}

ColumnRecord::ColumnRecord(string columnName, string columnType, int key){
	strcpy(this->columnName, columnName.c_str());
	strcpy(this->columnType, columnType.c_str());
    this->difVal = 0;
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
    vector<string> res;
    for(int i = 0; i < this->difVal; i ++) {
        char temp[100];
        strcpy(temp, this->encoding[i]);
        res.push_back(temp);
    }
    return res;
}

void ColumnRecord::setEncoding(vector<string> _encoding) {
    for(int i = 0; i < _encoding.size(); i ++) {
        strcpy(this->encoding[i], _encoding[i].c_str());
    }
    this->difVal = _encoding.size();
}

void ColumnRecord::togIsPrimary(){
    this->isPrimary = !this->isPrimary;
}
