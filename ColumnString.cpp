#include "ColumnString.h"

ColumnString::ColumnString():Column(){}

ColumnString::ColumnString(string name):Column(name){}

ColumnString::~ColumnString(){}

void ColumnString::writeFile(){
    ofstream writeptr(file_source, ios::out | ios::binary);
    if(!writeptr) {
        cout << "Cannot open the file" << endl;
        return;
    }
    for(int i = 0; i < column.size(); i ++) {
        writeptr.write((char *)column[i]. sizeof(Data<string>));
    }
    writeptr.close();
}
void ColumnString::loadFile(){
    ifstream readptr(file_source, ios::in | ios::binary);
    if(!readptr) {
        cout << "Cannot open the file" << endl;
        return;
    }
    readptr.seekg(0, ios::beg);
    while(readptr.peek() != EOF) {
        Data<string> *ptr = new Data<string>();
        readptr.read((char*)ptr, sizeof(Data<string>));
        column.push_back(ptr);
    }
    readptr.close();
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
