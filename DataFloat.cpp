#include "DataFloat.h"
#define tr(x) cerr<<x<<endl
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;

DataFloat::DataFloat(){
    string type="float";
    strcpy(this->type, type.c_str());
}
DataFloat::~DataFloat(){fn();}

DataFloat::DataFloat(float value){
    string type="float";
    strcpy(this->type, type.c_str());
    this->value=value;
}

void DataFloat::setValue(float value){
    this->value=value;
}
float DataFloat::getFloat(){
    return this->value;
}

string DataFloat::getType(){
    return this->type;
}