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
    cerr<<"create success\n";
    Row * row=new Row();
    row->addElement(1);
    row->addElement("abc");
    row->addElement(100.0f);
    database->insertRow("Emp",row);

    Row * row1=new Row();
    row1->addElement(2);
    row1->addElement("def");
    row1->addElement(101.0f);
    database->insertRow("Emp",row1);

    Row * row2=new Row();
    row2->addElement(3);
    row2->addElement("ghi");
    row2->addElement(102.0f);
    database->insertRow("Emp",row2);

    vector<string> cols={"EmpID","Name"};
    vector<pair<string,Data*>> conditions;
    database->selectRows("Emp",cols,conditions);
    DataInteger* data=new DataInteger(1);
    conditions.push_back({"EmpID",data});
    database->deleteRows("Emp",conditions);
    conditions.clear();
    database->selectRows("Emp",cols,conditions);

    Row * row3=new Row();
    row3->addElement(4);
    row3->addElement("jkl");
    row3->addElement(103.0f);
    database->insertRow("Emp",row3);



    cerr<<"\n----\n";
    database->show();

    database->close();
    cerr << "[+] Database Successfully Closed" << endl;
    delete database;
    cerr << "[+] Database Successfully Deleted" << endl;
    delete row;
    cerr << "[+] Row Successfully Deleted" << endl;
    delete row1;
    delete row2;
    delete row3;


    return 0;
}