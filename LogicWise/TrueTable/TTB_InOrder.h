#pragma once
#include "TrueTableBase.h"

class TTB_InOrder : public TrueTableBase
{
public:
	TTB_InOrder()
		: TrueTableBase(), _value(static_cast<unsigned int>(-1)) { }
	TTB_InOrder(unsigned int size)
		: TrueTableBase(size), _value(static_cast<unsigned int>(-1)) { }

	void init(unsigned int size);
	bool next();
	void reset();
	int operator[] (unsigned int i) const;

private:
	unsigned int _value;
};