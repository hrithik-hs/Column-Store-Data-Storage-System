#pragma once
#include <bits/stdc++.h>
#include "Data.h"
using namespace std;

class DataInteger:public Data{
	private:
		int value;
	public:
		DataInteger();
        DataInteger(int value);

        void setValue(int value);
        int getInt();
};