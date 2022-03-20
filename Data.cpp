#pragma once
#include "Data.h"

template<typename T>
Data<T>::Data(){}

template<typename T>
Data<T>::Data(T value){
	this->value=value;
}

template<typename T>
T Data<T>::getValue(){
	return this->value;
}

template<typename T>
void Data::setValue(T value){
	this->value=value;
}