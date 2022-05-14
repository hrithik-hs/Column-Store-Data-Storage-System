#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;
#define endl "\n"

class Data{
	private:
		// char type[100];
	public:
		Data();
		// Data(string type);
        virtual ~Data()=0;
		virtual string getType()=0;
		
		virtual void setValue(int value);
		virtual void setValue(float value);
		virtual void setValue(string value);

		virtual int getInt();
		virtual float getFloat();
		virtual string getString();
};