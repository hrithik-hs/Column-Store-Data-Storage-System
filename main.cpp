#include <bits/stdc++.h>
#include "Database.h"
#include "Row.h"
#define tr(X) cerr << X << endl;
using namespace std;

int main(){
    tr(1);
    Database * database=new Database("Sample","./File");
    database->createTable("Emp");
    database->addColumn("Emp","EmpID","int");

    cerr<<"create success\n";
    Row * row=new Row();
    row->addElement("int",1);

    database->insertRow("Emp",row);

    delete database;

    return 0;
}