#include "ColumnInteger.h"

ColumnInteger::ColumnInteger():Column(){}

ColumnInteger::ColumnInteger(string name):Column(name){}

ColumnInteger::~ColumnInteger(){}

void ColumnInteger::writeFile(){

}
void ColumnInteger::loadFile(){

}

void ColumnInteger::insertValue(int value){
	this->column.push_back(new Data<int>(value));
}
void ColumnInteger::deleteValue(int index){
	if(index <this->column.size() && index >=0)
		this->column[index]=NULL;
}
void ColumnInteger::alterValue(int index, int newValue){
	if(index <this->column.size() && index >=0)
		this->column[index]->setValue(newValue);
}
vector<Data<int> *> ColumnInteger::getColumn(){
	return this->column;
}