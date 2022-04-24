#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include "Data.h"
using namespace std;
#define endl "\n"

class DataEnum:public Data{
	private:
        static int numValues;
        static char encoding[10][100];
        char type[100];
        bool value[10];
	public:
		DataEnum();
		~DataEnum();
        DataEnum(vector<string> _encoding, string value);

        void setValue(string value);
        string getType();
        string getEnum();
};