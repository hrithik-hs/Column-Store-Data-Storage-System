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
    // fn();
    Database * database=new Database("Sample","./File");
    // database->show();
    database->createTable("Emp");
    database->addColumn("Emp","EmpID","int");
    database->addColumn("Emp","Name","string");
    database->addColumn("Emp","Salary","float");
    // cerr<<"create success\n";
    // Row * row=new Row();
    // row->addElement(1);
    // row->addElement("abc");
    // row->addElement(100.0f);
    // database->insertRow("Emp",row);

    // Row * row1=new Row();
    // row1->addElement(2);
    // row1->addElement("def");
    // row1->addElement(101.0f);
    // database->insertRow("Emp",row1);

    // Row * row2=new Row();
    // row2->addElement(3);
    // row2->addElement("ghi");
    // row2->addElement(102.0f);
    // database->insertRow("Emp",row2);


    cerr<<"\n----\n";
    database->show();

    database->close();
    delete database;
    // delete row;

    return 0;
}