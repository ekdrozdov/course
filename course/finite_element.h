#pragma once
#include "point.h"

class FE {
public:
	FE();
	FE(DATA_TYPE start, DATA_TYPE end);
	DATA_TYPE x1;
	DATA_TYPE x2;
	DATA_TYPE h;
};