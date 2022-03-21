#include <iostream>
#include <fstream>
#include <vector>

#include "rapidxml.hpp"
// #include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;


xml_document<> doc;
xml_node<> * root_node = NULL;
   
int main(){

	ifstream theFile ("sample.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	
	// Parse the buffer
	doc.parse<0>(&buffer[0]);
   
	// Find out the root node
	root_node = doc.first_node("Database");
	string dbName=root_node->first_attribute("name")->value();
	cout<<"DB Name "<<dbName<<endl;
    // cout<<root_node->first_node("Table")<<endl;
	// Iterate over the student nodes
	for (xml_node<> * table_node = root_node->first_node("Table"); table_node; table_node = table_node->next_sibling()){
		string tableName=table_node->first_attribute("name")->value();
		cout<<"\tTable Name "<<tableName<<endl;
		// Interate over the Student Names
		for(xml_node<> * column_node = table_node->first_node("Column"); column_node; column_node = column_node->next_sibling()){
			string columnName=column_node->first_attribute("name")->value();
			string columnType=column_node->first_attribute("type")->value();
			string columnLength="";
            if(column_node->first_attribute("length"))
                columnLength=column_node->first_attribute("length")->value();
			cout<<"\t\tColumn Name "<<columnName;
            cout<<"\n\t\t  Column Type "<<columnType;
            cout<<"\n\t\t  Column Length "<<columnLength<<endl;
		}
	}
	return 0;
}