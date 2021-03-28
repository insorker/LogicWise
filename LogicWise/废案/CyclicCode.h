#pragma once
#include <string.h>
#include <vector>
using std::vector;

class CyclicCode {
public:
	CyclicCode(unsigned int size)
		: _colSize(size), _rowSize(1 << size), _currentRow(1), _code(new int[_rowSize + 1]), _value() { }
	CyclicCode()
		: _colSize(), _rowSize(), _currentRow(), _code(), _value() { }
	~CyclicCode() {
		delete[] _code;
	}
	void init(unsigned int size) {
		_colSize = size;
		_rowSize = 1 << size;
		_currentRow = 1;
		_code = new int[_rowSize + 1];
	}
	bool next() {
		if (_currentRow > _rowSize)
			return false;

		_code[_currentRow] = getValue(_currentRow, _rowSize >> 1);
		vector<unsigned int> v = intToBinary(_code[_currentRow], _colSize);

		_value.clear();
		for (auto it = v.rbegin(); it != v.rend(); it++)
			_value.push_back(*it);

		_currentRow++;
		return true;
	}
	void reset() {
		_currentRow = 1;
		memset(_code, -1, _rowSize);
	}
	int operator[] (unsigned int i) const {
		if (i >= _colSize)
			return -1;
		else
			return _value[i];
	}
private:
	unsigned int getValue(const int p, const int u) {
		if (p == 1) {
			_code[1] = 0;
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
				return _code[np] - u;
			}
		}
	}
	vector<unsigned int> intToBinary(int x, int n) {
		vector<unsigned int> v;
		if (x >= 0) {
			while (x) {
				v.push_back(x & 1);
				x >>= 1;
			}
			while (v.size() < n) v.push_back(0);
		}
		else if (x < 0) {
			v = intToBinary(x + (1 << (n - 1)), n - 1);
			v.push_back(1);
		}

		return v;
	}
private:
	unsigned int _colSize;
	unsigned int _rowSize;
	unsigned int _currentRow;
	int* _code;
	vector<unsigned int> _value;
};