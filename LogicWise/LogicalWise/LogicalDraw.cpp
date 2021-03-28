#include "LogicalDraw.h"

void LogicalDraw::showPostfixExpression() const {
	cout << "后缀表达式：" << endl;
	stack<char> sc = _postfixExpression;
	while (!sc.empty()) {
		cout << sc.top() << ' ';
		sc.pop();
	}
	cout << endl;
}

void LogicalDraw::showTrueTable() {
	stack<char> s_exp;
	stack<char> s_compute;
	char oper;

	cout << "真值表：" << endl;
	for (char i = 'A'; i - 'A' < _size; ++i) {
		cout << i << '\t';
	}
	cout << endl;

	while (_ttb->next()) {
		s_exp = _postfixExpression;
		for (unsigned int i = 0; i < _size; ++i) {
			cout << (*_ttb)[i] << '\t';
		}
		while (!s_exp.empty()) {
			do {
				oper = s_exp.top();
				s_exp.pop();
				if (getCharType(oper) != CharType::VARIABLE)
					break;
				s_compute.push(oper);
			} while (getCharType(oper) == CharType::VARIABLE);
			calculate(oper, s_compute);
		}
		cout << s_compute.top() << endl;
		s_compute.pop();
	}
	cout << endl;
}