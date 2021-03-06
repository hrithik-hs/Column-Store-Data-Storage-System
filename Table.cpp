#include "Table.h"
#define tr(X) cerr<< X << endl;
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;
#include <typeinfo>

Table::Table(){}

Table::Table(string name, int blockSize, string address){
	this->name=name;
	this->blockSize = blockSize;
	this->address = address;
	int fl = this->loadFile();
	if(fl) cout << "[ T+ ] [ Constructor ] Table open successfull." << endl;
	else cout << "[ T- ] [ Constructor ] Table open failed." << endl;
}

Table::~Table(){
	for(int i = 0; i < this->columns.size(); i ++) {
		delete this->columns[i];
	}
	for(int i = 0; i < this->ColumnRecords.size(); i ++) {
		delete this->ColumnRecords[i];
	}
	cout << "[ T+ ] [ Destructor ] Table close successfull." << endl;
}

int Table::loadFile(){
	string curAddress = this->address+'/'+this->name+".tb";
	string folderAddress = this->address+'/'+this->name;
	FILE* fptr = fopen(&curAddress[0], "r");
	if(!fptr) {
        cout << "[ T- ] [ Load table ] Cannot open column record file for " << this->name << " table." << endl;
        return 0;
    }
	int ind=0;
	while(1){
	    ColumnRecord* ptr = new ColumnRecord();
		int sz=fread(ptr, sizeof(ColumnRecord), 1, fptr);
        if(sz==0)break;
		this->columnNames[(ptr->getColName())]=ind;
		ind++;
		Column* col=new Column(ptr->getColName(), this->blockSize ,folderAddress,ptr->getColType());
		this->columns.push_back(col);
		this->ColumnRecords.push_back(ptr);
		if(ptr->getIsPrimary()) this->primaryKey=this->columns.back();
	}
	fclose(fptr);
	return 1;
}

int Table::writeFile(){
	string curAddress = this->address+'/'+this->name+".tb";
	FILE* fptr = fopen(&(curAddress)[0], "wb");
	if(!fptr) {
        cout << "[ T- ] [ Write table ] Cannot open column record file for " << this->name << " table." << endl;
        return 0;
    }
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] != NULL) 
            fwrite(this->ColumnRecords[i],sizeof(ColumnRecord),1,fptr);
	}
	fclose(fptr);
	return 1;
}


void Table::addColumn(string columnName, string type){
	if(columnName.size() && this->columnNames.find(columnName)==this->columnNames.end()){
        this->columnNames[(columnName)]=this->columns.size();
		Column* col=new Column(columnName, this->blockSize ,this->address + "/" + this->name,type);
		this->columns.push_back(col);
		this->ColumnRecords.push_back(new ColumnRecord(columnName,type,0));
		if(type == "enum") {
			for(int i = 0; i < 10; i ++) {
				string columnAddress = this->address + "/" + this->name + "/" + columnName + "_" + to_string(i) + ".col";
				FILE* fptr = fopen(&columnAddress[0], "w");
				if(!fptr) {
					cout << "[ T- ] [ Add column ] Cannot create file for " << columnName << " column." << endl;
					return;
				}
				fclose(fptr);
			}
		}
		else {
			string columnAddress = this->address + '/' + this->name + '/' + columnName + ".col";
			FILE* fptr = fopen(&columnAddress[0], "w");
			if(!fptr) {
				cout << "[ T- ] [ Add column ] Cannot create file for " << columnName << " column." << endl;
				return;
			}
			fclose(fptr);
		}
		cout << "[ T+ ] [ Add column ] Column creation successfull. Name: "<< columnName << endl;
	}
    else{
        cout << "[ T! Warning ] [ Add column ] Column already exists with given name: " << columnName << endl;
    }
}

void Table::dropColumn(string columnName){
	if(this->columnNames.find(columnName)!=this->columnNames.end()){
		for(int i=0;i<this->columns.size();i++){
			if(this->columns[i]->getName()==columnName){
				this->columns[i]=NULL;
				this->ColumnRecords[i]=NULL;
				break;
			}
		}
		this->columnNames.erase(columnName);
		cout << "[ T+ ] [ Drop column ] Column drop successfull. Name: "<< columnName << endl;
	}
	else cout << "[ T! Warning ] [ Drop column ] Column doesn't exists with given name: " << columnName << endl;
}

void Table::alterColumn(string oldName, string newName){ /*only for renaming*/
	if(this->columnNames.find(oldName)==this->columnNames.end() || this->columnNames.find(newName)!=this->columnNames.end()) return;
	string coltype;
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getColName()==oldName){
			coltype = this->columns[i]->getType();
			this->ColumnRecords[i]->setColName(newName);
			this->columns[i]->setName(newName);
			this->columnNames[(newName)]=this->columnNames[(oldName)];
			this->columnNames.erase(oldName);
			break;
		}
	}
	if(coltype != "enum") {
		string oldAddress = this->address + '/' + this->name + '/' + oldName + ".col";
		string newAddress = this->address + '/' + this->name + '/' + newName + ".col";
		int f = rename(&oldAddress[0],&newAddress[0]);
		if(f!=0) cout << "[ T- ] [ Alter column ] Cannot rename file for " << oldName << " column." << endl;
		return;
	}
	else {
		for(int i = 0; i < 10; i ++) {
			string oldAddress = this->address + '/' + this->name + '/' + oldName + "_" + to_string(i) + ".col";
			string newAddress = this->address + '/' + this->name + '/' + newName + "_" + to_string(i) + ".col";
			int f = rename(&oldAddress[0], &newAddress[0]);
			if(f != 0) cout << "[ T- ] [ Alter column ] Cannot rename file for " << oldName << " column." << endl;
		}
	}
	cout << "[ T+ ] [ Alter column ] Alter column successfull for " << newName << " column." << endl;
} 

void Table::showTable(){
	vector<pair<string,Data*>> conditions;
	vector<string> cols;
	for(auto column: this->columnNames) {
		cols.push_back(column.first);

    }
	// cout<<endl;
	this->selectRows(cols,conditions);
	cout<<"Flag file"<<endl;
	string flagAddress = this->address+'/'+this->name+'/'+this->name+".flag";
	FILE* fptr = fopen(&flagAddress[0], "r");
	if(!fptr) {
        cout << "[ D- ] [ Show table ] Cannot open flag file for " << this->name << " database." << endl;
        return;
    }
	fseek(fptr,0,SEEK_SET);
	while(1){
		int fl=0;
		int sz = fread(&fl, sizeof(fl), 1, fptr);
        if(sz == 0) break;
		cout<<fl<<' ';
	}
	cout<<endl;
	fclose(fptr);
}

/*
void Table::setName(string newName){
	string oldAddress = this->address+'/'+this->name;
	string newAddress = this->address+'/'+newName;
	int f = rename(&oldAddress[0],&newAddress[0]);
	oldAddress+=".tb";
	newAddress+=".tb";
	f = rename(&oldAddress[0],&newAddress[0]);
	if(f==0) this->name = newName;
}
*/

void Table::setPrimaryKey(string columnName){
	if(columnName.size() && this->columnNames.find(columnName)==this->columnNames.end()){
		cout << "[ T! Warning ] [ Set primary ] Column doesn't exists with given name: " << columnName << endl;
		return;
	}

	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getIsPrimary()){
			this->ColumnRecords[i]->togIsPrimary();
			break;
		}
	}
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getColName()==columnName){
			this->ColumnRecords[i]->togIsPrimary();
			this->primaryKey = this->columns[i];
			break;
		}
	}
	int index = this->columnNames[columnName];
	this->columns[index]->setIsUniqueConstraint(true);
	cout << "[ T+ ] [ Set primary ] Set primary successfull for " << columnName << " column." << endl;
}

Column * Table::getPrimaryKey(){
	return this->primaryKey;
}

string Table::getName(){
	return this->name;
}

string Table::getColumnType(string columnName) {
	if(this->columnNames.count(columnName) == 0) {
		cout << "[ T- ][ getColumnType ] Column does not exists." << endl;
		return "";
	}
	int index = this->columnNames[columnName];
	return this->columns[index]->getType();
}

vector<Column *> Table::getColumns(){
	return this->columns;
}

int Table::insertRow(Row *row){
	string flagAddress = this->address+'/'+this->name+'/'+this->name+".flag";
    if(row->getRow().size()!=this->columns.size()){
		cout << "[ T- ] [ Insert row ] Unequal row size while inserting in " << this->name << " table." << endl;
		return 0;
	}
	for(int i=0;i<row->getRow().size();i++){
		if(row->getRow()[i]->getType() == "string" && this->columns[i]->getType() == "enum") {
			continue;
		}
		else if(row->getRow()[i]->getType()!=this->columns[i]->getType()){
			cout << "[ T- ] [ Insert row ] Unequal row type while inserting in " << this->name << " table." << endl;
			return 0;
		}
	}
	for(int i = 0; i < (int)(row->getRow().size()); i ++) {
		string type = row->getRow()[i]->getType();
		if(type == "int" || type == "float" || type == "string") {
			bool result = this->columns[i]->checkConstraints(row->getRow()[i], flagAddress);
			if(result == 0) {
				cout << "[ T- ] [ Insert row ] Row values violates constraints while inserting in " << this->name << " table." << endl;
				return 0;
			} 
		}
	}

	string delAddress = this->address+'/'+this->name+'/'+this->name+".del";
	FILE* delptr = fopen(&delAddress[0], "r+");
	if(!delptr) {
        cout << "[ T- ] [ Insert row ] Cannot open delete file for " << this->name << " table." << endl;
        return 0;
    }
	int delIndex;
	fseek(delptr,-1*sizeof(delIndex),SEEK_END);
	int sz=fread(&delIndex,sizeof(delIndex),1,delptr);
	if(sz==0) delIndex=-1;
	fs::path p{delAddress};
	ftruncate(fileno(delptr),fs::file_size(p)-4);
	fclose(delptr);

	for(int i=0;i<row->getRow().size();i++){
		if(this->columns[i]->getType()=="int"){
			this->columns[i]->insertValue(row->getRow()[i]->getInt(),delIndex);
		}
		else if(this->columns[i]->getType()=="float"){
			this->columns[i]->insertValue(row->getRow()[i]->getFloat(),delIndex);
		}
		else if(this->columns[i]->getType()=="string"){
			this->columns[i]->insertValue(row->getRow()[i]->getString(),delIndex);
		}
		else if(this->columns[i]->getType()=="enum") {
			string value = row->getRow()[i]->getString();
			vector<string> encoding = this->ColumnRecords[i]->getEncoding();
			this->columns[i]->insertValue(value, delIndex, this->ColumnRecords[i]->getEncoding());
			int found = -1;
			for(int j = 0; j < encoding.size(); j ++) {
				if(value == encoding[j]) {
					found = j;
					break;
				}
			}
            if(found == -1) {
                encoding.push_back(value);
                this->ColumnRecords[i]->setEncoding(encoding);
            }
		}
	}

	flagAddress = this->address+'/'+this->name+'/'+this->name+".flag";
	FILE* fptr = fopen(&flagAddress[0], "r+");
	if(!fptr) {
        cout << "[ T- ] [ Insert row ] Cannot open flag file for " << this->name << " table." << endl;
        return 0;
    }
	int fl=0;
	if(delIndex!=-1) fseek(fptr,delIndex*sizeof(fl),SEEK_SET);
	else fseek(fptr,0,SEEK_END);
	sz=fwrite(&fl,sizeof(fl),1,fptr);
	if(!sz) cout<<"[ T- ] [ Insert row ] Error when writing into flag file"<<endl;
	fclose(fptr);

	cout << "[ T+ ] [ Insert row ] Insert row successfull for " << this->name << " table." << endl;
	return 1;
}

int Table::close() {
    int fl = writeFile();
	if(!fl){
		cout << "[ T- ] [ Close table ] Close failed for " << this->name << " table." << endl;
		return 0;
	}
	// if(this->columns.size() == 0) return ;
    for(auto column: this->columns) {
        column->close();
    }
	cout << "[ T+ ] [ Close table ] Close successfull for " << this->name << " table." << endl;
	return 1;
}


int Table::selectRows(vector<string> cols, vector<pair<string,Data*>> conditions){
	int block=-1,flag=1;
	for(auto col:cols) cout<<col<<"\t";
	cout<<endl;
	string flagAddress = this->address+'/'+this->name+'/'+this->name+".flag";
	FILE* fptr = fopen(&flagAddress[0], "r");
	if(!fptr) {
        cout << "[ T- ] [ Select row ] Cannot open flag file for " << this->name << " table." << endl;
        return 0;
    }
	while(flag){
		block++;
		vector<int> index;
		for(int i=0;i<blockSize;i++){
			int fl;
			int sz = fread(&fl, sizeof(fl), 1, fptr);
			if(sz == 0){
				flag=0;
				break;
			}
			if(!fl) {
                index.push_back(i);
            }
		}
		if(conditions.size()){
			for(int i=0;i<conditions.size();i++){
				int colIndex = this->columnNames[conditions[i].first];
				if(this->columns[colIndex]->getType()=="int"){
					index = this->columns[colIndex]->selectRows(block,conditions[i].second->getInt(),index);
				}
				else if(this->columns[colIndex]->getType()=="float"){
					index = this->columns[colIndex]->selectRows(block,conditions[i].second->getFloat(),index);
				}
				else if(this->columns[colIndex]->getType()=="string"){
					index = this->columns[colIndex]->selectRows(block,conditions[i].second->getString(),index);
				}
                else if(this->columns[colIndex]->getType()=="enum"){
					index = this->columns[colIndex]->selectRows(block,conditions[i].second->getString(),index, this->ColumnRecords[colIndex]->getEncoding());
				}
			}
		}
		if(index.size()==0) continue;
		vector<string> colType;
		vector<vector<Data*>> ans;
		for(int i=0;i<cols.size();i++){
			int colIndex = this->columnNames[cols[i]];
			colType.push_back(this->columns[colIndex]->getType());
            if(colType.back() != "enum") {
			    ans.push_back(this->columns[colIndex]->selectRows(block,index));
            }
            else {
                ans.push_back(this->columns[colIndex]->selectRows(block,index, this->ColumnRecords[colIndex]->getEncoding()));
            }
		}
		for(int j=0;j<index.size();j++){
			for(int i=0;i<cols.size();i++){
				if(colType[i]=="int") cout<< ans[i][j]->getInt() <<"\t";
				else if(colType[i]=="float") cout<< ans[i][j]->getFloat() << "\t";
				if(colType[i]=="string" || colType[i] == "enum") cout<<string(ans[i][j]->getString())<< "\t";
			}
			cout<<endl;
		}
	}
	fclose(fptr);
	return 1;
}

int Table::deleteRows(vector<pair<string,Data*>> conditions){
	int block=-1,flag=1;
	string flagAddress = this->address+'/'+this->name+'/'+this->name+".flag";
	string delAddress = this->address+'/'+this->name+'/'+this->name+".del";
	FILE* fptr = fopen(&flagAddress[0], "r+");
	if(!fptr) {
        cout << "[ T- ] [ Delete row ] Cannot open flag file for " << this->name << " table." << endl;
        return 0;
    }
	FILE* delptr = fopen(&delAddress[0], "a");
	if(!delptr) {
        cout << "[ T- ] [ Delete row ] Cannot open delete file for " << this->name << " table." << endl;
        return 0;
    }
	while(flag){
		block++;
		fseek(fptr,(block*blockSize)*sizeof(int),SEEK_SET);
		vector<int> index;
		for(int i=0;i<blockSize;i++){
			int fl;
			int sz = fread(&fl, sizeof(fl), 1, fptr);
			if(sz == 0){
				flag=0;
				break;
			}
			if(!fl) index.push_back(i);
		}
		if(conditions.size()){
			for(int i=0;i<conditions.size();i++){
				int colIndex = this->columnNames[conditions[i].first];
				if(this->columns[colIndex]->getType()=="int"){
					index = this->columns[colIndex]->selectRows(block,conditions[i].second->getInt(),index);
				}
				else if(this->columns[colIndex]->getType()=="float"){
					index = this->columns[colIndex]->selectRows(block,conditions[i].second->getFloat(),index);
				}
				else if(this->columns[colIndex]->getType()=="string"){
					index = this->columns[colIndex]->selectRows(block,conditions[i].second->getString(),index);
				}
                else if(this->columns[colIndex]->getType()=="enum"){
					index = this->columns[colIndex]->selectRows(block,conditions[i].second->getString(),index, this->ColumnRecords[colIndex]->getEncoding());
				}
			}
		}
		if(index.size()==0) continue;
		int fl=1;
		for(int i=0;i<index.size();i++){
			int offset=(block*blockSize + index[i]);
			fwrite(&offset,sizeof(offset),1,delptr);
			fseek(fptr,offset*sizeof(fl),SEEK_SET);
			int sz=fwrite(&fl,sizeof(fl),1,fptr);
		}
	}
	fclose(fptr);
	fclose(delptr);
	return 1;
}

void Table::setIsUniqueConstraint(string columnName, bool value) {
	if(this->columnNames.find(columnName) == this->columnNames.end()) {
		cout << "[ T- ] [ Set constraint ] Column Does not Exists. Uniqueness Constraint cannot be added." << endl;
		return;
	}
	int index = this->columnNames[columnName];
	this->columns[index]->setIsUniqueConstraint(value);
	cout << "[ T+ ] [ Set constraint ] Uniqueness Constraint set successfully." << endl;
}
