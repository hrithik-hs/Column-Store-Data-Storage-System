#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include "Data.h"
using namespace std;
#define endl "\n"

class DataInteger:public Data{
	private:
        char type[100];
		int value;

	public:
		DataInteger();
        DataInteger(int value);
        ~DataInteger();

        void setValue(int value);
        int getInt();
        string getType();
};