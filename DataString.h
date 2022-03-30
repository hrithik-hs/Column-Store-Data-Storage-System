#pragma once
#include <bits/stdc++.h>
#include "Data.h"
using namespace std;

class DataString:public Data{
	private:
		string value;
	public:
		DataString();
        DataString(string value);

        void setValue(string value);
        string getString();
};