#pragma once
#include "point.h"

class CauchyProblem {
public:
	// u(a) = u<g>.
	DATA_TYPE boundCondFirst;
	// du / dx [x = 0] = theta.
	DATA_TYPE boundCondSecond;
	virtual DATA_TYPE f(DATA_TYPE x) = 0;
};
