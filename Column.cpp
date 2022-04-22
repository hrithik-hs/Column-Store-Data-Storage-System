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
    // cerr << "DOG " << this->type << endl;
    this->loadFile();
}

Column::~Column(){
    // fn();
	for(int i = 0; i < this->column.size(); i ++) {
		delete this->column[i];
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

void Column::insertValue(string value, int index, vector<string> encoding) {
    bool writeData = true;
    int found = -1;
    for(int i = 0; i < encoding.size(); i ++) {
        if(value == encoding[i]) {
            found = i;
            break;
        }
    }
    if(found == -1) {
        if(encoding.size() == 0) {
            found = 0;
        }
        else {
            string file_source1 = this->address + "/" + this->name + "_0" + ".col";
            string file_source2 = this->address + "/" + this->name + "_" + to_string(encoding.size()) + ".col";
            FILE* fptr1 = fopen(&file_source1[0], "r+");
            bool data = 0;
            int count = 0;
            while(true) {
                int sz = fread(&data, sizeof(data), 1, fptr1);
                if(sz == 0) break;
                count ++;
            }
            fclose(fptr1);
            FILE* fptr2 = fopen(&file_source2[0], "r+");
            for(int i = 0; i < count; i ++) {
                int sz = fwrite(&data, sizeof(data), 1, fptr2);
            }
            fclose(fptr2);
            found = encoding.size();
        }
        encoding.push_back(value);
    }
    for(int i = 0; i < encoding.size(); i ++) {
        string file_source = this->address + "/" + this->name + "_" + to_string(i) + ".col";
        FILE* writeptr = fopen(&file_source[0], "r+");
        bool writeData = (i == found);
        if(index != -1) {
            fseek(writeptr, index*sizeof(writeData), SEEK_SET);
        }
        else fseek(writeptr, 0, SEEK_END);
        int sz = fwrite(&writeData, sizeof(writeData), 1, writeptr);
        fclose(writeptr);
    }
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


void Column::setIsUniqueConstraint(bool value) {
    this->isUnique = value;
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

vector<int> Column::selectRows(int block, string value, vector<int> index, vector<string> encoding) {
    if(index.size() == 0) return index;
    int found = -1;
    for(int i = 0; i < encoding.size(); i ++) {
        if(value == encoding[i]) {
            found = i;
            break;
        }
    }
    if(found == -1) return vector<int>();
    string file_source = this->address + "/" + this->name + "_" + to_string(found) + ".col";
    FILE* readptr = fopen(&file_source[0], "r");
    vector<int> ans;
    for(int i = 0; i < index.size(); i ++) {
        bool readData;
        fseek(readptr, (block * blockSize + index[i]) * sizeof(readData), SEEK_SET);
        int sz = fread(&readData, sizeof(readData), 1, readptr);
        if(readData) ans.push_back(index[i]);
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

vector<Data*> Column::selectRows(int block, vector<int> index, vector<string> encoding){
    vector<Data*> ans;
    vector<FILE* > rptr;
    for(int i = 0; i < encoding.size(); i ++) {
        string file_name = this->address + "/" + this->name + "_" + to_string(i) + ".col";
        rptr.push_back(fopen(&file_name[0], "r"));
    }
    for(int i = 0; i < index.size(); i ++) {
        bool readData[10];
        for(int j = 0; j < encoding.size(); j ++) {
            fseek(rptr[j], (block * blockSize + index[i]) * sizeof(bool), SEEK_SET);
            int sz = fread(&(readData[j]), sizeof(readData[j]), 1, rptr[j]);
        }
        char value[100];
        for(int j = 0; j < encoding.size(); j ++) {
            if(readData[j]) {
                strcpy(value, encoding[j].c_str());
                break;
            }
        }
        DataString *ptr = new DataString(value);
        ans.push_back(ptr);
    }
    return ans;
}
bool Column::checkConstraints(Data* data) {
    if(this->isUnique == true) {
        bool flag = 0;
        if(data->getType() == "int") {
            flag = checkIsUniqueConstraint(data->getInt());
        }
        else if(data->getType() == "float") {
            flag = checkIsUniqueConstraint(data->getFloat());
        }
        else if(data->getType() == "string") {
            flag = checkIsUniqueConstraint(data->getString());
        }
        if(flag) {
            cout << "[+] Uniqueness constraint verified." << endl;
        }
        else {
            cout << "[-] Uniqueness constraint violated." << endl;
            return false;
        }
    }
    return true;
}

bool Column::checkIsUniqueConstraint(int value) {
    string file_source=this->address+"/"+this->name+".col";
    FILE* readptr = fopen(&file_source[0], "r");
    while(1) {
        int data;
        int sz = fread(&data, sizeof(data), 1, readptr);
        if(sz == 0) break;
        if(data == value) return false;
    }
    return true;
}

bool Column::checkIsUniqueConstraint(float value) {
    string file_source=this->address+"/"+this->name+".col";
    FILE* readptr = fopen(&file_source[0], "r");
    while(1) {
        float data;
        int sz = fread(&data, sizeof(data), 1, readptr);
        if(sz == 0) break;
        if(data == value) return false;
    }
    return true;
}

bool Column::checkIsUniqueConstraint(string value) {
    string file_source=this->address+"/"+this->name+".col";
    FILE* readptr = fopen(&file_source[0], "r");
    while(1) {
        char data[100];
        int sz = fread(&data, sizeof(data), 1, readptr);
        if(sz == 0) break;
        if(data == value) return false;
    }
    return true;
}
