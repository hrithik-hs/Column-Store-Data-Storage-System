#include "Query.h"

Query::Query(){}
Query::Query(string fileName,string type){
    this->fileName=fileName;
    this->type=type;
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

		cerr<<"DB name: "<<dbName<<endl;

		for (xml_node<> * table_node = database_node->first_node("Table"); table_node; table_node = table_node->next_sibling()){
			string tableName="";
			if(table_node->first_attribute("name"))
				tableName=table_node->first_attribute("name")->value();
			cerr<<"\tTable name: "<<tableName<<endl;
			
			for (xml_node<> * insert_node = table_node->first_node("Insert"); insert_node; insert_node = insert_node->next_sibling()){
				cerr<<"\tInsert Node"<<endl;
				for(xml_node<> * column_node = insert_node->first_node("Column"); column_node; column_node = column_node->next_sibling()){
					string columnName="";
					if(column_node->first_attribute("name"))
						columnName=column_node->first_attribute("name")->value();
					// string columnType="";
					// if(column_node->first_attribute("type"))
					// 	columnType=column_node->first_attribute("type")->value();
					cerr<<"\t\tColumn name:      "<<columnName<<endl;
            		// cerr<<"\t\t       type:      "<<columnType;
            		string columnValue="";
            		columnValue=column_node->value();
					cerr<<"\t\tColumn Value:      "<<columnValue<<endl;
				}

			}
		}
	}
}
void Query::parseCreateQuery(){

}

void Query::parseQuery(){
    if(this->type=="create"){
        this->parseCreateQuery();
    }
    else if(this->type=="insert"){
        this->parseInsertQuery();
    }
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