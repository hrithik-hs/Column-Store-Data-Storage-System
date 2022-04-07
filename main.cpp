// #include <bits/stdc++.h>
#include <set>
#include <vector>
#include <iostream>

#include "Database.h"
#include "Row.h"
#define tr(X) cerr << X << endl;
#define fn() cerr<<__PRETTY_FUNCTION__<<endl;

using namespace std;

int main(){
    fn();
    Database * database=new Database("Sample","./File");
    database->createTable("Emp");
    database->addColumn("Emp","EmpID","int");

    cerr<<"create success\n";
    Row * row=new Row();
    row->addElement("int",1);
    // database->insertRow("Emp",row);
    // database->show();
    database->close();
    fn();
    delete database;
    delete row;

    return 0;
}