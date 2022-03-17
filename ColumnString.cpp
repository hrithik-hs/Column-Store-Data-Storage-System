#include "ColumnString.h"

ColumnString::ColumnString():Column(){}

ColumnString::ColumnString(string name):Column(name){}

ColumnString::~ColumnString(){}

void ColumnString::writeFile(){

}
void ColumnString::loadFile(){

}

void ColumnString::insertValue(string value){
	this->column.push_back(new Data<string>(value));
}
void ColumnString::deleteValue(int index){
	if(index <this->column.size() && index >=0)
		this->column[index]=NULL;
}
void ColumnString::alterValue(int index, string newValue){
	if(index <this->column.size() && index >=0)
		this->column[index]->setValue(newValue);
}
void ColumnString::showValue(){
	return this->column;
}