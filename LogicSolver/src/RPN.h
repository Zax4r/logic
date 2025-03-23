#pragma once
#include "CONSTANTS.h"
#include <stack>
#include <vector>
using namespace std;

class RPN
{
private:
	string rpn;
	vector<int> unary;
	stack<char> stack_operands;
	bool validate(string& input);
public:
	RPN()
	{
		this->rpn = "";
	}

	void create_RPN(string& input);
	string get_RPN();
};

