#include "Query.h"

Query::Query(){}
Query::Query(string query){
	this->query=query;
}

Query::~Query(){}


void Query::setQuery(string query){
	this->query=query;
}

string Query::getQuery(){
	return this->query;
}