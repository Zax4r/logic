/*
������������ ������ �1
�������� ������� 321701 ������
������� ����� �������������
������� 4

�������� ������������ ����
19.04.2025

���������:
-�������������� ����������� ����� ���������������� ������
*/

#pragma once
#ifndef CONSTANTS_H  // ���������, ��� �� ��� ������� ���� ����
#define CONSTANTS_H  // ����������, ��� ���� �������

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