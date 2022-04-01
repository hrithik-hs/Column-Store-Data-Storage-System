#include "Data.h"

Data::Data(){}

Data::Data(string type){
    this->type=type;
}

Data::~Data(){}

string Data::getType(){
    return this->type;
}

void Data::setValue(int value){}
void Data::setValue(float value){}
void Data::setValue(string value){}

int Data::getInt(){
    return 0;
}
float Data::getFloat(){
    return 0.0;
}
string Data::getString(){
    return "0";
}