#include "RPN.h"

bool RPN::validate(string& input)
{
	int bracket_counter = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == OPEN_BRACKET)
			bracket_counter++;
		if (input[i] == CLOSE_BRACKET && bracket_counter == 0)
			return false;
		if (input[i] == CLOSE_BRACKET && bracket_counter)
			bracket_counter--;
	}
	return true;
}

void RPN::create_RPN(string& input)
{
	if (!(this->validate(input)))
	{
		cout << "Неправильная строка";
		return;
	}
	while (true)
	{
		auto pos = input.find("-");
		if (pos == string::npos)
		{
			break;
		}
		input.replace(pos,1,"");
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
