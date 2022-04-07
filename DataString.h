#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include "Data.h"
using namespace std;

class DataString:public Data{
	private:
		char value[100];
        char type[100];
	public:
		DataString();
		~DataString();
        DataString(string value);

        void setValue(string value);
        string getString();
        string getType();
};