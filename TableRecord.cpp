#include "TableRecord.h"

TableRecord::TableRecord(){}
TableRecord::TableRecord(string name) {
    this->name = name;
}
TableRecord::~TableRecord(){}

void TableRecord::setName(string name) {
    this->name = name;
}
string TableRecord::getName() {
    return this->name;
}