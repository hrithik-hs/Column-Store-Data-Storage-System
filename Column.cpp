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
    // fn();
	while(!this->column.empty()){
        delete this->column.back();
		this->column.pop_back();
	}
}
void Column::writeFile(){
}

void Column::loadFile(){
}

void Column::insertValue(float value, int index){
    string file_source=this->address+"/"+this->name+".col";
    FILE* writeptr = fopen(&file_source[0], "r+");
    if(index!=-1) fseek(writeptr,index*sizeof(value),SEEK_SET);
    else fseek(writeptr,0,SEEK_END);
    int sz=fwrite(&value,sizeof(value),1,writeptr);
    fclose(writeptr);
}
void Column::insertValue(int value, int index){
    string file_source=this->address+"/"+this->name+".col";
    FILE* writeptr = fopen(&file_source[0], "r+");
    if(index!=-1) fseek(writeptr,index*sizeof(value),SEEK_SET);
    else fseek(writeptr,0,SEEK_END);
    int sz=fwrite(&value,sizeof(value),1,writeptr);
    fclose(writeptr);
}
void Column::insertValue(string value, int index){
    char writeData[100];
    strcpy(writeData,value.c_str());
    string file_source=this->address+"/"+this->name+".col";
    FILE* writeptr = fopen(&file_source[0], "r+");
    if(index!=-1) fseek(writeptr,index*sizeof(writeData),SEEK_SET);
    else fseek(writeptr,0,SEEK_END);
    int sz=fwrite(&writeData,sizeof(writeData),1,writeptr);
    fclose(writeptr);
}

// void Column::deleteValue(int index){
// 	if(index <this->column.size() && index >=0)
// 		this->column[index]=NULL;
// }

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
    writeFile();
}

vector<int> Column::selectRows(int block,int value, vector<int> index){
    if(index.size()==0) return index;
    string file_source=this->address+"/"+this->name+".col";
    FILE* readptr = fopen(&file_source[0], "r");
    // if(!readptr) {
    //     cout << "Cannot open the load file" << endl;
    //     return;
    // }
    vector<int> ans;
    for(int i=0;i<index.size();i++){
        fseek(readptr,(block*blockSize + index[i])*sizeof(int),SEEK_SET);
        int readData;
		int sz = fread(&readData, sizeof(readData), 1, readptr);
        if(readData==value) ans.push_back(index[i]);    
    }
    fclose(readptr);
    return ans;
}
vector<int> Column::selectRows(int block,float value, vector<int> index){
    if(index.size()==0) return index;
    string file_source=this->address+"/"+this->name+".col";
    FILE* readptr = fopen(&file_source[0], "r");
    // if(!readptr) {
    //     cout << "Cannot open the load file" << endl;
    //     return;
    // }
    vector<int> ans;
    for(int i=0;i<index.size();i++){
        fseek(readptr,(block*blockSize + index[i])*sizeof(float),SEEK_SET);
        float readData;
		int sz = fread(&readData, sizeof(readData), 1, readptr);
        if(readData==value) ans.push_back(index[i]);    
    }
    fclose(readptr);
    return ans;
}
vector<int> Column::selectRows(int block,string value, vector<int> index){
    if(index.size()==0) return index;
    string file_source=this->address+"/"+this->name+".col";
    FILE* readptr = fopen(&file_source[0], "r");
    // if(!readptr) {
    //     cout << "Cannot open the load file" << endl;
    //     return;
    // }
    vector<int> ans;
    for(int i=0;i<index.size();i++){
        char readData[100];
        fseek(readptr,(block*blockSize + index[i])*sizeof(readData),SEEK_SET);
		int sz = fread(&readData, sizeof(readData), 1, readptr);
        if(string(readData)==value) ans.push_back(index[i]);    
    }
    fclose(readptr);
    return ans;
}

vector<Data*> Column::selectRows(int block, vector<int> index){
    vector<Data*> ans;
    string file_source=this->address+"/"+this->name+".col";
    FILE* readptr = fopen(&file_source[0], "r");
    if(this->type == "int"){
        for(int i=0;i<index.size();i++){
            fseek(readptr,(block*blockSize + index[i])*sizeof(int),SEEK_SET);
            int readData;
            int sz = fread(&readData, sizeof(readData), 1, readptr);
            DataInteger *ptr=new DataInteger(readData);
            ans.push_back(ptr);
        }
    }
    else if(this->type == "float"){
        for(int i=0;i<index.size();i++){
            fseek(readptr,(block*blockSize + index[i])*sizeof(float),SEEK_SET);
            float readData;
            int sz = fread(&readData, sizeof(readData), 1, readptr);
            DataFloat *ptr=new DataFloat(readData);
            ans.push_back(ptr);
        }
    }
    else if(this->type == "string"){
        for(int i=0;i<index.size();i++){
            char readData[100];
            fseek(readptr,(block*blockSize + index[i])*sizeof(readData),SEEK_SET);
            int sz = fread(&readData, sizeof(readData), 1, readptr);
            DataString *ptr=new DataString(readData);
            ans.push_back(ptr);
        }
    }
    fclose(readptr);
    return ans;
}