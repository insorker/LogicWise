#pragma once

#include "../TrueTable/TrueTableBase.h"
#include "../TrueTable/TTB_InOrder.h"
#include "../TrueTable//TTB_CyclicCode.h"
#include <string>
#include <stack>
using std::string;
using std::stack;

class LogicalParser
{
public:
	typedef enum { DEFAULT, KARNO } Style;
protected:
	typedef enum { VARIABLE, BLANK, OR, AND, NOT, L_BRACKET, R_BRACKET, ERROR_TYPE } CharType;

public:
	LogicalParser(unsigned int size, const string& infixExpression, Style style = DEFAULT);
	~LogicalParser();

protected:
	unsigned int _size;
	TrueTableBase* _ttb;
	stack<char> _postfixExpression;

protected:
	int charToInt(const char& var);
	void calculate(const char& oper, stack<char>& s_num);
	CharType getCharType(const char& c) const;

private:
	bool charTypeCmp(const char& oper, const char& soper) const;
	void operatorStackPush(const char& c, stack<char>& src, stack<char>& des);
	void infixToPostfix(const string& infixExpression);
};