/*
Лабораторная работа №1
Выполнил студент 321701 группы
Бедарик Захар Александрович
Вариант 4

Основной заголовочный файл
19.04.2025

Источники:
-Проектирование программных основ интеллекутальных систем
*/

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
#include <unordered_set>

using namespace std;

const char UNARY_OPERANDS = '!';
const string BINARY_OPERANDS = "&|<~";
const string LITERALS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const unordered_set<char> binary_ops = { '&', '|', '<', '~' };
const unordered_set<char> logic_consts = { '0', '1' };
const unordered_set<char> literals_set = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};
const string LOGIC_CONSTS = "01";
const string ALL_OPERANDS = "!&|<~";
const string ARGUMENTS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ01";
const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';

const map<char, int> PRIORITY = {
    {'&', 5},
    {'|', 4},
    {'<', 3},
    {'~', 3},
    {'(', 1}
};

#endif