#pragma once
#include <bits/stdc++.h>

using namespace std;


class Column{
	private:
		string name;
        string address;
	public:
		Column();
		Column(string name);
        Column(string name,string address);
		~Column();

		virtual void writeFile(string file_source)=0;
		virtual void loadFile(string file_source)=0;

		string getName();
		void setName(string name);
};