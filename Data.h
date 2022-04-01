#pragma once
#include <bits/stdc++.h>

using namespace std;

class Data{
	private:
		string type;
	public:
		Data();
		Data(string type);
        ~Data();
		string getType();
		
		virtual void setValue(int value);
		virtual void setValue(float value);
		virtual void setValue(string value);

		virtual int getInt();
		virtual float getFloat();
		virtual string getString();
};