#include "DataEnum.h"
#define tr(x) cerr<<x<<endl
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;

int DataEnum::numValues;
char DataEnum::encoding[10][100];

DataEnum::DataEnum(){
    string type = "enum";
    strcpy(this->type, type.c_str());
}

DataEnum::~DataEnum(){}

DataEnum::DataEnum(vector<string> _encoding, string _value){
    string type = "enum";
    strcpy(this->type, type.c_str());
    this->numValues = _encoding.size();
    for(int i = 0; i < this->numValues; i ++) {
        strcpy(this->encoding[i], _encoding[i].c_str());
    }
    for(int i = 0; i < this->numValues; i ++) {
        if(strcmp(this->encoding[i], _value.c_str()) == 0) {
            this->value[i] = true;
        }
        else this->value[i] = false;
    }
}

void DataEnum::setValue(string _value){
    for(int i = 0; i < this->numValues; i ++) {
        if(strcmp(this->encoding[i], _value.c_str()) == 0) {
            this->value[i] = true;
        }
        else this->value[i] = false;
    }
}

string DataEnum::getEnum(){
    for(int i = 0; i < this->numValues; i ++) {
        if(this->value[i]) {
            return this->encoding[i];
        }
    }
    return "NOT FOUND";
}

string DataEnum::getType(){
    return this->type;
}