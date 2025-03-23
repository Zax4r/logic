#include "Calculator.h"

int Calculator::solve(string& input)
{
    size_t ones_count = 0;
    auto literals = this->find_literals(input);
    vector<int> bits(literals.size(),0);
    map<char, int> values;
    size_t count = pow(2, bits.size());
    for (auto a : literals)
        cout << a << "   ";
    cout << '\n';
    for (size_t i = 0; i < count; i++)
    {
        for (int j = 0; j < bits.size(); j++)
            values[literals[j]] = bits[j];
        for (auto a : bits)
            cout << a << "   ";
        cout << this->calculate(input, values);
        cout << '\n';
        this->add_one(bits);
        ones_count += this->calculate(input, values);
    }
    return ones_count;
}

vector<char> Calculator::find_literals(string& input)
{
    set<char> res;
    for (auto chr : input)
        if (LITERALS.find(chr)!=string::npos)
            res.insert(chr);
    vector<char> res_v;
    res_v.reserve(res.size());
    for (auto i : res)
        res_v.push_back(i);
    return res_v;
}

void Calculator::add_one(vector<int>& input)
{
    int carry = 1;
    for (int i = input.size() - 1; i >= 0; i--)
    {
        int s = input[i] + carry;
        input[i] = s % 2;
        carry = int(s/2);
    }
}

int Calculator::calculate(string& rpn, map<char, int>& values)
{
    int first = -1;
    int second = -1;
    stack<int> reserve;
    for (auto chr : rpn)
    {
        if (BINARY_OPERANDS.find(chr) != string::npos)
        {
            if (first == -1)
            {
                first = reserve.top();
                reserve.pop();
            }

            switch (chr)
            {
            case '&':
            {
                second = first & second;
                break;
            }
            case '|':
            {
                second = first | second;
                break;
            }
            case '~':
            {
                second = int(first == second);
                break;
            }
            case '>':
            {
                second = int(first <= second);
                break;
            }
            }
            first = -1;
            continue;
        }

        if (UNARY_OPERANDS.find(chr) != string::npos)
        {
            if (second == -1)
                first = first ? 0:1;
            else
                second = second ? 0 : 1;
            continue;
        }

        if (first == -1)
        {
            first = values.at(chr);
            continue;
        }
        if (second == -1)
        {
            second = values.at(chr);
            continue;
        }
        reserve.push(values.at(chr));
    }
    return second;
}

