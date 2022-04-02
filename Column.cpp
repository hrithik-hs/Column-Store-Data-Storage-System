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
    cerr << "WriteFileColumn " << this->name << " " << this->address << endl;
	string file_source=this->address+"/"+this->name+".col";
	cerr << file_source << endl;
    // ofstream writeptr(file_source, ios::out | ios::binary);
    FILE* writeptr = fopen(&file_source[0], "w");
    if(!writeptr) {
        cout << "Cannot open the write file" << endl;
        return;
    }
    for(int i = 0; i < column.size(); i ++) {
		if(this->type=="int"){
			// writeptr.write((char *)column[i], sizeof(DataInteger));
            fwrite(this->column[i],sizeof(DataInteger),1,writeptr);
		}
		else if(this->type=="float"){
			// writeptr.write((char *)column[i], sizeof(DataFloat));
            fwrite(this->column[i],sizeof(DataFloat),1,writeptr);
		}
		else if(this->type=="string"){
			// writeptr.write((char *)column[i], sizeof(DataString));
            fwrite(this->column[i],sizeof(DataString),1,writeptr);
		}
        
    }
    fclose(writeptr);
}

void Column::loadFile(){
	// string file_source=this->address;
	string file_source=this->address+"/"+this->name+".col";
	// ifstream readptr(file_source, ios::in | ios::binary);
    // cerr << file_source << endl;
    FILE* readptr = fopen(&file_source[0], "r");
    if(!readptr) {
        cout << "Cannot open the load file" << endl;
        return;
    }
    // readptr.seekg(0, ios::beg);
    while(1) {
		if(this->type=="int"){
			Data *ptr = new DataInteger();
			int sz = fread(ptr, sizeof(DataInteger), 1, readptr);
            if(sz == 0) break;
			column.push_back(ptr);
		}
		else if(this->type=="float"){
			Data *ptr = new DataFloat();
			int sz = fread(ptr, sizeof(DataFloat), 1, readptr);
            if(sz == 0) break;
			column.push_back(ptr);
		}
		else if(this->type=="string"){
			Data *ptr = new DataString();
			int sz = fread(ptr, sizeof(DataString), 1, readptr);
            if(sz == 0) break;
			column.push_back(ptr);
		}
    }
    fclose(readptr);
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