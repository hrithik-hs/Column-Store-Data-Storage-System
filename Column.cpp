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
// Column::Column(string name,string address,string type){
// 	this->name=name;
//     this->address=address;
// 	this->type=type;
//     this->loadFile();
// }

Column::Column(string name,string address,string type,bool primary=0, bool unique=0, bool notNull=0){
	this->name=name;
    this->address=address;
	this->type=type;
    this->primary = primary;
    this->unique=unique;
    this->notNull=notNull;
    if(primary){
        this->unique=1;
        this->notNull=1;
    }
    this->loadFile();
}

Column::~Column(){
    // fn();
	while(!this->column.empty()){
		// tr((this->column.back()==NULL));
		// tr((this->column.back()));
        // tr(typeid((DataInteger *)this->column.back()).name());
        // tr((DataInteger *)this->column.back()->getInt());
        delete this->column.back();
        // tr(1);
		this->column.pop_back();
	}
    // fn();
}

void Column::writeFile(){
    // fn();
    // cerr << "WriteFileColumn " << this->name << " " << this->address << endl;
	string file_source=this->address+"/"+this->name+".col";
    FILE* writeptr = fopen(&file_source[0], "w");
    if(!writeptr) {
        cout << "Cannot open the write file" << endl;
        return;
    }
    
    for(int i = 0; i < column.size(); i ++) {
       
		if(this->type=="int"){
            int writeData=this->column[i]->getInt();
            int sz=fwrite(&writeData,sizeof(writeData),1,writeptr);
            // tr("Write size:");
            // tr(sz);
		}
		else if(this->type=="float"){
            float writeData=this->column[i]->getFloat();
            int sz=fwrite(&writeData,sizeof(writeData),1,writeptr);

		}
		else if(this->type=="string"){
            char writeData[100];
            strcpy(writeData,this->column[i]->getString().c_str());
            int sz=fwrite(&writeData,sizeof(writeData),1,writeptr);
		}
        
    }
    fclose(writeptr);
}

void Column::loadFile(){
    // fn();
	string file_source=this->address+"/"+this->name+".col";
    FILE* readptr = fopen(&file_source[0], "r");
    if(!readptr) {
        cout << "Cannot open the load file" << endl;
        return;
    }
    while(1) {
		if(this->type=="int"){
			int readData;
			int sz = fread(&readData, sizeof(readData), 1, readptr);
            if(sz == 0) break;
            DataInteger *ptr=new DataInteger(readData);
			this->column.push_back(ptr);

            // tr(ptr->getInt());
            // ptr->getInt();
            // tr(sz);
            // tr("Inside load column:");
            
		}
		else if(this->type=="float"){
			float readData;
			int sz = fread(&readData, sizeof(readData), 1, readptr);
            if(sz == 0) break;
            Data *ptr = new DataFloat(readData);
			column.push_back(ptr);
		}
		else if(this->type=="string"){

			// string readData;
            char readData[100];
			int sz = fread(&readData, sizeof(readData), 1, readptr);
            if(sz == 0) break;
            Data *ptr = new DataString(readData);
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

bool Column::checkConstraint(Data * data,vector<bool>flag){
    if(this->notNull && !data)return 0;
    if(!data)return 1;
    if(this->unique){
        for(int i=0;i<this->column.size();i++){
            if(flag[i])continue;
            if(this->type=="int" && this->column[i]->getInt()==data->getInt())return 0;
            if(this->type=="float" && this->column[i]->getFloat()==data->getFloat())return 0;
            if(this->type=="string" && this->column[i]->getString()==data->getString())return 0;
        }
    }
    return 1;
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
    writeFile();
}

void Column::showColumn() {
    // fn();
    // tr("column size : ");
    // tr(this->column.size());
    // tr(typeid(this->column.back()).name());
    for(int i=0;i< this->column.size();i++) {
        if(this->getType() == "int"){
            cout << this->column[i]->getInt() << " ";
            // tr(this->column[i]->getInt());
        }
        if(this->getType() == "string"){
            cout << this->column[i]->getString() << " ";
        }
        if(this->getType() == "float"){
            cout << this->column[i]->getFloat() << " ";
        }
    }
    cout<<endl;
}