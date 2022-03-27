#include "ColumnFloat.h"

ColumnFloat::ColumnFloat():Column(){}

ColumnFloat::ColumnFloat(string name):Column(name){}

ColumnFloat::ColumnFloat(string name,string address):Column(name,address){}

ColumnFloat::~ColumnFloat(){}

void ColumnFloat::writeFile(string file_source){
    ofstream writeptr(file_source, ios::out | ios::binary);
    if(!writeptr) {
        cout << "Cannot open the file" << endl;
        return;
    }
    for(int i = 0; i < column.size(); i ++) {
        writeptr.write((char *)column[i]. sizeof(Data<float>));
    }
    writeptr.close();
}

void ColumnFloat::loadFile(string file_source){
    ifstream readptr(file_source, ios::in | ios::binary);
    if(!readptr) {
        cout << "Cannot open the file" << endl;
        return;
    }
    readptr.seekg(0, ios::beg);
    while(readptr.peek() != EOF) {
        Data<float> *ptr = new Data<float>();
        readptr.read((char*)ptr, sizeof(Data<float>));
        column.push_back(ptr);
    }
    readptr.close();
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

vector<Data<float> *> ColumnFloat::getColumn(){
	return this->column;
}
