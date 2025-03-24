#pragma once
#include "RPN.h"
#include "Calculator.h"
class Solver
{
private:
	RPN converter;
	Calculator calculator;
	string original_input;
	string rpn_input;
	int result;
public:
	void start();
};

