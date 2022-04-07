#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include "Data.h"
using namespace std;

class DataFloat:public Data{
	private:
        char type[100];
		float value;
	public:
		DataFloat();
		~DataFloat();
        DataFloat(float value);

        void setValue(float value);
        string getType();
        float getFloat();
};