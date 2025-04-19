///*
//Лабораторная работа №1
//Выполнил студент 321701 группы
//Бедарик Захар Александрович
//Вариант 4
//
//Основной исполняемый файл программы
//19.04.2025
//
//Источники:
//-Проектирование программных основ интеллекутальных систем
//
//#(A/\(B/\(C/\(D/\(E/\(F/\(G/\(H/\(I/\(J/\(K/\(L/\(M/\(N/\(O/\(P/\(Q/\(R/\(S/\(T/\(U/\(V/\(W/\(X/\(Y/\Z)))))))))))))))))))))))))
//РАБОТАЕТ ПРАВИЛЬНО
//*/
//
//#include "CONSTANTS.h"
//using namespace std;
//
//vector<char> find_literals(string& input)
//{
//	set<char> res;
//	for (auto chr : input)
//		if (LITERALS.find(chr) != string::npos)
//			res.insert(chr);
//	vector<char> res_v;
//	res_v.reserve(res.size());
//	for (auto i : res)
//		res_v.push_back(i);
//	return res_v;
//}
//
//int calculate(string& rpn, map<char, int>& values)
//{
//	stack<int> eval_stack;
//
//	for (char token : rpn)
//	{
//		if (literals_set.count(token)) {
//			eval_stack.push(values.at(token));
//		}
//		else if (logic_consts.count(token)) {
//			eval_stack.push(token - '0');
//		}
//		else if (token == UNARY_OPERANDS) {
//			if (eval_stack.empty()) throw runtime_error("Unary operator with empty stack");
//			int val = eval_stack.top(); eval_stack.pop();
//			eval_stack.push(1 - val); // NOT
//		}
//		else if (binary_ops.count(token)) {
//			if (eval_stack.size() < 2) throw runtime_error("Binary operator with insufficient operands");
//
//			int right = eval_stack.top(); eval_stack.pop();
//			int left = eval_stack.top(); eval_stack.pop();
//
//			int result = 0;
//
//			switch (token) {
//			case '&': result = left & right; break;
//			case '|': result = left | right; break;
//			case '~': result = int(left == right); break;
//			case '<': result = int(!left || right); break; // Implication
//			default: throw runtime_error("Unknown binary operator");
//			}
//
//			eval_stack.push(result);
//		}
//		else {
//			throw runtime_error(string("Invalid character in RPN: ") + token);
//		}
//	}
//
//	if (eval_stack.size() != 1) {
//		throw runtime_error("Evaluation error: stack size != 1 at end");
//	}
//
//	return eval_stack.top();
//}
//
//int solve(string& input)
//{
//
//	auto literals = find_literals(input);
//	map<char, int> values = { {'1',1},{'0',0} };
//
//	size_t count = pow(2, literals.size());
//
//	bool find_one = false, find_zero = false;
//
//	int answer = 0;
//	for (size_t i = 0; i < count; i++)
//	{
//		if (find_one && find_zero)
//			return 1;
//
//		for (int j = 0; j < literals.size(); j++)
//			values[literals[j]] = (i >> (literals.size() - 1 - j)) & 1;
//		answer = calculate(input, values);
//
//		if (answer)
//			find_one = true;
//		else
//			find_zero = true;
//	}
//	if (find_one && find_zero)
//		return 1;
//	return 0;
//}
//
//
//bool validate(string& input)
//{
//	if (!input.length())
//		return false;
//
//	int open_bracket_counter = 0;
//	int close_bracket_counter = 0;
//	int operands_count = 0;
//	int binary_operands = 0;
//	int arguments = 0;
//	for (int i = 0; i < input.length(); i++)
//	{
//		if (ALL_OPERANDS.find(input[i]) != string::npos)
//		{
//			operands_count++;
//			if (input[i] != UNARY_OPERANDS)
//				binary_operands++;
//		}
//		else
//			if (ARGUMENTS.find(input[i]) != string::npos)
//				arguments++;
//			else
//				if (input[i] == OPEN_BRACKET)
//					open_bracket_counter++;
//				else
//					if (input[i] == CLOSE_BRACKET)
//						close_bracket_counter++;
//					else return false;
//
//		if (operands_count > open_bracket_counter)
//			return false;
//
//		if (close_bracket_counter > open_bracket_counter)
//			return false;
//
//		if (arguments - 2 >= binary_operands)
//			return false;
//	}
//	if (open_bracket_counter != close_bracket_counter)
//		return false;
//	if (open_bracket_counter != operands_count)
//		return false;
//	return true;
//}
//
//bool validate2(string& input)
//{
//	for (int i = 0; i < input.length(); i++)
//	{
//		if (input[i] == OPEN_BRACKET)
//		{
//			string temp = "";
//			int open_brc = 0;
//			for (int j = i; j < input.length(); j++)
//			{
//				if (input[j] == OPEN_BRACKET)
//					open_brc++;
//				temp += input[j];
//				if (input[j] == CLOSE_BRACKET)
//					open_brc--;
//				if (open_brc == 0)
//					break;
//			}
//			if (!validate(temp))
//				return false;
//		}
//	}
//	return validate(input);
//}
//
//bool validate_unchanged(string& input)
//{
//	for (int i = 0; i < input.length(); i++)
//	{
//		switch (input[i])
//		{
//		case('&'):
//		{
//			return false;
//		}
//		case('|'):
//		{
//			return false;
//		}
//		case('<'):
//		{
//			return false;
//		}
//		}
//	}
//	return true;
//}
//
//string change(string input)
//{
//	size_t pos;
//	while ((pos = input.find("->")) != string::npos)
//		input.replace(pos, 2, "<");
//	while ((pos = input.find("\\/")) != string::npos)
//		input.replace(pos, 2, "|");
//	while ((pos = input.find("/\\")) != string::npos)
//		input.replace(pos, 2, "&");
//	return input;
//}
//
//string create_RPN(string& input)
//{
//	vector<int> unary;
//	stack<char> stack_operands;
//	string rpn;
//	if (!validate_unchanged(input))
//		return "";
//
//	input = change(input);
//	if (!(validate2(input)))
//		return "";
//
//	for (int i = 0; i < input.length(); i++)
//	{
//		if (LITERALS.find(input[i]) != string::npos)
//		{
//			rpn += input[i];
//		}
//
//		if (LOGIC_CONSTS.find(input[i]) != string::npos)
//		{
//			rpn += input[i];
//		}
//
//		for (auto val : unary)
//		{
//			if (val == 0)
//			{
//				rpn += "!";
//				unary.erase(unary.begin() + val);
//			}
//		}
//
//		if (BINARY_OPERANDS.find(input[i]) != string::npos)
//		{
//			while (stack_operands.size() && ((PRIORITY.at(input[i]) < PRIORITY.at(stack_operands.top()))))
//			{
//				rpn += stack_operands.top();
//				stack_operands.pop();
//			}
//			stack_operands.push(input[i]);
//			continue;
//		}
//		else {
//			if (input[i] == UNARY_OPERANDS)
//			{
//				int brack_count = 0;
//				for (int j = i + 1; j < input.length(); j++)
//				{
//					if (input[j] != OPEN_BRACKET)
//					{
//						unary.push_back(brack_count);
//						break;
//					}
//					brack_count++;
//				}
//				continue;
//			}
//		}
//
//		if (input[i] == OPEN_BRACKET)
//			stack_operands.push(input[i]);
//
//		if (input[i] == CLOSE_BRACKET)
//		{
//			for (int j = 0; j < unary.size(); j += 1)
//				unary[j]--;
//
//			while (stack_operands.top() != OPEN_BRACKET)
//			{
//				rpn += stack_operands.top();
//				stack_operands.pop();
//			}
//			stack_operands.pop();
//		}
//	}
//	while (!(stack_operands.empty()))
//	{
//		rpn += stack_operands.top();
//		stack_operands.pop();
//	}
//	if (!(unary.empty()))
//		rpn += "!";
//
//	return rpn;
//}
//
//
//
//void start()
//{
//	string original_input;
//	cout << "Введите логическую формулу:\n";
//	getline(cin, original_input);
//	string rpn_input = create_RPN(original_input);
//	if (rpn_input == "")
//	{
//		cout << "Неправильная строка\n";
//		return;
//	}
//
//	int result = solve(rpn_input);
//	if (result)
//		cout << "Формула является нейтральной\n";
//	else
//		cout << "Формула НЕ является нейтральной\n";
//}
//
//
//
//int main()
//{
//    setlocale(LC_ALL, "ru");
//	for (int i = 0; i < 5; i++)
//		start();
//    return 0;
//}

/*
Лабораторная работа №1
Выполнил студент 321701 группы
Бедарик Захар Александрович
Вариант 4

Оптимизированная версия с рекурсивным спуском
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <cmath>

using namespace std;

// Константы
const char UNARY_OPERANDS = '!';
const string BINARY_OPERANDS = "&|<~";
const string LITERALS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string LOGIC_CONSTS = "01";
const string ALL_OPERANDS = "!&|<~";
const string ARGUMENTS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ01";
const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';

unordered_set<char> binary_ops = { '&', '|', '<', '~' };
unordered_set<char> logic_consts = { '0', '1' };
unordered_set<char> literals_set = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

map<char, int> PRIORITY = {
    {'&', 5},
    {'|', 4},
    {'<', 3},
    {'~', 3},
    {'(', 1}
};

// Функция для замены комбинаций операторов на однозначные символы
string change(string input) {
    size_t pos;
    while ((pos = input.find("->")) != string::npos)
        input.replace(pos, 2, "<");
    while ((pos = input.find("\\/")) != string::npos)
        input.replace(pos, 2, "|");
    while ((pos = input.find("/\\")) != string::npos)
        input.replace(pos, 2, "&");
    return input;
}

// Функция для проверки корректности формулы (оставлена без изменений)
bool validate(string& input) {
    if (!input.length())
        return false;

    int open_bracket_counter = 0;
    int close_bracket_counter = 0;
    int operands_count = 0;
    int binary_operands = 0;
    int arguments = 0;
    for (int i = 0; i < input.length(); i++) {
        if (ALL_OPERANDS.find(input[i]) != string::npos) {
            operands_count++;
            if (input[i] != UNARY_OPERANDS)
                binary_operands++;
        }
        else if (ARGUMENTS.find(input[i]) != string::npos)
            arguments++;
        else if (input[i] == OPEN_BRACKET)
            open_bracket_counter++;
        else if (input[i] == CLOSE_BRACKET)
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

bool validate2(string& input) {
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == OPEN_BRACKET) {
            string temp = "";
            int open_brc = 0;
            for (int j = i; j < input.length(); j++) {
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
        }
    }
    return validate(input);
}

bool validate_unchanged(string& input) {
    for (int i = 0; i < input.length(); i++) {
        switch (input[i]) {
        case('&'):
        case('|'):
        case('<'):
            return false;
        }
    }
    return true;
}

// Функция для поиска уникальных литералов в формуле
vector<char> find_literals(string& input) {
    set<char> res;
    for (auto chr : input)
        if (LITERALS.find(chr) != string::npos)
            res.insert(chr);
    vector<char> res_v(res.begin(), res.end());
    return res_v;
}

// Рекурсивный парсер для вычисления логического выражения
class Parser {
    string input;
    size_t pos;
    map<char, int> values;

public:
    Parser(string& expr, map<char, int>& vars) : input(expr), pos(0), values(vars) {}

    int parse() {
        int result = parseImplication();
        if (pos < input.length()) {
            throw runtime_error("Unexpected characters at end of expression");
        }
        return result;
    }

private:
    int parseImplication() {
        int left = parseOr();
        while (pos < input.length() && input[pos] == '<') {
            pos++;
            int right = parseImplication();
            left = (!left || right);
        }
        return left;
    }

    int parseOr() {
        int left = parseAnd();
        while (pos < input.length() && input[pos] == '|') {
            pos++;
            int right = parseAnd();
            left = (left || right);
        }
        return left;
    }

    int parseAnd() {
        int left = parseNot();
        while (pos < input.length() && input[pos] == '&') {
            pos++;
            int right = parseNot();
            left = (left && right);
        }
        return left;
    }

    int parseNot() {
        if (pos < input.length() && input[pos] == '!') {
            pos++;
            return !parseNot();
        }
        return parsePrimary();
    }

    int parsePrimary() {
        if (pos >= input.length()) {
            throw runtime_error("Unexpected end of expression");
        }

        if (input[pos] == OPEN_BRACKET) {
            pos++;
            int result = parseImplication();
            if (pos >= input.length() || input[pos] != CLOSE_BRACKET) {
                throw runtime_error("Missing closing bracket");
            }
            pos++;
            return result;
        }

        char c = input[pos++];
        if (literals_set.count(c)) {
            return values.at(c);
        }
        else if (logic_consts.count(c)) {
            return c - '0';
        }
        else {
            throw runtime_error(string("Unexpected character: ") + c);
        }
    }
};

// Функция для вычисления значения формулы
int calculate(string& expr, map<char, int>& values) {
    Parser parser(expr, values);
    return parser.parse();
}

// Основная функция решения
int solve(string& input) {
    auto literals = find_literals(input);
    map<char, int> values = { {'1',1}, {'0',0} };

    size_t count = pow(2, literals.size());
    bool find_one = false, find_zero = false;

    for (size_t i = 0; i < count; i++) {
        if (find_one && find_zero) return 1;

        for (int j = 0; j < literals.size(); j++)
            values[literals[j]] = (i >> (literals.size() - 1 - j)) & 1;

        int answer = calculate(input, values);

        if (answer) find_one = true;
        else find_zero = true;
    }

    return (find_one && find_zero) ? 1 : 0;
}

void start() {
    string original_input;
    cout << "Введите логическую формулу:\n";
    getline(cin, original_input);

    if (!validate_unchanged(original_input)) {
        cout << "Неправильная строка\n";
        return;
    }

    string processed_input = change(original_input);
    if (!validate2(processed_input)) {
        cout << "Неправильная строка\n";
        return;
    }

    int result = solve(processed_input);
    if (result)
        cout << "Формула является нейтральной\n";
    else
        cout << "Формула НЕ является нейтральной\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    for (int i = 0; i < 5; i++)
        start();
    return 0;
}