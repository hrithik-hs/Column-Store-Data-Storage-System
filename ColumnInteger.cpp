#include "ColumnInteger.h"

ColumnInteger::ColumnInteger():Column(){}

ColumnInteger::ColumnInteger(string name):Column(name){}

ColumnInteger::ColumnInteger(string name,string address):Column(name,address){}

ColumnInteger::~ColumnInteger(){}

void ColumnInteger::writeFile(string file_source){
    ofstream writeptr(file_source, ios::out | ios::binary);
    if(!writeptr) {
        cout << "Cannot open the file" << endl;
        return;
    }
    for(int i = 0; i < column.size(); i ++) {
        writeptr.write((char *)column[i].sizeof(Data<int>));
    }
    writeptr.close();
}
void ColumnInteger::loadFile(string file_source){
    ifstream readptr(file_source, ios::in | ios::binary);
    if(!readptr) {
        cout << "Cannot open the file" << endl;
        return;
    }
    readptr.seekg(0, ios::beg);
    while(readptr.peek() != EOF) {
        Data<int> *ptr = new Data<int>();
        readptr.read((char*)ptr, sizeof(Data<int>));
        column.push_back(ptr);
    }
    readptr.close();
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
