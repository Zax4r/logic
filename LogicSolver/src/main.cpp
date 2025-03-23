#include "RPN.h"
#include "Calculator.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    RPN rpnCalculator;
    Calculator calcs;
    string input;
    cout << "Введите выражение: ";
    getline(cin, input);
    rpnCalculator.create_RPN(input);
    cout << "Постфиксная нотация: " << rpnCalculator.get_RPN() << endl;
    string RPN = rpnCalculator.get_RPN();
    cout << calcs.solve(RPN);
    return 0;
}