#include "DataFloat.h"

DataFloat::DataFloat():Data("float"){}

DataFloat::DataFloat(float value):Data("float"){
    this->value=value;
}

void DataFloat::setValue(float value){
    this->value=value;
}
float DataFloat::getFloat(){
    return this->value;
}