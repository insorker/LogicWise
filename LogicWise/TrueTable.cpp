#include "TrueTable.h"

unsigned long long TrueTable::value() const {
	return _value;
}

bool TrueTable::next() {
	if (_value >= (1ULL << _length) - 1)
		return false;

	_value++;
	return true;
}

void TrueTable::reset() {
	_value = 0;
}