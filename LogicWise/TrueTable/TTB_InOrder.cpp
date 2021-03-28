#include "TTB_InOrder.h"

void TTB_InOrder::init(unsigned int size) {
	_size = size;
	_value = static_cast<unsigned int>(-1);
}

bool TTB_InOrder::next() {
	if (_value + 1 > (1 << _size) - 1)
		return false;

	_value++;
	return true;
}

void TTB_InOrder::reset() {
	_value = static_cast<unsigned int>(-1);
}

int TTB_InOrder::operator[] (unsigned int i) const {
	if (i >= _size)
		return -1;
	else
		return (_value >> _size - i - 1) & 1;
}