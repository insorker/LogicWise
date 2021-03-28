#pragma once
#include "LogicalParser.h"
#include <iostream>
using std::cout;
using std::endl;

class LogicalDraw : LogicalParser
{
public:
	LogicalDraw(unsigned int size, const string& infixExpression, Style style = DEFAULT)
		: LogicalParser(size, infixExpression, style) { }
public:
	void showPostfixExpression() const;
	void showTrueTable();
};