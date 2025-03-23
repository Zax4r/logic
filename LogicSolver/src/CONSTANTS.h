#pragma once
#ifndef CONSTANTS_H  // Проверяем, был ли уже включен этот файл
#define CONSTANTS_H  // Обозначаем, что файл включён

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <set>
#include <chrono>

using namespace std;

const string UNARY_OPERANDS = "!";
const string BINARY_OPERANDS = "&|>~";
const string LITERALS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';

const map<char, int> PRIORITY = {
    {'&', 5},
    {'|', 4},
    {'>', 3},
    {'~', 3},
    {'(', 1}
};

#endif