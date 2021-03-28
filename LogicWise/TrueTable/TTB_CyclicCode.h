#pragma once
#include "TrueTableBase.h"
#include <vector>
using std::vector;

class TTB_CyclicCode : public TrueTableBase
{
public:
	TTB_CyclicCode()
		: TrueTableBase(), _rowLength(0), _colLength(0), _rowIndex(1), _valueBuffer(), _value() { }
	TTB_CyclicCode(unsigned int size)
		: TrueTableBase(size), _rowLength(1 << size), _colLength(size), _rowIndex(1),
		_valueBuffer(new int[_rowLength + 1]), _value() { }
	~TTB_CyclicCode() {
		delete[] _valueBuffer;
	}

	void init(unsigned int size);
	bool next();
	void reset();
	int operator[] (unsigned int i) const;

private:
	unsigned int getValue(unsigned int p, unsigned int u);
	vector<unsigned int> intToVector(int x, int n);

private:
	unsigned int _rowLength;
	unsigned int _colLength;
	unsigned int _rowIndex;
	int* _valueBuffer;
	vector<int> _value;
};