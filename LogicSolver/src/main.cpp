/*
Лабораторная работа №1
Выполнил студент 321701 группы
Бедарик Захар Александрович
Вариант 4

Исполняемый файл программы
19.04.2025

Источники:
-Учебно-методическое пособие по ЛОИС

#(A/\(B/\(C/\(D/\(E/\(F/\(G/\(H/\(I/\(J/\(K/\(L/\(M/\(N/\(O/\(P/\(Q/\(R/\(S/\(T/\(U/\(V/\(W/\(X/\(Y/\Z)))))))))))))))))))))))))
*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>

using namespace std;

const char UNARY_OPERANDS = '!';
const unordered_set<char> BINARY_OPERANDS = {'&', '|', '<', '~'};
const unordered_set<char> LOGIC_CONSTS = {'0', '1'};
const unordered_set<char> LITERALS = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};
const unordered_set<char> ALL_OPERANDS = {'&', '|', '<', '~', '!'};
const unordered_set<char> ARGUMENTS = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','1','0'
};
const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';

const map<char, int> PRIORITY = {
    {'&', 5},
    {'|', 4},
    {'<', 3},
    {'~', 3},
    {'(', 1}
};

vector<char> find_literals(string& input) //finds all the literals
{
	set<char> res;
	for (auto chr : input)
		if (LITERALS.count(chr) != string::npos)
			res.insert(chr);
	vector<char> res_v;
	res_v.reserve(res.size());
	for (auto i : res)
		res_v.push_back(i);
	return res_v;
}

int calculate(string& rpn, map<char, int>& values) //calculates the rpn using logic
{
	stack<int> eval_stack;
    int right,left,result;
	for (char token : rpn)
	{
		if (LITERALS.count(token)) {
			eval_stack.push(values.at(token));
		}
		else if (LOGIC_CONSTS.count(token)) {
			eval_stack.push(token - '0');
		}
		else if (token == UNARY_OPERANDS) {
			int val = eval_stack.top(); eval_stack.pop();
			eval_stack.push(1 - val);
		}
		else {
			right = eval_stack.top();
            eval_stack.pop();
            
			left = eval_stack.top();
            eval_stack.pop();
			switch (token) {
			case '&': result = left & right; 
            break;
			case '|': result = left | right; 
            break;
			case '~': result = int(left == right); 
            break;
			case '<': result = int(!left || right); 
            break;
			}
			eval_stack.push(result);
		}
	}
	return eval_stack.top();
}

int solve(string& input) // solve the task for input
{

	auto literals = find_literals(input);
	map<char, int> values = {};

	size_t count = pow(2, literals.size());

	bool find_one = false, find_zero = false;

	int answer = 0;
	for (size_t i = 0; i < count; i++)
	{
		if (find_one && find_zero)
			return 1;

		for (int j = 0; j < literals.size(); j++)
			values[literals[j]] = (i >> (literals.size() - 1 - j)) & 1;
		answer = calculate(input, values);

		if (answer)
			find_one = true;
		else
			find_zero = true;
	}
	if (find_one && find_zero)
		return 1;
	return 0;
}


bool validate(string& input) // validates the formula
{
    if (input.empty()) 
        return false;
    
    int open = 0, close = 0, ops = 0, bin_ops = 0, args = 0;
    
    for (char c : input) {
        if (ALL_OPERANDS.count(c)) {
            ops++;
            if (c != UNARY_OPERANDS) bin_ops++;
        }
        else if (ARGUMENTS.count(c)) args++;
        else if (c == OPEN_BRACKET) open++;
        else if (c == CLOSE_BRACKET) close++;
        else 
            return false;

        if (ops > open || close > open || args - bin_ops > 1) 
            return false;
    }
    return open == close && open == ops;
}

bool validate2(string& input) // this func checks all subformulas in the input
{
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == OPEN_BRACKET)
		{
			string temp = "";
			int open_brc = 0;
			for (int j = i; j < input.length(); j++)
			{
				if (input[j] == OPEN_BRACKET)
					open_brc++;
				temp += input[j];
				if (input[j] == CLOSE_BRACKET)
					open_brc--;
				if (open_brc == 0)
					break;
			}
			if (!validate(temp))
				return false;
            if ((temp.length() != input.length()) && !validate2(temp)) // save from (((A/\B)/\(C/\D)/\(E/\F)))
                return false;
		}
	}
	return validate(input); // save from (A/\B))
}

bool validate_unchanged(string& input)
{
	for (int i = 0; i < input.length(); i++)
	{
		switch (input[i])
		{
		case('&'):
		case('|'):
		case('<'):
			return false;
		}
	}
	return true;
}

string change(string input)
{
	size_t pos;
	while ((pos = input.find("->")) != string::npos)
		input.replace(pos, 2, "<");
	while ((pos = input.find("\\/")) != string::npos)
		input.replace(pos, 2, "|");
	while ((pos = input.find("/\\")) != string::npos)
		input.replace(pos, 2, "&");
	return input;
}

string create_RPN(string& input)//creates a RPN from original input
 {
    if (!validate_unchanged(input)) return "";
    input = change(input);
    if (!validate2(input)) return "";

    stack<char> ops;
    string rpn;
    vector<int> unary;

    for (char c : input) {
        if (ARGUMENTS.count(c)) {
            rpn += c;
            continue;
        }

        if (c == UNARY_OPERANDS) {
			int brackets = 0;
			auto pos = &c - &input[0];
			for (int j = pos + 1; j < input.size() && input[j] == OPEN_BRACKET; j++) {
				brackets++;
			}
			unary.push_back(brackets);
			continue;
		}
        if (BINARY_OPERANDS.count(c)) {
            while (!ops.empty() && PRIORITY.at(c) < PRIORITY.at(ops.top())) {
                rpn += ops.top();
                ops.pop();
            }
            ops.push(c);
            continue;
        }

        if (c == OPEN_BRACKET) {
            ops.push(c);
            continue;
        }

        if (c == CLOSE_BRACKET) {
            while (ops.top() != OPEN_BRACKET) {
                rpn += ops.top();
                ops.pop();
            }
            ops.pop();
            for (auto& cnt : unary) cnt--;
        }
    }

    while (!ops.empty()) {
        rpn += ops.top();
        ops.pop();
    }

    rpn += string(unary.size(),'!');
    return rpn;
}

int main()
{
   setlocale(LC_ALL, "ru");
	for (int i = 0; i < 5; i++)
		{
			cout << "Символ логической лжи: 0" << endl;
			cout << "Символ логической правды: 1" << endl;
			cout << "Символ логического ИЛИ: \\/" << endl;
			cout << "Символ логического И: /\\" << endl;
			cout << "Символ логического отрицания: !" << endl;
			cout << "Символ логической импликации: ->" << endl;
			cout << "Символ логической эквиваленции:~" << endl;
			cout << "Введите логическую формулу:\n";
		
			string original_input;
			getline(cin, original_input);
			string rpn_input = create_RPN(original_input);
			if (rpn_input == "")
				cout << "Неправильная строка\n" << endl;
			
			else
			{
			int result = solve(rpn_input);
			if (result)
				cout << "Формула является нейтральной\n" << endl;
			else
				cout << "Формула НЕ является нейтральной\n" << endl;
			}
		}
   return 0;
}
