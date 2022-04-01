#include "DataString.h"

DataString::DataString():Data("string"){}

DataString::DataString(string value):Data("string"){
    this->value=value;
}

void DataString::setValue(string value){
    this->value=value;
}
string DataString::getString(){
    return this->value;
}