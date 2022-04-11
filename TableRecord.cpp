#include "TableRecord.h"

TableRecord::TableRecord(){}
TableRecord::TableRecord(string name,int size) {
    strcpy(this->name, name.c_str());
    this->size=size;
}
TableRecord::~TableRecord(){}

void TableRecord::setName(string name) {
    strcpy(this->name, name.c_str());
}
string TableRecord::getName() {

    return this->name;
}

int TableRecord::getSize(){
    return this->size;
}
void TableRecord::setSize(int size){
    this->size=size;
}
