#pragma once
#include <bits/stdc++.h>

using namespace std;


template<typename T>
class Data{
	private:
		T value;
	public:
		Data();
		Data(T value);

		T getValue();
		void setValue(T value);
};