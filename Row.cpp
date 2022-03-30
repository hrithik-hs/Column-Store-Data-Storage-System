#include "Row.h"


Row::Row(){}

Row::Row(vector<Column*>row){
	this->row=row;
}

// Row::Row(const Row &row){} //copy constuctor (if needed)

Row::~Row(){
	while(!this->row.empty()){
		delete this->row.back();
		this->row.pop_back();
	}
}

// void addElement(Column * element);
template <typename T>
void Row::addElement(string type, T value){
	Column* col=new Column()
	col->insertValue(value);
	col->setType(type);
	this->row.push_back(col);
}

void Row::setRow(vector<Column *> row){
	this->row=row;
}

vector<Column *> Row::getRow(){
	return this->row;
}