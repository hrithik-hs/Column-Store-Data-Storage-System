#include "DataInteger.h"

DataInteger::DataInteger():Data("int"){}

DataInteger::DataInteger(int value):Data("int"){
    this->value=value;
}

void DataInteger::setValue(int value){
    this->value=value;
}

int DataInteger::getInt(){
    return this->value;
}