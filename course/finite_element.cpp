#include "finite_element.h"

int FE::total = 0;

FE::FE() {
	x1 = 0.0;
	x2 = 0.0;
	h = 0.0;
	++total;
}

FE::~FE() {
	x1 = 0.0;
	x2 = 0.0;
	h = 0.0;
	--total;
}

FE::FE(DATA_TYPE start, DATA_TYPE end) {
	x1 = start;
	x2 = end;
	h = end - start;
}
