#pragma once

#include <string>
#include <stack>
#include <iostream>
#include "TrueTable.h"
#include "CyclicCode.h"
using std::string;
using std::stack;
using std::cout;

class LogicalOperation {
	typedef enum { VARIABLE, BLANK, OR, AND, NOT, L_BRACKET, R_BRACKET, ERROR_TYPE } CharType;
public:
	typedef enum { DEFAULT, KARNO } Style;
	LogicalOperation(unsigned int& size, const string& infixExpression, Style style = DEFAULT);
	void showPostfixExpression() const;
	void showTrueTable();
	void showKarnaughDiagram();
	void showSimplifiedResult();
private:
	CharType getCharType(const char& c) const;
	bool charTypeCmp(const char& oper, const char& soper) const;
	void stackTransfer(const char& c, stack<char>& src, stack<char>& des, bool hasBracket = false);
	void infixToPostfix(const string& oldExp);
	int getVariableValue(const char& var);
	void calculate(const char& oper, stack<char>& s_num);
private:
	unsigned int _size;
	stack<char> _postfixExpression;
	TrueTable _trueTable;
	CyclicCode _trueTable_kn;
	Style _style;
};
