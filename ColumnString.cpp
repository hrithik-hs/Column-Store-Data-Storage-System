#include "ColumnString.h"

ColumnString::ColumnString():Column(){}

ColumnString::ColumnString(string name):Column(name){}
ColumnString::ColumnString(string name,string address):Column(name,address){}

ColumnString::~ColumnString(){}

void ColumnString::writeFile(string file_source){
    ofstream writeptr(file_source, ios::out | ios::binary);
    if(!writeptr) {
        cout << "Cannot open the file" << endl;
        return;
    }
    for(int i = 0; i < column.size(); i ++) {
        writeptr.write((char *)column[i].sizeof(Data<string>));
    }
    writeptr.close();
}
void ColumnString::loadFile(string file_source){
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
vector<Data<string> * > ColumnString::getColumn(){
	return this->column;
}
