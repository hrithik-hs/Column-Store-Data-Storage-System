#include "TableRecord.h"

TableRecord::TableRecord(){}
TableRecord::TableRecord(string name) {
    strcpy(this->name, name.c_str());
}
TableRecord::~TableRecord(){}

void TableRecord::setName(string name) {
    strcpy(this->name, name.c_str());
}
string TableRecord::getName() {
    return this->name;
}