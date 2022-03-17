#include "ColumnFloat.h"

ColumnFloat::ColumnFloat():Column(){}

ColumnFloat::ColumnFloat(string name):Column(name){}

ColumnFloat::~ColumnFloat(){}

void ColumnFloat::writeFile(){

}
void ColumnFloat::loadFile(){

}

void ColumnFloat::insertValue(float value){
	this->column.push_back(new Data<float>(value));
}
void ColumnFloat::deleteValue(int index){
	if(index <this->column.size() && index >=0)
		this->column[index]=NULL;
}
void ColumnFloat::alterValue(int index, float newValue){
	if(index <this->column.size() && index >=0)
		this->column[index]->setValue(newValue);
}
void ColumnFloat::showValue(){
	return this->column;
}