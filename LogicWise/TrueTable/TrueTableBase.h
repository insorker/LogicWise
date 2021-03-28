#pragma once

class TrueTableBase {
public:
	TrueTableBase()
		: _size(0) { }
	TrueTableBase(unsigned int size)
		: _size(size) { }

public:
	virtual void init(unsigned int size) = 0;
	virtual bool next() = 0;
	virtual void reset() = 0;
	virtual int operator[] (unsigned int i) const = 0;

protected:
	unsigned int _size;
};