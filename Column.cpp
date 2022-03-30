#include "Column.h"

Column::Column(){}
Column::Column(string name){
	this->name=name;
}
Column::Column(string name,string address){
	this->name=name;
    this->address=address;
}
Column::Column(string name,string address,string type){
	this->name=name;
    this->address=address;
	this->type=type;
}

Column::~Column(){
	this->writeFile();
	while(!this->column.empty()){
		delete this->column.back();
		this->column.pop_back();
	}
}

void Column::writeFile(){
	string file_source=this->address;
	ofstream writeptr(file_source, ios::out | ios::binary);
    if(!writeptr) {
        cout << "Cannot open the file" << endl;
        return;
    }
    for(int i = 0; i < column.size(); i ++) {
		if(this->type=="int"){
			writeptr.write((char *)column[i], sizeof(DataInteger));
		}
		else if(this->type=="float"){
			writeptr.write((char *)column[i], sizeof(DataFloat));
		}
		else if(this->type=="string"){
			writeptr.write((char *)column[i], sizeof(DataString));
		}
        
    }
    writeptr.close();
}

void Column::loadFile(){
	string file_source=this->address;
	ifstream readptr(file_source, ios::in | ios::binary);
    if(!readptr) {
        cout << "Cannot open the file" << endl;
        return;
    }
    readptr.seekg(0, ios::beg);
    while(readptr.peek() != EOF) {
		if(this->type=="int"){
			Data *ptr = new DataInteger();
			readptr.read((char*)ptr, sizeof(DataInteger));
			column.push_back(ptr);
		}
		else if(this->type=="float"){
			Data *ptr = new DataFloat();
			readptr.read((char*)ptr, sizeof(DataFloat));
			column.push_back(ptr);
		}
		else if(this->type=="string"){
			Data *ptr = new DataString();
			readptr.read((char*)ptr, sizeof(DataString));
			column.push_back(ptr);
		}
    }
    readptr.close();
}

void Column::insertValue(float value){
	Data * data=new DataFloat(value);
	this->column.push_back(data);
}
void Column::insertValue(int value){
	Data * data=new DataInteger(value);
	this->column.push_back(data);
}
void Column::insertValue(string value){
	Data * data=new DataString(value);
	this->column.push_back(data);
}

void Column::deleteValue(int index){
	if(index <this->column.size() && index >=0)
		this->column[index]=NULL;
}

void Column::alterValue(int index, int newValue){
	if(index <this->column.size() && index >=0)
		this->column[index]->setValue(newValue);
}
void Column::alterValue(int index, float newValue){
	if(index <this->column.size() && index >=0)
		this->column[index]->setValue(newValue);
}
void Column::alterValue(int index, string newValue){
	if(index <this->column.size() && index >=0)
		this->column[index]->setValue(newValue);
}

vector<Data *> Column::getColumn(){
	return this->column;
}
string Column::getType(){
	return this->type;
}
string Column::getName(){
	return this->name;
}
string Column::getAddress(){
	return this->address;
}

void Column::setName(string name){
	this->name=name;
}
void Column::setType(string type){
	this->type=type;
}
void Column::setAddress(string address){
	this->address=address;
}