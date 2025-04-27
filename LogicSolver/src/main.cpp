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
#include <chrono>

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
	for (int i=0;i<input.length();i++)
		if (LITERALS.count(input[i]))
			res.insert(input[i]);
	return vector<char>(res.begin(), res.end());
}

int calculate(string& rpn, map<char, int>& values) //calculates the rpn using logic
{
	stack<int> eval_stack;
    int right,left,result;
	char token;
	for (int i=0;i<rpn.length();i++)
	{
		token = rpn[i];
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
			return find_one && find_zero;

		for (int j = 0; j < literals.size(); j++)
			values[literals[j]] = (i >> (literals.size() - 1 - j)) & 1;
		answer = calculate(input, values);

		if (answer)
			find_one = true;
		else
			find_zero = true;
	}
	return find_one && find_zero;
}


bool validate(string& input) // validates the formula
{
    if (input.empty()) 
        return false;
    
    int open = 0, close = 0, ops = 0, bin_ops = 0, args = 0;
    
    for (int i=0;i<input.length();i++) {
		char c = input[i];
		ops+= int(ALL_OPERANDS.count(c));
		bin_ops+= int (c!=UNARY_OPERANDS);
		args+= int(ARGUMENTS.count(c));
		open+= int(c == OPEN_BRACKET);
		close+= int(c == CLOSE_BRACKET);
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
				open_brc+= int(input[j] == OPEN_BRACKET);
				temp += input[j];
				open_brc-= int(input[j] == CLOSE_BRACKET);
				if (open_brc == 0)
					break;
			}
            if (!validate(temp)) // save from (((A/\B)/\(C/\D)/\(E/\F)))
                return false;
		}
	}
	return validate(input); // save from (A/\B))
}

bool validate_unchanged(string& input)
{
	for (int i = 0; i < input.length(); i++)
		if (input[i] == '&' || input[i]=='|' || input[i]=='<')
			return false;
	return true;
}

string change(string input)
{
	int pos;
	while ((pos = input.find("->")) != string::npos)
		input.replace(pos, 2, "<");
	while ((pos = input.find("\\/")	) != string::npos)
		input.replace(pos, 2, "|");
	while ((pos = input.find("/\\")) != string::npos)
		input.replace(pos, 2, "&");
	return input;
}

bool validate_input(string& input) {
    if (!validate_unchanged(input)) return false;
    input = change(input);
    return validate2(input);
}

bool handle_argument(char c, string& rpn) {
    if (ARGUMENTS.count(c)) {
        rpn += c;
        return true;
    }
    return false;
}

void process_unary_after_bracket(vector<int>& unary, string& rpn) {
    for (int i = 0; i < unary.size(); i++) {
        if (unary[i]-- == 0) {
            rpn += '!';
            unary.erase(unary.begin()+i);
            i--;
        }
    }
}

int count_leading_brackets(const string& input, int start) {
    int brackets = 0;
    for (int j = start; j < input.length(); j++) {
        if (input[j] == OPEN_BRACKET)
            brackets++;
        else break;
    }
    return brackets;
}

bool handle_unary_operand(char c, int i, string& input, vector<int>& unary) {
    if (c == UNARY_OPERANDS) {
        int brackets = count_leading_brackets(input, i+1);
        unary.push_back(brackets);
        return true;
    }
    return false;
}

bool handle_binary_operand(char c, stack<char>& ops, string& rpn) {
    if (BINARY_OPERANDS.count(c)) {
        while (!ops.empty() && PRIORITY.at(c) < PRIORITY.at(ops.top())) {
            rpn += ops.top();
            ops.pop();
        }
        ops.push(c);
        return true;
    }
    return false;
}

bool handle_open_bracket(char c, stack<char>& ops) {
    if (c == OPEN_BRACKET) {
        ops.push(c);
        return true;
    }
    return false;
}

bool handle_close_bracket(char c, stack<char>& ops, string& rpn, vector<int>& unary) {
    if (c == CLOSE_BRACKET) {
        while (ops.top() != OPEN_BRACKET) {
            rpn += ops.top();
            ops.pop();
        }
        ops.pop();
        process_unary_after_bracket(unary, rpn);
        return true;
    }
    return false;
}

void process_remaining_operators(stack<char>& ops, string& rpn) {
    while (!ops.empty()) {
        rpn += ops.top();
        ops.pop();
    }
}

void process_remaining_unary(vector<int>& unary, string& rpn) {
    if (unary.size() % 2)
        rpn += "!";
}

string create_RPN(string& input) {
    if (!validate_input(input)) return "";
    stack<char> ops;
    string rpn;
    vector<int> unary;

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];
		handle_argument(c, rpn);
		handle_unary_operand(c, i, input, unary);
		handle_binary_operand(c, ops, rpn);
		handle_open_bracket(c, ops);
		handle_close_bracket(c, ops, rpn, unary);
    }

    process_remaining_operators(ops, rpn);
    process_remaining_unary(unary, rpn);
    
    return rpn;
}

void TestUser()
{	
	vector<char> answers = {'1','2','1','1','2'};
	vector<string> formulas = {"(A/\\A)","(A->A)","B","(!(A~B))","((A/\\(B/\\C))/\\(!A))"};
	for (int i =0;i<answers.size();i++)
	{
	string answer = " ";
	cout << "Принадлежит ли данная формула классу нейтральных?" << endl << formulas[i] << endl;
	cout <<"1.Да\t"  << "2.Нет" << endl;
	getline(cin,answer);
	if (answer[0] == answers[i])
		cout <<"Правильно!!!!!!" << endl;
	else 
		cout<< "Неправильно!!!!!" << endl;
	}
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
	TestUser();
   return 0;
}
