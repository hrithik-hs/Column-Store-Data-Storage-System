#include "Data.h"

Data::Data(){}

Data::Data(string type){
    this->type=type;
}
string Data::getType(){
    return this->type;
}