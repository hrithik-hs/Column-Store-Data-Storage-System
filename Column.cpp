#include "Column.h"
#define tr(x) cerr<<x<<endl
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;
#include <typeinfo>


Column::Column(){}
Column::Column(string name){
	this->name=name;
}
Column::Column(string name,string address){
	this->name=name;
    this->address=address;
    this->loadFile();
}
Column::Column(string name,string address,string type){
	this->name=name;
    this->address=address;
	this->type=type;
    this->loadFile();
}

Column::~Column(){
    fn();
	while(!this->column.empty()){
		// tr((this->column.back()==NULL));
		// tr(sizeof(this->column.back()));
        // tr(typeid((DataInteger *)this->column.back()).name());
        // tr((DataInteger *)this->column.back()->getInt());
        delete this->column.back();
        // tr(1);
		this->column.pop_back();
	}
    // fn();
}

void Column::writeFile(){
    fn();
    // cerr << "WriteFileColumn " << this->name << " " << this->address << endl;
	string file_source=this->address+"/"+this->name+".col";
    FILE* writeptr = fopen(&file_source[0], "w");
    if(!writeptr) {
        fn();
        cout << "Cannot open the write file" << endl;
        return;
    }
    
    for(int i = 0; i < column.size(); i ++) {
       
		if(this->type=="int"){
            DataInteger * ptr=new DataInteger(this->column[i]->getInt());
            // DataInteger ptr(this->column[i]->getInt());
            tr(this->column[i]->getInt());
            int sz=fwrite(ptr,sizeof(DataInteger),1,writeptr);
            // tr("Write size:");
            // tr(sz);
		}
		// else if(this->type=="float"){
        //     fwrite(this->column[i],sizeof(DataFloat),1,writeptr);
		// }
		// else if(this->type=="string"){
        //     fwrite(this->column[i],sizeof(DataString),1,writeptr);
		// }
        
    }
    fclose(writeptr);

    tr("\nread-----\n");
    FILE* readptr = fopen(&file_source[0], "r");
    DataInteger *ptr=new DataInteger();
    // int sz = fread((DataInteger *)ptr, sizeof(DataInteger), 1, readptr);
    int sz = fread(ptr, sizeof(ptr), 1, readptr);
    // if(sz == 0) break;
    tr(typeid(ptr).name());
    tr("ptr value:");tr(ptr->getInt());
    fclose(readptr);
    tr("read-----\n");
}

void Column::loadFile(){
    fn();
	string file_source=this->address+"/"+this->name+".col";
    FILE* readptr = fopen(&file_source[0], "r");
    if(!readptr) {
        fn();
        cout << "Cannot open the load file" << endl;
        return;
    }
    while(1) {
		if(this->type=="int"){
			DataInteger *ptr=new DataInteger();
			// int sz = fread((DataInteger *)ptr, sizeof(DataInteger), 1, readptr);
			int sz = fread(ptr, sizeof(ptr), 1, readptr);
            if(sz == 0) break;
            tr(typeid(ptr).name());
            tr("ptr value:");
            tr(ptr->getInt());
			// this->column.push_back(ptr);
            // ptr->getInt();
            // tr(sz);
            // tr("Inside load column:");
            
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

void Column::close() {
    fn();
    writeFile();
}

void Column::showColumn() {
    fn();
    tr("column size : ");
    tr(this->column.size());
    tr(typeid(this->column.back()).name());
    for(int i=0;i< this->column.size();i++) {
        if(this->getType() == "int"){
            // cout << this->column[i]->getInt() << endl;
            // tr(this->column[i]->getInt());
        }
        // if(data->getType() == "string"){
        //     cout << data->getString() << endl;
        // }
        // if(data->getType() == "float"){
        //     cout << data->getFloat() << endl;
        // }
    }
}