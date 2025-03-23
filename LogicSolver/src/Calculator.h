#pragma once
#include "CONSTANTS.h"
class Calculator
{
private:
	vector<char> find_literals(string& input);
	void add_one(vector<int>& input);
	int calculate(string& rpn,map<char,int>& values);
public:
	int solve(string& input);
};

