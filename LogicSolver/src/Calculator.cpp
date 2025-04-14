#include "Calculator.h"

int Calculator::solve(string& input)
{

    auto literals = this->find_literals(input);

    vector<int> bits(literals.size(),0);

    map<char, int> values = { {'1',1},{'0',0} };

    size_t count = pow(2, bits.size());

    bool find_one = false, find_zero = false;

    int answer = 0;
    for (auto a : literals)
        cout << a << "   ";
    cout << '\n';
    for (size_t i = 0; i < count; i++)
    {
        if (find_one && find_zero)
            return 1;
        for (int j = 0; j < bits.size(); j++)
            values[literals[j]] = bits[j];
        for (auto a : bits)
            cout << a << "   ";
        answer = this->calculate(input, values);
        cout << answer << endl;

        if (answer)
            find_one = true;
        else
            find_zero = true;
        this->add_one(bits);
    }
    if (find_one && find_zero)
        return 1;
    return 0;
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
        if (LITERALS.find(chr) != string::npos)
            reserve.push(values.at(chr));

        if (BINARY_OPERANDS.find(chr) != string::npos)
        {
            second = reserve.top();
            reserve.pop();
            first = reserve.top();
            reserve.pop();

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
            reserve.push(second);
            second = -1;
            first = -1;
            continue;
        }

        if (UNARY_OPERANDS.find(chr) != string::npos)
        {
            auto val = reserve.top();
            reserve.pop();
            val = (val + 1) % 2;
            reserve.push(val);
            continue;
        }
    }
    return reserve.top();
}

