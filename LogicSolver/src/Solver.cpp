#include "Solver.h"

void Solver::start()
{
	cout << "������� ���������� �������\n";
	getline(cin, this->original_input);
	this->converter.create_RPN(this->original_input);
	this->rpn_input = this->converter.get_RPN();
	if (this->rpn_input == "")
		return;

	cout << "��� ���������� ������� " << this->rpn_input << endl;
	this->result = this->calculator.solve(this->rpn_input);
	if (this->result)
		cout << "������� �������� �����������";
	else
		cout << "������� �� �������� �����������";
}
