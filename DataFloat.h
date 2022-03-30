#pragma once
#include <bits/stdc++.h>
#include "Data.h"
using namespace std;

class DataFloat:public Data{
	private:
		float value;
	public:
		DataFloat();
        DataFloat(float value);

        void setValue(float value);
        float getFloat();
};