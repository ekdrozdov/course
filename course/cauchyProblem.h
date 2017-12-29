#pragma once
#include "point.h"

class CauchyProblem {
public:
	Point initCondFirst;
	Point initCondSecond;
	virtual DATA_TYPE f(DATA_TYPE x) = 0;
};
