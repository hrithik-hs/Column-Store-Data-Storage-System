#include <set>
#include <vector>
#include <iostream>

#include "Database.h"
#include "Row.h"

void init(Database* database) {
    cerr << "Database" << endl;
    // Create table Emp[EmpID(int), Name(string), Salary(float)].
    database->createTable("Emp");
    database->addColumn("Emp","EmpID","int");
    database->addColumn("Emp","Name","string");
    database->addColumn("Emp","Salary","float");
    // Create table Dept[DeptName(enum), EmpID(int)].
    database->createTable("Dept");
    database->addColumn("Dept", "EmpID", "int");
    database->addColumn("Dept", "DeptName", "enum"); 
    // Fill Data in Emp Table.
    Row *EmpRow1 = new Row();
    EmpRow1->addElement(1);
    EmpRow1->addElement("E1");
    EmpRow1->addElement(10000.0f);

    Row *EmpRow2 = new Row();
    EmpRow2->addElement(2);
    EmpRow2->addElement("E2");
    EmpRow2->addElement(20000.0f);

    Row *EmpRow3 = new Row();
    EmpRow3->addElement(3);
    EmpRow3->addElement("E3");
    EmpRow3->addElement(30000.0f);

    Row *EmpRow4 = new Row();
    EmpRow4->addElement(4);
    EmpRow4->addElement("E4");
    EmpRow4->addElement(40000.0f);

    database->insertRow("Emp", EmpRow1);
    database->insertRow("Emp", EmpRow2);
    database->insertRow("Emp", EmpRow3);
    database->insertRow("Emp", EmpRow4);

    // Fill Data in Dept table.
    Row *DeptRow1 = new Row();
    DeptRow1->addElement(1);
    DeptRow1->addElement("D1");

    Row *DeptRow2 = new Row();
    DeptRow2->addElement(2);
    DeptRow2->addElement("D2");

    Row *DeptRow3 = new Row();
    DeptRow3->addElement(3);
    DeptRow3->addElement("D3");

    Row *DeptRow4 = new Row();
    DeptRow4->addElement(4);
    DeptRow4->addElement("D4");

    database->insertRow("Dept", DeptRow1);
    database->insertRow("Dept", DeptRow2);
    database->insertRow("Dept", DeptRow3);
    database->insertRow("Dept", DeptRow4);

    cerr << "Database successfully created" << endl;
}

void printResult(int success) {
    if(success) {
        cout << "[+] Test Case Passed" << endl;
    }
    else {
        cout << "[-] Test Case Failed" << endl;
    }
}

int main() {
    Database* database = new Database("Sample", "./File");
    init(database);

    // Set EmpID in Emp as primary key and check Uniqueness constraint.
    database->setPrimaryKey("Emp", "EmpID");
    database->setIsUniqueConstraint("Emp", "EmpID", true);
    Row* testRow1 = new Row();
    testRow1->addElement(4);
    testRow1->addElement("E5");
    testRow1->addElement(60000.0f);
    int success = database->insertRow("Emp", testRow1);
    printResult(success == 0);

    // Check if data is stored correctly.
    vector<string> cols = {"EmpID", "Name", "Salary"};
    database->selectRows("Emp", cols, {});

    DataInteger* tempData = new DataInteger(1);
    database->deleteRows("Emp", {make_pair("EmpID", tempData)});
    database->selectRows("Emp", cols, {});
}