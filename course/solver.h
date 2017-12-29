#pragma once
#include "cauchyProblem.h"
#include "finite_element.h"
#include <stdio.h>

class Solver {
public:
	Solver();
	Solver(int start, int end, int resolution);
	~Solver();
	void buildSystem(CauchyProblem* problem);
	void solve();
	DATA_TYPE getSolution(DATA_TYPE x);

private:
	FE* fe;
	DATA_TYPE a, c;
	DATA_TYPE h;
	int n; // number of finite elements
	DATA_TYPE* A;
	DATA_TYPE* b;
};