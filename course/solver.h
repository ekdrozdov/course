#pragma once
#include "cauchyProblem.h"
#include "finite_element.h"
#include <stdio.h>

class Solver {
public:
	Solver();
	Solver(int start, int end, int nodesTotal, DATA_TYPE* xi);
	~Solver();
	void buildSLAE(CauchyProblem* problem);
	void solve();
	DATA_TYPE u(DATA_TYPE x);

private:
	DATA_TYPE basisFunc(DATA_TYPE x, int feLeftNum, int feRigthNum);
	FE* fe;
	DATA_TYPE a, c;
	DATA_TYPE* A;
	DATA_TYPE* b;
	DATA_TYPE* q;
};
