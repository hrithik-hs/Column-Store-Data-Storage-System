#include "DataInteger.h"
#define tr(x) cerr<<x<<endl
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;

DataInteger::DataInteger(){
    string type="int";
    strcpy(this->type, type.c_str());
}

DataInteger::DataInteger(int value){
    string type="int";
    strcpy(this->type, type.c_str());
    this->value=value;
}
DataInteger::~DataInteger(){}


void DataInteger::setValue(int value){
    this->value=value;
}

int DataInteger::getInt(){
    return this->value;
}

string DataInteger::getType(){
    return this->type;
}