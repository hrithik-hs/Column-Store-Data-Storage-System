#include "DataString.h"
#define tr(x) cerr<<x<<endl
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;

DataString::DataString(){
    string type="string";
    strcpy(this->type, type.c_str());
}
DataString::~DataString(){}

DataString::DataString(string value){
    string type="string";
    strcpy(this->type, type.c_str());
    strcpy(this->value, value.c_str());
}

void DataString::setValue(string value){
   strcpy(this->value, value.c_str());
}
string DataString::getString(){
    return this->value;
}

string DataString::getType(){
    return this->type;
}