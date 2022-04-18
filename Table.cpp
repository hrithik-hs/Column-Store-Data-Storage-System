#include "Table.h"
#define tr(X) cerr<< X << endl;
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;
#include <typeinfo>

Table::Table(){}

Table::Table(string name, string address){
	this->name=name;
	this->address = address;
	this->loadFile();
}

// Table::Table(string name,vector<Column *> columns){
// 	this->name=name;
// 	this->columns=columns;
// 	for(auto column:columns){
// 		this->columnNames.insert
// 	}
// }
// Table::Table(string name,vector<Column *> columns, Column * primaryKey){
// 	this->name=name;
// 	this->columns=columns;
// 	this->primaryKey=primaryKey;
// }

Table::~Table(){
	while(!this->columns.empty()){
        // tr(this->columns.back());
		delete this->columns.back();
		this->columns.pop_back();
	}
    // delete this->ColumnRecords.back();
    while(!this->ColumnRecords.empty()){
        // tr(this->ColumnRecords.back());
        delete this->ColumnRecords.back();
		this->ColumnRecords.pop_back();
    }
	delete this->primaryKey;
    // fn();
}

void Table::loadFile(){
	string curAddress = this->address+'/'+this->name+".tb";
	string folderAddress = this->address+'/'+this->name;
	FILE* fptr = fopen(&curAddress[0], "r");
	int i=0;
	while(1){
	    ColumnRecord* ptr = new ColumnRecord();
		int sz=fread(ptr, sizeof(ColumnRecord), 1, fptr);
        if(sz==0)break;
		this->columnNames[(ptr->getColName())]=i;
		i++;

		Column* col=new Column(ptr->getColName(),folderAddress,ptr->getColType());
		this->columns.push_back(col);
		this->ColumnRecords.push_back(ptr);
		if(ptr->getIsPrimary()) this->primaryKey=this->columns.back();
	}
	this->flag.assign(this->ColumnRecords.size(), 0);
	fclose(fptr);
}

void Table::writeFile(){
	string curAddress = this->address+'/'+this->name+".tb";
	FILE* fptr = fopen(&(curAddress)[0], "w");
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] != NULL && this->flag[i] == 0) 
            fwrite(this->ColumnRecords[i],sizeof(ColumnRecord),1,fptr);
	}
	fclose(fptr);
}


void Table::addColumn(string columnName, string type){
	if(columnName.size() && this->columnNames.find(columnName)==this->columnNames.end()){
        this->columnNames[(columnName)]=this->columns.size();
		Column* col=new Column(columnName,this->address + "/" + this->name,type);
		
		this->columns.push_back(col);
		this->ColumnRecords.push_back(new ColumnRecord(columnName,type,0));
		string columnAddress = this->address+'/'+this->name+'/'+columnName+".col";
		FILE* fptr = fopen(&columnAddress[0], "w");
		fclose(fptr);
	}
    else{
        cerr << "Column Already Exists!" << endl;
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
	}
}

void Table::alterColumn(string oldName, string newName){ /*only for renaming*/
	if(this->columnNames.find(oldName)==this->columnNames.end() || this->columnNames.find(newName)!=this->columnNames.end()) return;
	string oldAddress = this->address+'/'+this->name+'/'+oldName+".col";
	string newAddress = this->address+'/'+this->name+'/'+newName+".col";
	int f=rename(&oldAddress[0],&newAddress[0]);
	if(f!=0) return;
	for(int i=0;i<this->ColumnRecords.size();i++){
		if(this->ColumnRecords[i] && this->ColumnRecords[i]->getColName()==oldName){
			this->ColumnRecords[i]->setColName(newName);
			this->columns[i]->setName(newName);
			this->columnNames[(newName)]=this->columnNames[(oldName)];
			this->columnNames.erase(oldName);
			break;
		}
	}
} 

void Table::showTable(){
	vector<pair<string,Data*>> conditions;
	vector<string> cols;
	for(auto column: this->columnNames) {
		cols.push_back(column.first);

    }
	cout<<endl;
	this->selectRows(cols,conditions);
	cout<<"Flag file"<<endl;
	string flagAddress = this->address+'/'+this->name+'/'+this->name+".flag";
	FILE* fptr = fopen(&flagAddress[0], "r");
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
	if(columnName.size() && this->columnNames.find(columnName)==this->columnNames.end()) return;

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
}

Column * Table::getPrimaryKey(){
	return this->primaryKey;
}

string Table::getName(){
	return this->name;
}

vector<Column *> Table::getColumns(){
	return this->columns;
}

void Table::insertRow(Row *row){
    if(row->getRow().size()!=this->columns.size()){
		return;
	}
	for(int i=0;i<row->getRow().size();i++){
		if(row->getRow()[i]->getType()!=this->columns[i]->getType()){
			return;
		}
	}
	string delAddress = this->address+'/'+this->name+'/'+this->name+".del";
	FILE* delptr = fopen(&delAddress[0], "r+");
	int delIndex;
	fseek(delptr,-1*sizeof(delIndex),SEEK_END);
	int sz=fread(&delIndex,sizeof(delIndex),1,delptr);
	if(sz==0) delIndex=-1;
	fs::path p{delAddress};
	ftruncate(fileno(delptr),fs::file_size(p)-4);
	// cout<<"delete file size: "<<fs::file_size(p)<<endl;
	fclose(delptr);
	cout<<"Inserting into index: "<<delIndex<<endl;

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
	}

	string flagAddress = this->address+'/'+this->name+'/'+this->name+".flag";
	FILE* fptr = fopen(&flagAddress[0], "r+");
	int fl=0;
	if(delIndex!=-1) fseek(fptr,delIndex*sizeof(fl),SEEK_SET);
	else fseek(fptr,0,SEEK_END);
	sz=fwrite(&fl,sizeof(fl),1,fptr);
	if(!sz) cout<<"Error when writing into flag file"<<endl;
	fclose(fptr);
}

void Table::close() {
    writeFile();
	if(this->columns.size() == 0) return ;
    for(auto column: this->columns) {
        column->close();
    }
}
// template <typename T1,typename T2>
// void Table::updateRow(string columnName,T1 newValue, string comparisionColumn, T2 comparisionValue){

// }

// template <typename T>
// void Table::deleteRow(string comparisionColumn,T comparisionValue){
    
// }


void Table::selectRows(vector<string> cols, vector<pair<string,Data*>> conditions){
	int block=-1,flag=1;
	for(auto col:cols) cout<<col<<"\t";
	cout<<endl;
	string flagAddress = this->address+'/'+this->name+'/'+this->name+".flag";
	FILE* fptr = fopen(&flagAddress[0], "r");
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
			}
		}
		// cout<<"Printing index array for block "<<block<<":"<<endl;
		// for(int i=0;i<index.size();i++) cout<<index[i]<<' ';
		// cout<<endl;
		if(index.size()==0) continue;
		vector<string> colType;
		vector<vector<Data*>> ans;
		for(int i=0;i<cols.size();i++){
			int colIndex = this->columnNames[cols[i]];
			colType.push_back(this->columns[colIndex]->getType());
			ans.push_back(this->columns[colIndex]->selectRows(block,index));
		}
		for(int j=0;j<index.size();j++){
			for(int i=0;i<cols.size();i++){
				if(colType[i]=="int") cout<<ans[i][j]->getInt()<<"\t";
				else if(colType[i]=="float") cout<<ans[i][j]->getFloat()<<"\t";
				if(colType[i]=="string") cout<<string(ans[i][j]->getString())<<"\t";
			}
			cout<<endl;
		}
	}
	fclose(fptr);
}

void Table::deleteRows(vector<pair<string,Data*>> conditions){
	int block=-1,flag=1;
	string flagAddress = this->address+'/'+this->name+'/'+this->name+".flag";
	string delAddress = this->address+'/'+this->name+'/'+this->name+".del";
	FILE* fptr = fopen(&flagAddress[0], "r+");
	FILE* delptr = fopen(&delAddress[0], "a");
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
			}
		}
		// cout<<"Printing index array in deletion for block "<<block<<":"<<endl;
		// for(int i=0;i<index.size();i++) cout<<index[i]<<' ';
		// cout<<endl;
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
}

