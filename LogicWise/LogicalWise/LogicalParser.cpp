#include "LogicalParser.h"

LogicalParser::LogicalParser(unsigned int size, const string& infixExpression, Style style)
	: _size(size), _ttb()
{
	switch (style) {
	case DEFAULT:
		_ttb = new TTB_InOrder(size);
		break;
	case KARNO:
		_ttb = new TTB_CyclicCode(size);
		break;
	}
	infixToPostfix(infixExpression);
}

LogicalParser::~LogicalParser() {
	delete _ttb;
}

int LogicalParser::charToInt(const char& var) {
	if ('A' <= var && var <= 'Z') {
		return (*_ttb)[var - 'A'];
	}
	else if ('0' <= var && var <= '9') {
		return var - '0';
	}
	else return -1;
}

void LogicalParser::calculate(const char& oper, stack<char>& s_num) {
	char x, y;
	switch (oper) {
	case '+':
		x = s_num.top();
		s_num.pop();
		y = s_num.top();
		s_num.pop();
		s_num.push((charToInt(x) | charToInt(y)) + '0');
		break;
	case '*':
		x = s_num.top();
		s_num.pop();
		y = s_num.top();
		s_num.pop();
		s_num.push((charToInt(x) & charToInt(y)) + '0');
		break;
	case '!':
		x = s_num.top();
		s_num.pop();
		s_num.push(!charToInt(x) + '0');
		break;
	}
}

LogicalParser::CharType LogicalParser::getCharType(const char& c) const {
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

bool LogicalParser::charTypeCmp(const char& oper, const char& soper) const {
	return getCharType(oper) <= getCharType(soper) ? true : false;
}


void LogicalParser::operatorStackPush(const char& c, stack<char>& src, stack<char>& des) {
	if (c != ')') {
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

void LogicalParser::infixToPostfix(const string& infixExpression) {
	CharType charType = CharType::BLANK;
	stack<char> s_oldExp;
	stack<char> s_newExp;
	stack<char> s_oper;

	for (auto it = infixExpression.begin(); it != infixExpression.end(); ++it) {
		while ((charType = getCharType(*it)) == CharType::BLANK) ++it;

		if (charType == CharType::ERROR_TYPE)
			return;

		if (charType == CharType::VARIABLE || charType == CharType::NOT || charType == CharType::L_BRACKET) {
			stack<char> copy = s_oldExp;
			if (!copy.empty()) {
				bool flag = (getCharType(copy.top()) == CharType::VARIABLE)
					|| (getCharType(copy.top()) == CharType::R_BRACKET);
				if (flag)
					operatorStackPush('*', s_oper, s_newExp);
			}
		}

		if (charType == CharType::VARIABLE) {
			s_newExp.push(*it);
		}
		else {
			operatorStackPush(*it, s_oper, s_newExp);
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
