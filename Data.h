#pragma once
#include <bits/stdc++.h>

using namespace std;


template<Typename T>
class Data{
	private:
		T value;
	public:
		IntegerData();
		IntegerData(T value);

		T getValue();
		void setValue(T value);
};