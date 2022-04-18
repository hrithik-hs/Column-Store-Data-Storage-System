#include "Row.h"


Row::Row(){}

Row::Row(vector<Data*>row){
	this->row=row;
}

// Row::Row(const Row &row){} //copy constuctor (if needed)

Row::~Row(){
	while(!this->row.empty()){
		delete this->row.back();
		this->row.pop_back();
	}
}

void Row::addElement(int value){
	Data * data=new DataInteger(value);
	this->row.push_back(data);
}

void Row::addElement(float value){
	Data * data=new DataFloat(value);
	this->row.push_back(data);
}

void Row::addElement(string value){
	Data * data=new DataString(value);
	this->row.push_back(data);
}

void Row::setRow(vector<Data *> row){
	this->row=row;
}

vector<Data *> Row::getRow(){
	return this->row;
}