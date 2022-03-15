#pragma once
#include <bits/stdc++.h>

using namespace std;


class Column{
	private:
		string name;
	public:
		Column();
		Column(string name);
		~Column();

		virtual void writeFile()=0;
		virtual void loadFile()=0;

		string getName();
		void setName(string name);
};