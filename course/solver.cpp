#include "solver.h"

Solver::Solver() {
	A = NULL;
	b = NULL;
	a = 0;
	c = 0;
	n = 0;
	h = 0;
}

Solver::Solver(int start, int end, int resolution) {
	// resolution -- number of nodes in mesh
	A = new DATA_TYPE[resolution * 3];
	b = new DATA_TYPE[resolution];
	n = resolution - 1;
	a = start;
	c = end;
	h = (end - start) / (resolution - 1.0);
	fe = new FE[n];
	DATA_TYPE x = start;
	fe = new FE[n];
	for (int i = 0; i < n; ++i) {
		fe = &FE(x, x + h);
		x += h;
	}
}

Solver::~Solver() {
	if (A) {
		delete A;
		A = NULL;
	}
	if (b) {
		delete b;
		b = NULL;
	}
	if (fe) {
		delete fe;
		fe = NULL;
	}
	a = 0;
	c = 0;
	n = 0;
	h = 0;
}


void Solver::buildSystem(CauchyProblem* problem) {
	for (DATA_TYPE* pA = A, *pB = b; pA < &A[n * 3]; ++pA, ++pB) {
		*pA = 0;
		*pB = 0;
	}

	DATA_TYPE* pA = A + 1;
	DATA_TYPE* pB = b;
	for (int i = 0; i < n; ++i) {
		DATA_TYPE impact = fe[i].h;
		*pA += impact;
		pA++;
		*pA -= impact;
		pA++;
		*pA-= impact;
		pA++;
		*pA += impact;

		*pB = (fe[i].h / 6.0) * (2.0 * problem->f(fe[i].x1 + problem->f(fe[i].x2)));
		pB++;
		*pB = (fe[i].h / 6.0) * (problem->f(fe[i].x1 + 2.0 * problem->f(fe[i].x2)));
	}
}