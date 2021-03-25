#include "LogicalOperation.h"

LogicalOperation::LogicalOperation(unsigned int& size, const string& infixExpression, Style style)
	: _size(size), _postfixExpression(), _trueTable(size), _trueTable_kn(), _style(style)
{
	infixToPostfix(infixExpression);
	if (_style == KARNO)
		_trueTable_kn.init(size);
}

void LogicalOperation::showPostfixExpression() const {
	cout << "后缀表达式：" << '\n';
	stack<char> sc = _postfixExpression;
	while (!sc.empty()) {
		cout << sc.top() << ' ';
		sc.pop();
	}
	cout << '\n';
}

void LogicalOperation::showTrueTable() {
	stack<char> s_exp;
	stack<char> s_compute;
	char c;

	cout << "真值表：" << '\n';
	for (char i = 'A'; i - 'A' < _size; ++i) {
		cout << i << '\t';
	}
	cout << '\n';

	// TrueTable  使用 do while
	// CyclicCode 使用 while
	if (_style == DEFAULT) {
		 do {
			s_exp = _postfixExpression;
			for (unsigned int i = 0; i < _size; ++i) {
				cout << _trueTable[i] << '\t';
			}
			while (!s_exp.empty()) {
				do {
					c = s_exp.top();
					s_exp.pop();
					if (getCharType(c) != CharType::VARIABLE)
						break;
					s_compute.push(c);
				} while (getCharType(c) == CharType::VARIABLE);
				calculate(c, s_compute);
			}
			cout << s_compute.top() << '\n';
			s_compute.pop();
		} while (_trueTable.next());
	}
	else if (_style == KARNO) {
		while (_trueTable_kn.next()) {
			s_exp = _postfixExpression;
			for (unsigned int i = 0; i < _size; ++i) {
				cout << _trueTable_kn[i] << '\t';
			}
			while (!s_exp.empty()) {
				do {
					c = s_exp.top();
					s_exp.pop();
					if (getCharType(c) != CharType::VARIABLE)
						break;
					s_compute.push(c);
				} while (getCharType(c) == CharType::VARIABLE);
				calculate(c, s_compute);
			}
			cout << s_compute.top() << '\n';
			s_compute.pop();
		}
	}
	cout << '\n';
}

void LogicalOperation::showKarnaughDiagram() {

}

void LogicalOperation::showSimplifiedResult() {

}

LogicalOperation::CharType LogicalOperation::getCharType(const char& c) const {
	if ('A' <= c && c <= 'Z')
		return CharType::VARIABLE;
	switch (c) {
	case ' ':
		return CharType::BLANK;
	case '+':
		return CharType::OR;
	case '*':
		return CharType::AND;
	case '!':
		return CharType::NOT;
	case '(':
		return CharType::L_BRACKET;
	case ')':
		return CharType::R_BRACKET;
	}
	return CharType::ERROR_TYPE;
}

bool LogicalOperation::charTypeCmp(const char& oper, const char& soper) const {
	return getCharType(oper) <= getCharType(soper) ? true : false;
}

void LogicalOperation::stackTransfer(const char& c, stack<char>& src, stack<char>& des, bool hasBracket) {
	if (hasBracket == false) {
		if (!src.empty() && src.top() != '(' && charTypeCmp(c, src.top()))
			while (!src.empty() && src.top() != '(' && charTypeCmp(c, src.top())) {
				des.push(src.top());
				src.pop();
			}
		src.push(c);
	}
	else {
		while (!src.empty() && src.top() != '(') {
			des.push(src.top());
			src.pop();
		}
		src.pop();
	}
}

void LogicalOperation::infixToPostfix(const string& oldExp) {
	CharType charType = CharType::BLANK;
	stack<char> s_oldExp;
	stack<char> s_newExp;
	stack<char> s_oper;

	for (auto it = oldExp.begin(); it != oldExp.end(); ++it) {
		while ((charType = getCharType(*it)) == CharType::BLANK) ++it;

		if (charType == CharType::ERROR_TYPE)
			return;
		else if (charType == CharType::VARIABLE) {
			stack<char> copy = s_oldExp;
			if (!copy.empty() && getCharType(copy.top()) == CharType::VARIABLE) {
				stackTransfer('*', s_oper, s_newExp, false);
			}
			s_newExp.push(*it);
		}
		else if (charType == CharType::R_BRACKET) {
			stackTransfer(*it, s_oper, s_newExp, true);
		}
		else if (charType == CharType::L_BRACKET) {
			stack<char> copy = s_oldExp;
			if (!copy.empty() && getCharType(copy.top()) == CharType::R_BRACKET) {
				stackTransfer('*', s_oper, s_newExp, false);
			}
			s_oper.push(*it);
		}
		else if (charType == CharType::NOT) {
			stack<char> copy = s_oldExp;
			while (!copy.empty() && copy.top() == CharType::NOT) copy.pop();
			if (!copy.empty() && (getCharType(copy.top()) == CharType::VARIABLE || getCharType(copy.top()) == CharType::R_BRACKET)) {
				stackTransfer('*', s_oper, s_newExp, false);
			}
			s_oper.push(*it);
		}
		else {
			stackTransfer(*it, s_oper, s_newExp, false);
		}

		s_oldExp.push(*it);
	}
	while (!s_oper.empty()) {
		s_newExp.push(s_oper.top());
		s_oper.pop();
	}
	while (!s_newExp.empty()) {
		_postfixExpression.push(s_newExp.top());
		s_newExp.pop();
	}
}

int LogicalOperation::getVariableValue(const char& var) {
	if ('A' <= var && var <= 'Z') {
		if (_style == DEFAULT)
			return _trueTable[var - 'A'];
		else if (_style == KARNO)
			return _trueTable_kn[var - 'A'];
	}
	else if ('0' <= var && var <= '9') {
		return var - '0';
	}
	else return -1;
}

void LogicalOperation::calculate(const char& oper, stack<char>& s_num) {
	char x, y;
	switch (oper) {
	case '+':
		x = s_num.top();
		s_num.pop();
		y = s_num.top();
		s_num.pop();
		s_num.push((getVariableValue(x) | getVariableValue(y)) + '0');
		break;
	case '*':
		x = s_num.top();
		s_num.pop();
		y = s_num.top();
		s_num.pop();
		s_num.push((getVariableValue(x) & getVariableValue(y)) + '0');
		break;
	case '!':
		x = s_num.top();
		s_num.pop();
		s_num.push(!getVariableValue(x) + '0');
		break;
	}
}