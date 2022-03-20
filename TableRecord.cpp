#include "TableRecord.h"

TableRecord::TableRecord(){}
TableRecord::TableRecord(string name) {
    this->name = name;
}

void TableRecord::setName(string name) {
    this->name = name;
}
string TableRecord::getName(string name) {
    return this->name;
}