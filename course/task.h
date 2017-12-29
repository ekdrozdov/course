#pragma once
#include "cauchyProblem.h"

class Task : public CauchyProblem {
public:
	Task();
	DATA_TYPE f(DATA_TYPE x);
};