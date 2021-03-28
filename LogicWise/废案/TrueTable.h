#pragma once

/* Ë³ÐòÉú³É£¬ÒÑ·ÏÆú */

class TrueTable {
public:
	TrueTable(const unsigned int& length)
		: _length(length), _value(0) { }
	unsigned long long value() const;
	bool next();
	void reset();
	int operator[] (unsigned int i) const {
		if (i >= _length)
			return -1;
		else
			return (_value >> (_length - i - 1)) & 1;
	}
private:
	unsigned int _length;
	unsigned long long _value;
};