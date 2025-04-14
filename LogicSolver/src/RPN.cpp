#include "RPN.h"

bool RPN::validate(string& input)
{
	int open_bracket_counter = 0;
	int close_bracket_counter = 0;
	int operands_count = 0;
	int binary_operands = 0;
	int arguments = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (ALL_OPERANDS.find(input[i]) != string::npos)
		{
			operands_count++;
			if (BINARY_OPERANDS.find(input[i]) != string::npos)
				binary_operands++;
		}
		else
			if (ARGUMENTS.find(input[i]) != string::npos)
				arguments++;
			else
				if (input[i] == OPEN_BRACKET)
					open_bracket_counter++;
				else
					if (input[i] == CLOSE_BRACKET)
						close_bracket_counter++;
					else return false;

		if (operands_count > open_bracket_counter)
			return false;

		if (close_bracket_counter > open_bracket_counter)
			return false;

		if (arguments - 2 >= binary_operands)
			return false;
	}
	if (open_bracket_counter != close_bracket_counter)
		return false;
	if (open_bracket_counter != operands_count)
		return false;
	return true;
}

string RPN::change(string& input)
{
	while (true)
	{
		auto pos3 = input.find("/\\");
		auto pos2 = input.find("\\/");
		auto pos = input.find("-");
		if (pos != string::npos)
		{
			input.replace(pos, 1, "");
		}
		else
			if (pos2 != string::npos)
			{
				input.replace(pos2, 2, "|");
			}
				else if (pos3 != string::npos) {
					input.replace(pos3, 2, "&");
				}
				else return input;
	}
}

void RPN::create_RPN(string& input)
{
	input = this->change(input);
	if (!(this->validate(input)))
	{
		cout << "Неправильная строка";
		return;
	}
	for (int i=0;i<input.length();i++)
	{
		if (LITERALS.find(input[i]) != string::npos)
		{
			this->rpn += input[i];
		}
		
		if (LOGIC_CONSTS.find(input[i]) != string::npos)
		{
			this->rpn += input[i];
		}

		for (auto val : this->unary)
		{
			if (val == 0)
			{
				this->rpn += "!";
				this->unary.erase(this->unary.begin() + val);
			}
		}

		if (BINARY_OPERANDS.find(input[i]) != string::npos)
		{
			while (this->stack_operands.size() && ((PRIORITY.at(input[i]) < PRIORITY.at(this->stack_operands.top()))))
			{
				this->rpn += this->stack_operands.top();
				this->stack_operands.pop();
			}
			this->stack_operands.push(input[i]);
			continue;
		}
		else {
			if (UNARY_OPERANDS.find(input[i]) != string::npos)
			{
				int brack_count = 0;
				for (int j=i+1;j<input.length();j++)
				{
					if (input[j] != OPEN_BRACKET)
					{
						this->unary.push_back(brack_count);
						break;
					}
					brack_count++;
				}
				continue;
			}
		}

		if (input[i] == OPEN_BRACKET)
			this->stack_operands.push(input[i]);

		if (input[i] == CLOSE_BRACKET)
		{
			for (int j = 0; j < this->unary.size(); j += 1)
				this->unary[j]--;

			while (this->stack_operands.top() != OPEN_BRACKET)
			{
				this->rpn += this->stack_operands.top();
				this->stack_operands.pop();
			}
			this->stack_operands.pop();
		}
	}
	while (!(this->stack_operands.empty()))
	{
		this->rpn += this->stack_operands.top();
		this->stack_operands.pop();
	}
	if (!(this->unary.empty()))
		this->rpn += "!";
}

string RPN::get_RPN()
{
	return rpn;
}
