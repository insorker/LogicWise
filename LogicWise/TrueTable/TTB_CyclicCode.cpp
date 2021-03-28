#include "TTB_CyclicCode.h"

void TTB_CyclicCode::init(unsigned int size) {
	_size = size;
	_rowLength = 1 << size;
	_colLength = size;
	_rowIndex = 1;
	_valueBuffer = new int[_rowLength + 1];
}

bool TTB_CyclicCode::next() {
	if (_rowIndex > _rowLength)
		return false;

	_valueBuffer[_rowIndex] = getValue(_rowIndex, _rowLength >> 1);
	vector<unsigned int> v = intToVector(_valueBuffer[_rowIndex], _colLength);

	_value.clear();
	for (auto it = v.rbegin(); it != v.rend(); it++)
		_value.push_back(*it);

	_rowIndex++;
	return true;
}

void TTB_CyclicCode::reset() {
	_rowIndex = 1;
	_value.clear();
}

int TTB_CyclicCode::operator[] (unsigned int i) const {
	if (i >= _colLength)
		return -1;
	else
		return _value[i];
}

unsigned int TTB_CyclicCode::getValue(unsigned int p, unsigned int u) {
	if (p == 1) {
		_valueBuffer[1] = 0;
		return 0;
	}
	else {
		if (p <= u) {
			if (p <= (u >> 1))
				return getValue(p, u >> 1);
			else
				return getValue(p, u >> 1) + u;
		}
		else {
			int np = (u << 1) - p + 1;
			return _valueBuffer[np] - u;
		}
	}
}

vector<unsigned int> TTB_CyclicCode::intToVector(int x, int n) {
	vector<unsigned int> v;
	if (x >= 0) {
		while (x) {
			v.push_back(x & 1);
			x >>= 1;
		}
		while (v.size() < n) v.push_back(0);
	}
	else if (x < 0) {
		v = intToVector(x + (1 << (n - 1)), n - 1);
		v.push_back(1);
	}

	return v;
}
