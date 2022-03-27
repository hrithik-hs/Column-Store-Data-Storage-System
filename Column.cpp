#include "Column.h"

Column::Column(){}

Column::Column(string name){
	this->name=name;
}
Column::Column(string name,string address){
	this->name=name;
    this->address=address;
}
Column::~Column(){}

string Column::getName(){
	return this->name;
}

void Column::setName(string name){
	this->name=name;
}
