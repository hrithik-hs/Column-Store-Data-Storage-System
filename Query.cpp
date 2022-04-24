#include "Query.h"


Query::Query(){}
Query::Query(string fileName,string type){
	// cerr<<"Query"<<endl;
    this->fileName=fileName;
    this->type=type;
    this->parseQuery();
}
Query::~Query(){}

// code
void Query::parseInsertQuery(){
	xml_document<> doc;
    xml_node<> * root_node = NULL;

    ifstream theFile (this->fileName);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
   
	root_node = doc.first_node("root");
	for (xml_node<> * database_node = root_node->first_node("Database"); database_node; database_node = database_node->next_sibling()){
		
		string dbName="";
		if(database_node->first_attribute("name"))
			dbName=database_node->first_attribute("name")->value();
		else ;

		struct DatabaseInsert databaseInsert;
		databaseInsert.databaseName=dbName;

		for (xml_node<> * table_node = database_node->first_node("Table"); table_node; table_node = table_node->next_sibling()){
			string tableName="";
			if(table_node->first_attribute("name"))
				tableName=table_node->first_attribute("name")->value();
			
			struct TableInsert tableInsert;
			tableInsert.tableName=tableName;
			
			for (xml_node<> * insert_node = table_node->first_node("Insert"); insert_node; insert_node = insert_node->next_sibling()){
				struct InsertRow row;
				for(xml_node<> * column_node = insert_node->first_node("Column"); column_node; column_node = column_node->next_sibling()){
					string columnName="";
					if(column_node->first_attribute("name"))
						columnName=column_node->first_attribute("name")->value();
					string columnValue="";
            		columnValue=column_node->value();

					row.columnNames.push_back(columnName);
					row.columnValues.push_back(columnValue);
				}
				tableInsert.rows.push_back(row);
			}
			databaseInsert.tableInserts.push_back(tableInsert);
		}
		this->databaseInserts.push_back(databaseInsert);
	}
}
void Query::parseCreateQuery(){
	xml_document<> doc;
	xml_node<> * root_node = NULL;

	ifstream theFile (this->fileName);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
   
	root_node = doc.first_node("root");
	for (xml_node<> * database_node = root_node->first_node("Database"); database_node; database_node = database_node->next_sibling()){
		
		string dbName="",block="";
		if(database_node->first_attribute("name"))
			dbName=database_node->first_attribute("name")->value();
		else ;
		if(database_node->first_attribute("block"))
			block=database_node->first_attribute("block")->value();
		else ;

		struct DatabaseCreate databaseCreate;
		databaseCreate.databaseName=dbName;
		databaseCreate.blockSize=block;

		//cerr<<"DB name: "<<dbName<<endl;

		for (xml_node<> * table_node = database_node->first_node("Table"); table_node; table_node = table_node->next_sibling()){
			string tableName="";
			if(table_node->first_attribute("name"))
				tableName=table_node->first_attribute("name")->value();
			//cerr<<"\tTable name: "<<tableName<<endl;

			struct TableCreate tableCreate;
			tableCreate.tableName=tableName;

			for(xml_node<> * column_node = table_node->first_node("Column"); column_node; column_node = column_node->next_sibling()){
				string columnName="";
				if(column_node->first_attribute("name"))
					columnName=column_node->first_attribute("name")->value();
				string columnType="";
				if(column_node->first_attribute("type"))
					columnType=column_node->first_attribute("type")->value();
				string columnConstraints="";
				if(column_node->first_attribute("constraints"))
					columnConstraints=column_node->first_attribute("constraints")->value();

				struct ColumnCreate columnCreate;
				columnCreate.columnName=columnName;
				columnCreate.columnType=columnType;
				columnCreate.isUniqueConstraint=0;
				columnCreate.isPrimaryConstraint=0;

				if(columnConstraints=="P")columnCreate.isPrimaryConstraint=1;
				if(columnConstraints=="U")columnCreate.isUniqueConstraint=1;

				//cerr<<"\t\tColumn  name:      "<<columnName<<endl;
        		//cerr<<"\t\t        type:      "<<columnType<<endl;
        		//cerr<<"\t\t       const:      "<<columnConstraints<<endl;

        		tableCreate.columns.push_back(columnCreate);
			}
			databaseCreate.tables.push_back(tableCreate);
		}
		this->databaseCreates.push_back(databaseCreate);
	}
}

void Query::parseSelectQuery(){
    xml_document<> doc;
	xml_node<> * root_node = NULL;
	ifstream theFile (this->fileName);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
   
	root_node = doc.first_node("root");

	for (xml_node<> * database_node = root_node->first_node("Database"); database_node; database_node = database_node->next_sibling()){
		
		string dbName="";
		if(database_node->first_attribute("name"))
			dbName=database_node->first_attribute("name")->value();
		else ;

		// cerr<<"DB name: "<<dbName<<endl;

		struct DatabaseSelect databaseSelect;
		databaseSelect.databaseName=dbName;

		for (xml_node<> * table_node = database_node->first_node("Table"); table_node; table_node = table_node->next_sibling()){
			string tableName="";
			if(table_node->first_attribute("name"))
				tableName=table_node->first_attribute("name")->value();
			// cerr<<"\tTable name: "<<tableName<<endl;

			struct TableSelect tableSelect;
			tableSelect.tableName=tableName;

			for(xml_node<> * column_node = table_node->first_node("Column"); column_node; column_node = column_node->next_sibling()){
				string columnName="";
				if(column_node->first_attribute("name"))
					columnName=column_node->first_attribute("name")->value();
				// cerr<<"\t\tColumn  name:      "<<columnName<<endl;
				
				string columnValue="";
				bool flag=0;
				if(column_node->first_attribute("value")){
					columnValue=column_node->first_attribute("value")->value();
					flag=1;
				}
        		// if(flag)cerr<<"\t\t       Condnvalue:      "<<columnValue<<endl;

        		if(flag){
        			struct Condition condition;
					condition.columnName=columnName;
					condition.value=columnValue;
					tableSelect.conditions.push_back(condition);
        		}
        		else{
        			tableSelect.columnNames.push_back(columnName);
        		}
			}
			databaseSelect.tables.push_back(tableSelect);
		}
		this->databaseSelects.push_back(databaseSelect);
	}
}
void Query::parseDeleteQuery(){
    xml_document<> doc;
	xml_node<> * root_node = NULL;
	ifstream theFile (this->fileName);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
   
	root_node = doc.first_node("root");

	for (xml_node<> * database_node = root_node->first_node("Database"); database_node; database_node = database_node->next_sibling()){
		
		string dbName="";
		if(database_node->first_attribute("name"))
			dbName=database_node->first_attribute("name")->value();
		else ;

		// cerr<<"DB name: "<<dbName<<endl;

		struct DatabaseDelete databaseDelete;
		databaseDelete.databaseName=dbName;

		for (xml_node<> * table_node = database_node->first_node("Table"); table_node; table_node = table_node->next_sibling()){
			string tableName="";
			if(table_node->first_attribute("name"))
				tableName=table_node->first_attribute("name")->value();
			// cerr<<"\tTable name: "<<tableName<<endl;

			struct TableDelete tableDelete;
			tableDelete.tableName=tableName;

			for(xml_node<> * column_node = table_node->first_node("Column"); column_node; column_node = column_node->next_sibling()){
				string columnName="";
				if(column_node->first_attribute("name"))
					columnName=column_node->first_attribute("name")->value();
				// cerr<<"\t\tColumn  name:      "<<columnName<<endl;
				
				string columnValue="";
				if(column_node->first_attribute("value"))
					columnValue=column_node->first_attribute("value")->value();
        		// if(flag)cerr<<"\t\t       Condnvalue:      "<<columnValue<<endl;
    			struct Condition condition;
				condition.columnName=columnName;
				condition.value=columnValue;

				tableDelete.conditions.push_back(condition);
			}
			databaseDelete.tables.push_back(tableDelete);
		}
		this->databaseDeletes.push_back(databaseDelete);
	}
}

void Query::parseQuery(){
    if(this->type=="create"){
        this->parseCreateQuery();
    }
    else if(this->type=="insert"){
        this->parseInsertQuery();
    }
    else if(this->type=="select"){
        this->parseSelectQuery();
    }
    else if(this->type=="delete"){
        this->parseDeleteQuery();
    }
    else cerr<<"Query Type Inconsistent"<<endl;
}

void Query::setFileName(string fileName){
    this->fileName=fileName;
}
void Query::setType(string Type){
    this->type=type;
}

string Query::getFileName(){
    return this->fileName;
}
string Query::getType(){
    return this->type;
}

vector<DatabaseInsert> Query::getDatabaseInserts(){
    return this->databaseInserts;
}
vector<DatabaseCreate> Query::getDatabaseCreates(){
    return this->databaseCreates;
}
vector<DatabaseSelect> Query::getDatabaseSelects(){
    return this->databaseSelects;
}
vector<DatabaseDelete> Query::getDatabaseDeletes(){
    return this->databaseDeletes;
}