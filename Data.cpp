#pragma once
#include "Data.h"


Data::Data(){}

Data::Data(T value){
	this->value=value;
}

T Data::getValue(){
	return this->value;
}

void Data::setValue(T value){
	this->value=value;
}